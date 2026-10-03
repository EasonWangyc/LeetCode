"""
RoPE (Rotary Position Embedding) —— NumPy 参考实现

依赖 numpy。运行：
  python3 rope.py

⚠️ 有一个坑必须讲清楚：RoPE 有两种**不等价**的配对约定，很多资料混着讲。

  约定 A「交错对」(interleaved，原论文 / LLaMA 的 HF 实现之一)
      配对 (x0,x1), (x2,x3), ... 第 i 对用角度 θ_i

  约定 B「前后半」(rotate_half，GPT-NeoX / 大部分 HF 模型)
      配对 (x_i, x_{i+d/2}), ... 第 i 对用角度 θ_i

两者只差一个固定的维度置换（把 [偶, 奇] 重排成 [前, 后]），
所以数学上能互相转换，但**同一个公式下混用两种约定，结果就是错的**。
下面两套都实现并各自验证。
"""
import numpy as np


# ============================================================ 约定 A：交错对
def build_rope_cache(seq_len, head_dim, base=10000.0):
    """
    预计算 cos/sin 表，shape (seq_len, head_dim)。
    工程实现都这么干 —— 否则每个 token 都要重算 pow/cos/sin。
    交错对约定下，第 2i 和 2i+1 个分量共用角度 θ_i。
    """
    half = head_dim // 2
    inv_freq = base ** (-2.0 * np.arange(half) / head_dim)   # θ_i 的系数
    theta = np.arange(seq_len)[:, None] * inv_freq[None, :]  # (S, half)
    emb = np.repeat(theta, 2, axis=-1)                       # (S, d)
    return np.cos(emb), np.sin(emb)


def rotate_interleaved(x):
    """[x0,x1,x2,x3] -> [-x1,x0,-x3,x2]"""
    out = np.empty_like(x)
    out[..., 0::2] = -x[..., 1::2]
    out[..., 1::2] = x[..., 0::2]
    return out


def apply_rope(x, cos, sin):
    """x: (..., seq_len, head_dim)，cos/sin: (seq_len, head_dim)"""
    return x * cos + rotate_interleaved(x) * sin


def apply_rope_naive(x, positions, base=10000.0):
    """按交错对逐对旋转的直译版，用来验证上面的表驱动写法。"""
    d = x.shape[-1]
    out = np.zeros_like(x)
    for i in range(d // 2):
        theta = positions * base ** (-2.0 * i / d)
        c, s = np.cos(theta), np.sin(theta)
        x0, x1 = x[..., 2 * i], x[..., 2 * i + 1]
        out[..., 2 * i] = x0 * c - x1 * s
        out[..., 2 * i + 1] = x0 * s + x1 * c
    return out


# ============================================================ 约定 B：前后半
def build_rope_cache_hf(seq_len, head_dim, base=10000.0):
    """前后半约定：前半和后半共用角度，所以是把 theta 拼两份而不是 repeat。"""
    half = head_dim // 2
    inv_freq = base ** (-2.0 * np.arange(half) / head_dim)
    theta = np.arange(seq_len)[:, None] * inv_freq[None, :]   # (S, half)
    emb = np.concatenate([theta, theta], axis=-1)             # (S, d)
    return np.cos(emb), np.sin(emb)


def rotate_half(x):
    """HuggingFace 的写法：[x1, x2] -> [-x2, x1]（x1/x2 是前后两半）"""
    half = x.shape[-1] // 2
    return np.concatenate([-x[..., half:], x[..., :half]], axis=-1)


def apply_rope_hf(x, cos, sin):
    return x * cos + rotate_half(x) * sin


def apply_rope_naive_hf(x, positions, base=10000.0):
    """前后半配对的直译版。"""
    d = x.shape[-1]
    half = d // 2
    out = np.zeros_like(x)
    for i in range(half):
        theta = positions * base ** (-2.0 * i / d)
        c, s = np.cos(theta), np.sin(theta)
        x0, x1 = x[..., i], x[..., i + half]
        out[..., i] = x0 * c - x1 * s
        out[..., i + half] = x0 * s + x1 * c
    return out


def interleaved_to_halfsplit(x):
    """把 [偶, 奇] 布局重排成 [前, 后] 布局 —— 两种约定之间的那个置换。"""
    return np.concatenate([x[..., 0::2], x[..., 1::2]], axis=-1)


if __name__ == "__main__":
    rng = np.random.default_rng(0)
    B, H, S, d = 2, 4, 8, 16
    x = rng.standard_normal((B, H, S, d))
    pos = np.arange(S)

    print("=== 约定 A：表驱动 vs 直译 ===")
    cosA, sinA = build_rope_cache(S, d)
    a = apply_rope(x, cosA, sinA)
    b = apply_rope_naive(x, pos)
    print("最大差:", np.abs(a - b).max())
    assert np.allclose(a, b, atol=1e-10)

    print("\n=== 约定 B：表驱动 vs 直译 ===")
    cosB, sinB = build_rope_cache_hf(S, d)
    c = apply_rope_hf(x, cosB, sinB)
    e = apply_rope_naive_hf(x, pos)
    print("最大差:", np.abs(c - e).max())
    assert np.allclose(c, e, atol=1e-10)

    print("\n=== 两种约定的关系：差一个固定置换 ===")
    # 先按 A 旋转再换布局，应当等于先换布局再按 B 旋转
    lhs = interleaved_to_halfsplit(a)
    rhs = apply_rope_hf(interleaved_to_halfsplit(x), cosB, sinB)
    print("置换后最大差:", np.abs(lhs - rhs).max())
    assert np.allclose(lhs, rhs, atol=1e-10)
    print("（注意：不换布局直接用 B 的公式套 A 的数据，误差是",
          f"{np.abs(a - c).max():.3f} —— 这就是混用两种约定的后果）")

    print("\n=== 性质 1：正交变换，不改变长度 ===")
    for name, y in (("A", a), ("B", c)):
        diff = np.abs(np.linalg.norm(x, axis=-1) - np.linalg.norm(y, axis=-1)).max()
        print(f"  约定 {name}: ‖y‖ - ‖x‖ 最大偏差 = {diff:.3e}")
        assert diff < 1e-10

    print("\n=== 性质 2：<RoPE(q,m), RoPE(k,n)> 只依赖 m-n ===")
    q = rng.standard_normal(d)
    v = np.tile(q, (1, 1, S, 1))          # 所有位置内容相同，点积只由位置差决定
    r = apply_rope(v, cosA, sinA)[0, 0]   # (S, d)
    for diff in (1, 2, 3):
        dots = [float(r[i] @ r[i + diff]) for i in range(S - diff)]
        spread = max(dots) - min(dots)
        print(f"  间隔 {diff}: 极差 = {spread:.2e}   点积 ≈ {dots[0]:.4f}")
        assert spread < 1e-10
    print("  -> 这正是 RoPE 相对位置性质的来源：两个旋转的夹角只由 m-n 决定")

    print("\n全部通过 ✓")
