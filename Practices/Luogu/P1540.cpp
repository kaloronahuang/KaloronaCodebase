// P1540;
#include <iostream>
#include <cstring>

int main()
{
    // start to do I/O;
    int memsize;
    int wordNum;
    std::cin >> memsize >> wordNum;
    int wl[wordNum];
    for (int i = 0; i < wordNum; i++)
        std::cin >> wl[i];
    // memdef;
    int mem[memsize];
    memset(mem, -1, sizeof(mem));
    int cnt = 0;
    int mempos = 0;
    // go to search;
    for (int i = 0; i < wordNum; i++)
    {
        bool toCheck = false;
        for (int j = 0; j < memsize; j++)
        {
            if (wl[i] == mem[j])
            {
                toCheck = true;
                break;
            }
        }
        if (toCheck)
            continue;
        mem[mempos % memsize] = wl[i];
        cnt++;
        mempos++;
    }
    std::cout << cnt;
    return 0;
}