// 9273 on noi.openjudge.com
#include <iostream>
#include <vector>

using namespace std;

int cnt = 0;
int standard = 0;
int full_length = 0;

// 0 means short;
// 1 means more;
// 3 means decent;
int isValidiate()
{
    int acc = full_length;
    if (acc > standard)
        return 1;
    if (acc < standard)
        return 0;
    return 3;
}

void getPossible()
{
    if (isValidiate() == 0)
    {
        // do process;
        // add 1 or 2 or 3;
        full_length += 1;
        getPossible();
        full_length -= 1;
        int tmpcnt = cnt;
        full_length += 2;
        getPossible();
        full_length -= 2;
        if(cnt == tmpcnt)
            return;
        full_length += 2;
        getPossible();
        full_length -= 2;
        return;
    }
    else if (isValidiate() == 1)
    {
        return;
    }
    cnt++;
}

int main()
{
    int target;
    while(cin>>target)
    {
        standard = target;
        getPossible();
        cout<<cnt<<endl;
        cnt = 0;
    }
    return 0;
}