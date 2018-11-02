// P1052.cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 400000;
const int maxm = 1000;
const int INF = 0x7fffffff;
// positions of stones;
int stone[maxm];
// used for DP;
int F[maxn];
// the distance between 2 stones;
int diff[maxn];
// flag[pos] to indicate whether there is a stone at pos;
bool flag[maxn];
int L, S, T, M;

void DP()
{
    // start loop to the farthest;
    for (int i = 1; i <= L + T; i++)
        for (int k = S; k <= T; k++)
        {
            // to transform from F[i-k];
            // k is the step number;
            if (i - k >= 0)
                F[i] = min(F[i], F[i - k]);
            // if there is a stone, count it!
            F[i] += (flag[i]) ? 1 : 0;
        }
}

int main()
{
    // input;
    cin >> L >> S >> T >> M;
    for (int i = 1; i <= M; i++)
        cin >> stone[i];
    sort(stone + 1, stone + M + 1);
    diff[0] = 0;
    // to calc and zip with the distances;
    for (int i = 1; i <= M; i++)
        diff[i] = (stone[i] - stone[i - 1]) % 2520;
    // to update the shortened distances and the flag[];
    for (int i = 1; i <= M; i++)
        stone[i] = stone[i - 1] + diff[i], flag[stone[i]] = true;
    L = stone[M];
    // to init for the F;
    for (int i = 0; i <= L + T; i++)
        F[i] = M;
    F[0] = 0;
    // Start to DP();
    DP();
    // to figure out the ans;
    int ans = M;
    for (int i = L; i < L + T; i++)
        ans = min(ans, F[i]);
    // output;
    cout << ans;
    return 0;
}