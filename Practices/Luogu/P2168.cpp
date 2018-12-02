// P2168.cpp
// tag:Huffman
#include <iostream>
#include <queue>
#include <cstdio>
#define ll long long
using namespace std;
const int maxn = 100200;
ll n, k, weights[maxn];
priority_queue<int> seq;

int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &weights[i]), seq.push(weights[i]);
    int numOfZero = 
    return 0;
}