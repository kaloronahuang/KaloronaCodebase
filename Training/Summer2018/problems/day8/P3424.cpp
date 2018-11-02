#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int F(int x)
{
    if (x == 0)
        return 1;
    if (x == 1)
        return 1;
    if (x == 2)
        return 2;
    if (x == 3)
        return 3;
    return F(x - 1) + F(x - 2);
}

int main()
{
    int xl, yl;
    int xacc, yacc;
    xacc = yacc = 0;
    cin >> xl;
    int xs[xl];
    for (int i = 0; i < xl; i++)
    {
        cin >> xs[i];
        xacc += F(i + 1) * xs[i];
    }
    cin >> yl;
    int ys[yl];
    for (int i = 0; i < yl; i++)
    {
        cin >> ys[i];
        yacc += F(i + 1) * ys[i];
    }
    int account = xacc + yacc;
    int tmp = account;
    vector<int> result;
    int backNum = 20;
    int currentPos;
    bool found = false;
findFirstDigit:
    for (int pos = backNum - 1; pos > -1; pos--)
    {
        // first digit;
        if (F(pos) < tmp && F(pos + 1) > tmp)
        {
            currentPos = pos;
            tmp -= F(pos);
            goto search;
        }
        if (F(pos) == tmp)
        {
            result.resize(pos - 1, 0);
            result.push_back(1);
            goto print;
        }
    }

search:
    for (int i = currentPos - 1; i > -1; i--)
    {
        for (int digit = 0; digit < 10; digit++)
        {
            if (F(i)*digit < tmp && tmp < F(i + 1)*digit)
            {
                tmp -=F(i);
                result[i] = digit;
                i--;
                found=true;
                break;
            }
        }
    }

    if (!found)
    {
        result.resize(0);
        backNum = currentPos;
        goto findFirstDigit;
    }

print:
    for (int j = 0; j < result.size(); j++)
    {
        cout << result[j];
        if (j != result.size() - 1)
            cout << " ";
    }

    return 0;
}