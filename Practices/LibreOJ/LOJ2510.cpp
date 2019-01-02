// LOJ2510.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MX_N = 20020;
int n, head[MX_N];
struct edges
{
    int to, nxt;
} edges[MX_N];
struct node
{
    int cityId, villageId;
    int ai, bi, ci;
} nodes[MX_N];
int main()
{
    scanf("%d", &n);
    return 0;
}