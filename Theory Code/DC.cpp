// DC.cpp

const int MAX_N = 10000;

// 面对菊花图等毒瘤结构，边分治的复杂度就会飙升，这个时候我们需要加
// 虚点和虚边来优化树，使其变为一颗二叉树。
struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];
int head[MAX_N]; // 默认全为 -1.

void rebuild(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].to)
    {
        int to = edges[i].to, wt = edges[i].weight;
        if (to == fa)
            continue;
        
    }
}