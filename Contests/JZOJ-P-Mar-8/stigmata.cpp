// stigmata.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;

int n, m;
double p, q, ai[MAX_N], bi[MAX_N], gans;
priority_queue<double> pq;

char nc()
{
    static char buff[1 << 20], *p1, *p2;
    return p1 == p2 && (p2 = (p1 = buff) + fread(buff, 1, 1 << 20, stdin)) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char c = nc();
    while (!isdigit(c))
        f = (c == '-') ? -1 : f, c = nc();
    while (isdigit(c))
        x = (x << 3) + (x << 1) + c - '0', c = nc();
    return x * f;
}

void fileIO()
{
    freopen("stigmata.in", "r", stdin);
    freopen("stigmata.out", "w", stdout);
}

double pow2(double x) { return x * x; }

int main()
{
    // fileIO();
    n = read(), p = read(), q = read(), m = read(), p /= 1000, q /= 1000;
    for (int i = 1; i <= n; i++)
        ai[i] = read(), bi[i] = read(), ai[i] /= 1000, bi[i] /= 1000;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (ai[i] != ai[j])
            {
                double midx = (bi[j] - bi[i]) / (ai[i] - ai[j]);
                double midy = (ai[i] * bi[j] - ai[j] * bi[i]) / (ai[i] - ai[j]);
                double z = pow2(midx - p) + pow2(midy - q);
                if (pq.size() < m)
                    pq.push(z);
                else if (pq.top() > z)
                    pq.pop(), pq.push(z);
            }
    while (!pq.empty())
        gans += sqrt(pq.top()), pq.pop();
    printf("%.10lf\n", gans);
    return 0;
}