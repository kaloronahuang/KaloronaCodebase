#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

#define integer __int128

integer powTable[81];

integer max(integer a, integer b)
{
    if (a > b)
        return a;
    return b;
}

integer min(integer a, integer b)
{
    if (a < b)
        return a;
    return b;
}

void prePow()
{
    powTable[0] = 1;
    powTable[1] = 2;
    powTable[2] = 4;
    for (int i = 3; i < 80; i++)
        powTable[i] = 2 * powTable[i - 1];
}

int row, col;
int *line;

integer DPTable[90][90];
unsigned char DPStatus[90][90];

short currentDay = 1;

integer DP(int startPos, int endPos)
{
	int times = col - (endPos-startPos);
    if (DPStatus[startPos][endPos] == currentDay)
        return DPTable[startPos][endPos];
    if (endPos - startPos == 1)
    {
        DPTable[startPos][endPos] =
            max(line[startPos], line[endPos]) * powTable[times + 1] +
            min(line[startPos], line[endPos]) * powTable[times];
        DPStatus[startPos][endPos] = currentDay;
        return DPTable[startPos][endPos];
    }
    integer st = line[startPos] * powTable[times] + DP(startPos + 1, endPos);
    integer ed = line[endPos] * powTable[times] + DP(startPos, endPos - 1);
    integer res = max(st, ed);
    DPTable[startPos][endPos] = res;
    DPStatus[startPos][endPos] = currentDay;
    return res;
}

integer DoDP()
{
    return DP(0, col - 1);
}

void print(integer in)
{
    integer copyed = in;
    string str;
    for (int i = 0; i < 100; i++)
    {
        if (copyed == 0)
            break;
        str += '0' + copyed % 10;
        copyed = (integer)(copyed / 10);
    }
    if (str == "")
        str = "0";
    reverse(str.begin(), str.end());
    cout << str;
}

int main()
{
    prePow();
    memset(DPStatus, 0, sizeof(DPStatus));
    cin >> row >> col;
    if (row == 1 && col == 1)
    {
        int a;
        cin >> a;
        print((integer)(a * 2));
        return 0;
    }
    integer ret = 0;

    for (int i = 0; i < row; i++)
    {
        int arr[col];
        for (int j = 0; j < col; j++)
            cin >> arr[j];
        line = arr;
        ret = ret + DoDP();
        currentDay++;
    }
    print(ret);
    return 0;
}
