// CH1801.cpp
#include <stack>
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
map<char, char> mapping;
stack<char> st;
int main()
{
    mapping['}'] = '{', mapping[')'] = '(', mapping[']'] = '[';
    char ch;
    int ans = 0, max_len = 0;
    bool flag = false;
    while (scanf("%c", &ch) != EOF && ch != 'X')
        if (ch == '{' || ch == '[' || ch == '(')
            st.push(ch), flag = false;
        else if (flag)
            continue;
        else if (!st.empty() && st.top() == mapping[ch])
            max_len += 2, st.pop();
        else
        {
            ans = max(max_len, ans), max_len = 0;
            while (!st.empty())
                st.pop();
            flag = true;
        }
    ans = max(ans, max_len);
    printf("%d", ans);
    return 0;
}