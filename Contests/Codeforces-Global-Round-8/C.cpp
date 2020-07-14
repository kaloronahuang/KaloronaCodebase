// C.cpp
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int n;
vector<pii> box;

int main()
{
    scanf("%d", &n), n++;
    int bx = 0;
    for (int i = 1; i <= n; i++, bx += 2)
        if (i & 1)
        {
            box.push_back(make_pair(bx, 0));
            box.push_back(make_pair(bx, 1));
            box.push_back(make_pair(bx, 2));

            box.push_back(make_pair(bx + 1, 0));
            box.push_back(make_pair(bx + 1, 2));

            box.push_back(make_pair(bx + 2, 0));
            box.push_back(make_pair(bx + 2, 1));
            box.push_back(make_pair(bx + 2, 2));
        }
        else
        {
            box.push_back(make_pair(bx, 2));
            box.push_back(make_pair(bx, 3));
            box.push_back(make_pair(bx, 4));

            box.push_back(make_pair(bx + 1, 2));
            box.push_back(make_pair(bx + 1, 4));

            box.push_back(make_pair(bx + 2, 2));
            box.push_back(make_pair(bx + 2, 3));
            box.push_back(make_pair(bx + 2, 4));
        }
    sort(box.begin(), box.end()), box.erase(unique(box.begin(), box.end()), box.end());
    printf("%d\n", int(box.size()));
    for (pii x : box)
        printf("%d %d\n", x.first, x.second);
    return 0;
}