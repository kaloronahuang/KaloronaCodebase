// A.cpp
#include <bits/stdc++.h>
using namespace std;
string A, B;
int main()
{
    cin >> A >> B;
    if (A.length() != B.length())
        printf("No"), exit(0);
    for (int i = 0; i < A.length(); i++)
    {
        if (A[i] == 'a' || A[i] == 'e' || A[i] == 'i' || A[i] == 'o' || A[i] == 'u')
            if (!(B[i] == 'a' || B[i] == 'e' || B[i] == 'i' || B[i] == 'o' || B[i] == 'u'))
                printf("No"), exit(0);
        if (!(A[i] == 'a' || A[i] == 'e' || A[i] == 'i' || A[i] == 'o' || A[i] == 'u'))
            if ((B[i] == 'a' || B[i] == 'e' || B[i] == 'i' || B[i] == 'o' || B[i] == 'u'))
                printf("No"), exit(0);
    }
    printf("Yes");
    return 0;
}