// CH0802.cpp
#include <iostream>
#include <deque>
#include <map>
using namespace std;
struct card
{
    bool upper;
    int number;
};
deque<card> heap[15];
int ans[15];

void read()
{
    map<char, int> mapping;
    mapping['A'] = 1, mapping['J'] = 11, mapping['Q'] = 12, mapping['K'] = 13, mapping['0'] = 10;
    for (int i = 1; i <= 13; i++)
    {
        char key;
        for (int j = 1; j <= 4; j++)
        {
            scanf((j == 4) ? "%c \n" : "%c ", &key);
            int num;
            if ('0' < key && key <= '9')
                num = key - '0';
            else
                num = mapping[key];
            heap[i].push_back(card{false, num});
        }
    }
    return;
}

int main()
{
    read();
    int tot = 0;
    for (int tim = 0; tim < 4; tim++)
    {
        card curt = heap[13].back();
        heap[13].pop_back();
        while (curt.number != 13)
        {
            if (!curt.upper)
                ans[curt.number]++;
            curt.upper = true;
            heap[curt.number].push_back(curt);
            card tar = heap[curt.number].front();
            heap[curt.number].pop_front();
            curt = tar;
        }
    }
    int total = 0;
    for (int i = 1; i <= 12; i++)
        total += (ans[i] == 4) ? 1 : 0;
    printf("%d", total);
    return 0;
}