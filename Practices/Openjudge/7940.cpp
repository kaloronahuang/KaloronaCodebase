#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    // basic I/O;
    int N;
    cin >> N;
    int arr[N];
    for (int i = 0; i < N; i++)
        cin >> arr[i];
    sort(arr, arr + N);
    int M;
    cin >> M;
    int query[M];
    for (int i = 0; i < M; i++)
        cin >> query[i];
    // start to go;

    for (int j = 0; j < M; j++)
    {
        int currentQuery = query[j];
        int standard = 0;
        int s, e;
        s = 0;
        e = N - 1;
        bool toGo = false;
        while (s + 1 < e)
        {
            standard = arr[(int)((s + e) / 2)];
            if (currentQuery == standard)
            {
                cout << currentQuery;
                toGo = true;
                break;
            }
            if (currentQuery < standard) // left;
            {
                e = (int)((s + e) / 2);
            }
            else // right;
            {
                s = (int)((s + e) / 2);
            }
        }
        if (!toGo)
        {
            if (abs(arr[s] - currentQuery) > abs(arr[e] - currentQuery))
                cout << arr[e];
            else if (abs(arr[s] - currentQuery) == abs(arr[e] - currentQuery))
                cout << min(arr[e], arr[s]);
            else
                cout << arr[s];
        }
        if (j != M - 1)
            cout << endl;
    }
    return 0;
}