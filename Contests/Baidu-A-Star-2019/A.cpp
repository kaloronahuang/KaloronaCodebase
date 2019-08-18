// A.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int V, X = 0;
        scanf("%d", &V);
        int tmp = V;
        while (tmp)
            X += tmp % 10, tmp /= 10;
        vector<int> vec;
        for (int i = 1; i <= X; i++)
            if (X % i == 0 && V % i == 0)
                vec.push_back(i);
        printf("%d\n", vec.size());
        for (int i = 0, siz = vec.size(); i < siz - 1; i++)
            printf("%d ", vec[i]);
        printf("%d\n", vec[vec.size() - 1]);
    }
    return 0;
}