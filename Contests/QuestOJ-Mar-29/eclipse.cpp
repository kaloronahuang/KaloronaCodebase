// eclipse.cpp
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

int T, A, B, X, Y, Z, mod, C, Q, block;

struct matrix
{
    int ln, col, mat[3][3];

    matrix(int n_ = 3, int m_ = 3) : ln(n_), col(m_) { memset(mat, 0, sizeof(mat)); }

    int *operator[](const int &idx) { return mat[idx]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret(ln, rhs.col);
        for (int i = 0; i < ln; i++)
            for (int j = 0; j < rhs.col; j++)
                for (int k = 0; k < col; k++)
                    ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    bool operator==(const matrix &rhs) const
    {
        for (int i = 0; i < ln; i++)
            for (int j = 0; j < col; j++)
                if (mat[i][j] != rhs.mat[i][j])
                    return false;
        return true;
    }
} trans, bm;

struct matrixHash
{
    ull operator()(const matrix &rhs) const
    {
        ull ret = 0;
        for (int i = 0; i < rhs.ln; i++)
            for (int j = 0; j < rhs.col; j++)
                ret = ret * mod + rhs.mat[i][j];
        return ret;
    }
};

const int upper_domain = 1e6 + 7;

struct hashTable
{

    int head[upper_domain], current;
    struct edge
    {
        int to, nxt;
        ull mat;
    } edges[upper_domain * 10];

    void clear() { memset(head, -1, sizeof(head)), current = 0; }

    void insert(matrix &bas, int to)
    {
        ull val = matrixHash()(bas);
        int key = val % upper_domain;
        for (int i = head[key]; i != -1; i = edges[i].nxt)
            if (edges[i].mat == val)
                return;
        edges[current].to = to, edges[current].nxt = head[key];
        edges[current].mat = val, head[key] = current++;
    }

    int query(matrix &rhs)
    {
        ull val = matrixHash()(rhs);
        int key = val % upper_domain;
        for (int i = head[key]; i != -1; i = edges[i].nxt)
            if (edges[i].mat == val)
                return edges[i].to;
        return -1;
    }
} ump;

vector<int> miniLoop;

ll calcMiniLoop(ll pos, int loopLen)
{
    if (pos < 0)
        return 0;
    return upper_bound(miniLoop.begin(), miniLoop.end(), pos % loopLen) - miniLoop.begin() + (pos / loopLen) * miniLoop.size();
}

int findLoop(matrix start_pt, bool mode = false)
{
    int ret = 2e9;
    matrix curt = start_pt;
    for (int i = 0; i < block; curt = trans * curt, i++)
    {
        int pos = ump.query(curt);
        if (pos - i >= mode)
            ret = min(ret, pos - i);
    }
    return ret == 2e9 ? -1 : ret;
}

int findLoop()
{
    int ret = findLoop(bm, true);
    if (ret == -1)
    {
        matrix curt = trans, start_pt = bm;
        for (int i = 1; i < block; i++)
            curt = trans * curt;
        for (int i = 1;; i++)
        {
            start_pt = curt * start_pt;
            if (start_pt == bm)
                return i * block;
        }
    }
    return ret;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d%d%d%d%d", &A, &B, &X, &Y, &Z, &mod, &C, &Q);
        if (X + Y == 0)
        {
            ll L, R;
            while (Q--)
                scanf("%lld%lld", &L, &R), printf("%lld\n", 1LL * (R - L + 1) * (C == Z));
        }
        else if (Y == 0)
        {
            int len = 1, bas = B;
            miniLoop.clear();
            if (B == C)
                miniLoop.push_back(0);
            while ((bas = bas * X + Z) % mod != B)
            {
                if (bas == C)
                    miniLoop.push_back(len);
                len++;
            }
            ll L, R;
            while (Q--)
            {
                scanf("%lld%lld", &L, &R), L--, R--;
                ll ans = (A == C) + calcMiniLoop(R - 1, len);
                if (L > 0)
                    ans -= (A == C);
                ans -= calcMiniLoop(L - 2, len);
                printf("%lld\n", ans);
            }
        }
        else
        {
            // prep for matrix;
            trans.ln = trans.col = 3;
            trans[0][0] = X, trans[0][1] = Y, trans[0][2] = Z;
            trans[1][0] = trans[2][2] = 1;
            bm.ln = 3, bm.col = 1, bm[0][0] = B, bm[1][0] = A, bm[2][0] = 1;
            // init for bsgs;
            ump.clear(), block = sqrt(mod + 0.5);
            matrix unit = trans, start_pt = bm;
            for (int i = 1; i < block; i++)
                unit = trans * unit;
            for (int i = 0; i < mod * mod + mod; i += block, start_pt = unit * start_pt)
                ump.insert(start_pt, i);
            int len = findLoop();
            miniLoop.clear();
            for (int i = 0; i < mod; i++)
            {
                matrix curt(3, 1);
                curt[0][0] = i, curt[1][0] = C, curt[2][0] = 1;
                int pos = findLoop(curt);
                if (pos != -1)
                    miniLoop.push_back(pos);
            }
            sort(miniLoop.begin(), miniLoop.end());
            while (Q--)
            {
                ll L, R;
                scanf("%lld%lld", &L, &R), L--, R--;
                ll ans = calcMiniLoop(R, len);
                if (L > 0)
                    ans -= calcMiniLoop(L - 1, len);
                printf("%lld\n", ans);
            }
        }
    }
    return 0;
}