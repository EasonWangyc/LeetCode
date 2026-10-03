"""
Multi-Head Self-Attention —— NumPy 参考实现

用途：
1. 面试白板：不依赖框架，只用 numpy 就能讲清楚每一步的 shape 变换
2. 对拍：CUDA kernel 的正确性可以用这里的输出做基准

依赖 numpy。运行：
  python3 attention.py
"""
import numpy as np


# --------------------------------------------------------------------- softmax
def softmax(x, axis=-1):
    """数值稳定版：先减最大值，否则 exp(大数) 会溢出成 inf。"""
    x = x - x.max(axis=axis, keepdims=True)
    e = np.exp(x)
    return e / e.sum(axis=axis, keepdims=True)


# ------------------------------------------------------------------ layer norm
def layer_norm(x, gamma, beta, eps=1e-5):
    """沿最后一维归一化。gamma/beta 的 shape 是 (d_model,)。"""
    mean = x.mean(axis=-1, keepdims=True)
    var = x.var(axis=-1, keepdims=True)
    return (x - mean) / np.sqrt(var + eps) * gamma + beta


# ------------------------------------------------------------------------ MHA
def multi_head_attention(X, Wq, Wk, Wv, Wo, num_heads, causal=True):
    """
    X:  (batch, seq_len, d_model)
    Wq/Wk/Wv/Wo: (d_model, d_model)
    返回: (batch, seq_len, d_model)

    四步 shape 变换（面试就按这个顺序讲）：
      1. 投影      (B, S, D) -> (B, S, D)
      2. 分头      (B, S, D) -> (B, H, S, hd)
      3. 注意力    (B, H, S, hd) -> (B, H, S, hd)
      4. 合并+投影 (B, S, D) -> (B, S, D)
    """
    B, S, D = X.shape
    hd = D // num_heads
    assert D % num_heads == 0, "d_model 必须能被 head 数整除"

    # 1. 线性投影
    Q = X @ Wq
    K = X @ Wk
    V = X @ Wv

    # 2. 分头：把最后一维切成 H 段，并把 head 维挪到前面
    def split_heads(t):
        return t.reshape(B, S, num_heads, hd).transpose(0, 2, 1, 3)  # (B, H, S, hd)

    Q, K, V = split_heads(Q), split_heads(K), split_heads(V)

    # 3. 缩放点积注意力
    scale = 1.0 / np.sqrt(hd)          # 少了它，d_head 一大 softmax 就饱和
    scores = Q @ K.transpose(0, 1, 3, 2) * scale          # (B, H, S, S)

    if causal:
        # 上三角（不含对角线）置 -inf，exp 之后自然变成 0
        mask = np.triu(np.ones((S, S), dtype=bool), k=1)
        scores = np.where(mask, -np.inf, scores)

    attn = softmax(scores, axis=-1) @ V                    # (B, H, S, hd)

    # 4. 合并多头，再投影
    attn = attn.transpose(0, 2, 1, 3).reshape(B, S, D)
    return attn @ Wo


def multi_head_attention_naive(X, Wq, Wk, Wv, Wo, num_heads, causal=True):
    """逐元素三重循环的直译版，只用来验证上面的向量化写法。"""
    B, S, D = X.shape
    hd = D // num_heads
    Q, K, V = X @ Wq, X @ Wk, X @ Wv
    out = np.zeros((B, S, D))
    scale = 1.0 / np.sqrt(hd)

    for b in range(B):
        for h in range(num_heads):
            for i in range(S):
                q = Q[b, i, h * hd:(h + 1) * hd]
                hi = i + 1 if causal else S
                scores = np.array([
                    float(q @ K[b, j, h * hd:(h + 1) * hd]) * scale
                    for j in range(hi)
                ])
                w = np.exp(scores - scores.max())
                w /= w.sum()
                for d in range(hd):
                    out[b, i, h * hd + d] = sum(
                        w[j] * V[b, j, h * hd + d] for j in range(hi)
                    )
    return out @ Wo


# -------------------------------------------------------------------- 自测
if __name__ == "__main__":
    rng = np.random.default_rng(0)
    B, S, D, H = 2, 4, 8, 2

    X = rng.standard_normal((B, S, D)).astype(np.float64)
    Wq, Wk, Wv, Wo = (rng.standard_normal((D, D)) * 0.2 for _ in range(4))

    print("=== softmax ===")
    big = np.array([[1000.0, 1000.0, 1000.0]])   # 不减最大值这里就是 nan
    print("大数输入 ->", softmax(big), " 行和 =", softmax(big).sum())
    assert np.allclose(softmax(big).sum(axis=-1), 1.0)

    print("\n=== layer_norm ===")
    x = rng.standard_normal((3, 16)) * 5 + 100   # 均值远离 0
    y = layer_norm(x, np.ones(16), np.zeros(16))
    print("输出均值", np.abs(y.mean(-1)).max(), " 输出方差", np.abs(y.var(-1) - 1).max())
    assert np.allclose(y.mean(-1), 0, atol=1e-10)
    assert np.allclose(y.var(-1), 1, atol=1e-10)

    print("\n=== MHA ===")
    vec = multi_head_attention(X, Wq, Wk, Wv, Wo, H, causal=True)
    naive = multi_head_attention_naive(X, Wq, Wk, Wv, Wo, H, causal=True)
    print("向量化 vs 三重循环 最大差:", np.abs(vec - naive).max())
    print("输出 shape:", vec.shape)
    assert np.allclose(vec, naive, atol=1e-12)
    assert vec.shape == (B, S, D)

    print("\n=== 因果性 ===")
    X2 = X.copy()
    X2[:, -1, :] += 10.0          # 只改最后一个 token
    vec2 = multi_head_attention(X2, Wq, Wk, Wv, Wo, H, causal=True)
    leak = np.abs(vec2[:, :-1, :] - vec[:, :-1, :]).max()
    moved = np.abs(vec2[:, -1, :] - vec[:, -1, :]).max()
    print(f"前面 token 的输出变化 = {leak:.3e}（应为 0）")
    print(f"最后 token 的输出变化 = {moved:.3e}（应 > 0）")
    assert leak == 0.0 and moved > 0

    print("\n=== 缩放因子的作用 ===")
    for hd in (4, 64, 512):
        q = rng.standard_normal(hd)
        k = rng.standard_normal(hd)
        raw = q @ k
        print(f"  head_dim={hd:4d}  q·k={raw:8.2f}   缩放后={raw / np.sqrt(hd):6.3f}")

    print("\n全部通过 ✓")
