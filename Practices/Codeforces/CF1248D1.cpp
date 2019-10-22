// CF1248D1.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550;

char str[MAX_N];
int n, val;
pair<int, int> answer;

int calc()
{
    int cnt = 0, min_pos = -1, min_val = n;
    for (int i = 1; i <= n; i++)
    {
        if (str[i] == '(')
            cnt++;
        else
            cnt--;
        if (str[i] == '(' && cnt < min_val)
            min_val = cnt, min_pos = i;
    }
    cnt = 0;
    int pans = 0;
    for (int i = 1, j = min_pos; i <= n; i++, j = ((j == n) ? 1 : j + 1))
    {
        if (str[j] == '(')
            cnt++;
        else
        {
            cnt--;
            if (cnt == 0)
                pans++;
        }
    }
    return pans;
}

int main()
{
    scanf("%d%s", &n, str + 1);
    int lbrucket = 0, rbrucket = 0;
    for (int i = 1; i <= n; i++)
        lbrucket += (str[i] == '('), rbrucket += (str[i] == ')');
    if (lbrucket != rbrucket)
        printf("0\n1 1"), exit(0);
    val = calc(), answer = make_pair(1, 1);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            swap(str[i], str[j]);
            int pans = calc();
            if (pans > val)
                val = pans, answer = make_pair(i, j);
            swap(str[i], str[j]);
        }
    printf("%d\n%d %d", val, answer.first, answer.second);
    return 0;
}