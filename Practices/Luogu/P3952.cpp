// P3952.cpp
#include <bits/stdc++.h>

using namespace std;

char content[1010], opt[20];
int T, L, complexity, vis[300];

struct instruction
{
    char typ, var_name[3];
    bool tag, tag2;
    int x, y;
    instruction()
    {
        typ = 0, memset(var_name, 0, sizeof(var_name));
        tag = tag2 = false;
        x = y = 0;
    }
};
stack<instruction> st;

int read()
{
    int pos = 1, ret = 0;
    while (opt[pos] != 0)
        ret = ret * 10 + opt[pos] - '0', pos++;
    return ret;
}

int main()
{
    //freopen("input.in", "r", stdin);
    scanf("%d", &T);
    while (T--)
    {
        memset(vis, 0, sizeof(vis));
        // complexity reader;
        complexity = 0;
        memset(opt, 0, sizeof(opt));
        scanf("%d%s", &L, opt + 1);
        if (strlen(opt + 1) == 4)
            complexity = (opt[3] == '1') ? 0 : 1;
        else
            for (int i = 5, siz = strlen(opt + 1); i <= siz - 1; i++)
                complexity = complexity * 10 + (opt[i] - '0');
        // read the whole content;
        int mx_idx = 0;
        bool err_flag = false;
        while (!st.empty())
            st.pop();
        for (int i = 1, curt_complexity = 0, choke = 0; i <= L; i++)
        {
            instruction ist;
            ist.tag = false, ist.tag2 = false;
            scanf("%s", content + 1);
            ist.typ = content[1];
            if (ist.typ == 'F')
            {
                scanf("%s", ist.var_name + 1);
                // repeated name;
                err_flag |= (vis[ist.var_name[1]] > 0);
                vis[ist.var_name[1]]++;
                // read the condition;
                scanf("%s", opt + 1);
                if (opt[1] == 'n')
                    ist.x = -1;
                else
                    ist.x = read();

                scanf("%s", opt + 1);
                if (opt[1] == 'n')
                    ist.y = -1;
                else
                    ist.y = read();

                if (ist.x != -1 && ist.y == -1)
                {
                    // O(n);
                    if (choke == 0)
                        curt_complexity++, ist.tag2 = true;
                }
                else if (ist.x == -1 && ist.y != -1)
                    choke++, ist.tag = true;
                else if (ist.x != -1 && ist.y != -1 && ist.x > ist.y)
                    choke++, ist.tag = true;

                st.push(ist);
            }
            else if (ist.typ == 'E')
            {
                if (st.empty())
                    // nowhere to go;
                    err_flag = true;
                else
                {
                    instruction current_ist = st.top();
                    if (current_ist.tag)
                        choke--;
                    if (current_ist.tag2)
                        curt_complexity--;
                    vis[current_ist.var_name[1]]--;
                    st.pop();
                }
            }
            mx_idx = max(mx_idx, curt_complexity);
        }
        err_flag |= (!st.empty());
        if (err_flag)
        {
            puts("ERR");
            continue;
        }
        puts(mx_idx == complexity ? "Yes" : "No");
    }
    return 0;
}