// POJ1015.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
int n, m, pi[220], di[220], rd = 1, F[30][805], D[220][25][805], suma, sumb;
vector<int> anses;
void getPath(int i, int j, int k)
{
    if (j == 0)
        return;
    int last = D[i][j][k];
    getPath(last - 1, j - 1, k - (pi[last] - di[last]));
    anses.push_back(last);
    suma += pi[last], sumb += di[last];
}
int main()
{
    while (scanf("%d%d", &n, &m) && n != 0 && m != 0)
    {
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &pi[i], &di[i]);
        memset(F, 0xcf, sizeof(F));
        F[0][400] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = m; j > 0; j--)
                for (int k = 0; k <= 800; k++)
                    D[i][j][k] = D[i - 1][j][k];
            for (int j = m; j; j--)
                for (int k = 0; k <= 800; k++)
                {
                    if (k - (pi[i] - di[i]) < 0 || k - (pi[i] - di[i]) > 800)
                        continue;
                    int val = F[j - 1][k - (pi[i] - di[i])] + pi[i] + di[i];
                    if (val > F[j][k])
                        F[j][k] = val, D[i][j][k] = i;
                }
        }
        int ans = 0;
        for (int k = 0; k <= 400; k++)
        {
            if (F[m][k + 400] >= 0 && F[m][k + 400] > F[m][400 - k])
            {
                ans = k + 400;
                break;
            }
            if (F[m][400 - k] >= 0)
            {
                ans = 400 - k;
                break;
            }
        }
        suma = sumb = 0;
        getPath(n, m, ans);
        printf("Jury #%d\n", rd++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", suma, sumb);
        int siz = anses.size();
        for (int i = 0; i < siz; i++)
            printf(" %d", anses[i]);
        printf("\n\n");
        anses.clear();
    }
    return 0;
}