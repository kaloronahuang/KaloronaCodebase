#include <iostream>
#include <algorithm>
#include <cstdio>
#define pr pair<int, int>
using namespace std;
bool pre[4][4], curt[4][4];
char crt;
int ans = 1e9, answer;
void place(int x, int y)
{
    for (int i = 0; i < 4; i++)
        curt[x][i] ^= 1;
    for (int i = 0; i < 4; i++)
        curt[i][y] ^= 1;
    curt[x][y] ^= 1;
}
pr getPos(int th)
{
    return make_pair((int)(th / 4), th % 4);
}
int main()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            scanf("%c", &crt);
            if (crt == '\n')
                j--;
            else
                pre[i][j] = (crt == '-');
        }
    for (int st = 0; st < (1 << 16); st++)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                curt[i][j] = pre[i][j];
        int cnt = 0;
        for (int i = 0; i < 16; i++)
        {
            if ((st >> i) & 1)
                place(getPos(i).first, getPos(i).second), cnt++;
            if (cnt > ans)
                goto cont;
        }
    cont:
        if (cnt > ans)
            continue;
        bool flag = true;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (!curt[i][j])
                {
                    flag = false;
                    goto cst_label;
                }
        if (flag && ans > cnt)
            ans = cnt, answer = st;
    cst_label:
        continue;
    }
    printf("%d\n", ans);
    for (int i = 0; i < 16; i++)
        if ((answer >> i) & 1)
            printf("%d %d\n", getPos(i).first + 1, getPos(i).second + 1);
    return 0;
}