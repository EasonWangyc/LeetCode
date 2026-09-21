"""
请实现一个标准的Transformer Encoder Layer。该层由两个主要子层组成:
- 多头自注意力机制(Multi-Head Self-Attention. MHSA)
- 前馈网络 (Position-wise Feed-Forward Network FFN)
每个子层之后都紧跟着残差连接(Residual Connection)和层归一化(Layer Normalization)。
实现要求:编写 Transformer Encoder Layer 类的 forward方法,使用单位矩阵作为权重

输入:x (batch_size, seq_len, d_model) = (1, 2, 4)
输出:output (batch_size, seq_len, d_model) = (1, 2. 4)

样例
输入:11.00 12.00 3.00 1.00 15.00 16.00 10.00 11.00
输出:0.81 1.17-0.95-1.04 0.72 1.24-1.11-0.8

注意：$$\text{FFN}(x) = \text{Activation}(x W_1 + b_1) W_2 + b_2$$
使用单位矩阵作为权重且激活函数为ReLU时,W_1 = W_2 = I, b_1 = b_2 = 0,此时FFN = ReLU(x) = max(0, x)
"""
import math
import numpy as np

def self_attention(x):
    """两个头的自注意力机制"""
    batch_size, seq_len, model_dim = x.shape;
    num_head, head_dim = 2, 2;
    # 最后一个维度切分，且调整顺序便于注意力计算
    q = x.reshape(batch_size, seq_len, num_head, head_dim)
    q = q.transpose(0, 2, 1, 3)
    k = q
    v = q
    scores = q @ k.transpose(0, 1, 3, 2) / math.sqrt(head_dim)
    scores = scores - scores.max(axis=-1, keepdims=True)
    weights = np.exp(scores)
    weights /= weights.sum(axis=-1,keepdims=True)
    attn = weights @ v
    attn = attn.transpose(0, 2, 1, 3)
    return attn.reshape(batch_size, seq_len, model_dim)

def layer_norm(x, eps=1e-5):
    """在最后一个维度执行layernorm"""
    mean = x.mean(axis=-1, keepdims=True)
    variance = ((x - mean) ** 2).mean(axis=-1, keepdims=True)
    return (x - mean) / np.sqrt(variance + eps)

def encoder_forward(x):
    # 第一层实现MHSA，然后残差连接和LayerNorm
    hidden = layer_norm(x + self_attention(x))
    # 第二层，单位矩阵FFN退化为逐元素ReLU
    hidden = layer_norm(hidden + np.maximum(0.0, hidden))
    return hidden

values = list(map(float, input().split()))
inputs = np.array(values, dtype=float).reshape(1, 2, 4)
outputs = encoder_forward(inputs).reshape(-1)
print(" ".join(f"{value:.2f}" for value in outputs))