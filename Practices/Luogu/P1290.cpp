// P1290.cpp
#include <bits/stdc++.h>

using namespace std;

int Q;

bool play(int x, int y, int person)
{
    if (x == y)
        return person;
    if ((y / x) >= 2)
        return person;
    return play(y - x, x, person ^ 1);
}

int main()
{
    scanf("%d", &Q);
    while (Q--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x > y)
            swap(x, y);
        puts(play(x, y, 0) == false ? "Stan wins" : "Ollie wins");
    }
    return 0;
}