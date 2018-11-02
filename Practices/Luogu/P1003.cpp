#include <iostream>

struct carpet
{
    int a;
    int b;
    int xl;
    int yl;
};

int main()
{
    int N;
    std::cin >> N;
    carpet cs[N];
    // IO;
    for (int i = 0; i < N; i++)
        std::cin >> cs[i].a >> cs[i].b >> cs[i].xl >> cs[i].yl;
    int xd, yd;
    std::cin >> xd >> yd;
    int maxvalue = -1;
    for (int i = 0; i < N; i++)
    {
        carpet currentc = cs[i];
        if (currentc.a <= xd && currentc.b <= yd &&
            currentc.a + currentc.xl >= xd &&
            currentc.b + currentc.yl >= yd)
            maxvalue = i + 1;
    }
    std::cout << maxvalue;
    return 0;
}