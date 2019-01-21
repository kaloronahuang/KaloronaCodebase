// A.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
bool box[10010];
vector<int> vec;
int main()
{
    memset(box, true, sizeof(box));
    box[1] = false;
    for (int i = 2; i < 10010; i++)
        if (box[i])
        {
            for (int j = 2; j * i < 10010; j++)
                box[i * j] = false;
            if (i >= 2000)
                vec.push_back(i);
        }
    int T, k;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &k);
        k--;
        int loc = k % 6, year = vec[k / 6];
        string res;
        switch (loc)
        {
        case 0:
            res = "01-10";
            break;
        case 1:
            res = "02-20";
            break;
        case 2:
            res = "03-30";
            break;
        case 3:
            res = "10-01";
            break;
        case 4:
            res = "11-11";
            break;
        case 5:
            res = "12-21";
            break;
        }
        printf("%d-%s\n", year, res.c_str());
    }
    return 0;
}