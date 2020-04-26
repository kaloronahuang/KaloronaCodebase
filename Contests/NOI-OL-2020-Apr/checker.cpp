// checker.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    while (true)
    {
        system("./gen.out > testcase.in");
        system("./color_bf.out < testcase.in > testcase.ans");
        system("./color.out < testcase.in > testcase.out");
        if (system("diff testcase.out testcase.ans"))
        {
            puts("FUCK");
            break;
        }
        else
            puts("Accepted");
    }
    return 0;
}