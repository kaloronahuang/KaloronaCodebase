// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n, ai[MAX_N];
vector<int> seq;

int main()
{
    bool valid = true;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), seq.push_back(ai[i]);
    stack<int> st;
    while (!seq.empty())
    {
        int pos = 0;
        for (int i = 0, siz = seq.size(); i < siz; i++)
            if (seq[i] == i + 1)
                pos = i + 1;
        if (pos == 0)
            puts("-1"), exit(0);
        seq.erase(seq.begin() + pos - 1);
        st.push(pos);
    }
    while (!st.empty())
        printf("%d\n", st.top()), st.pop();
    return 0;
}