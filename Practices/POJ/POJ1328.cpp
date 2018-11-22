// POJ1328.cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 1010;
struct point
{
	double x, y;
	bool operator<(const point &pt) const
	{
		return x < pt.x;
	}
} stall[maxn], ranges[maxn];

int main()
{
	int cnt = 1;
	while (true)
	{
		int n, d;
		bool flag = false;
		scanf("%d%d", &n, &d);
		if (n == d && d == 0)
			return 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%lf%lf", &stall[i].x, &stall[i].y);
			if (stall[i].y > d)
				flag = true;
		}
		if (flag)
		{
			printf("Case %d: %d\n", cnt++, -1);
			continue;
		}
		sort(stall + 1, stall + n + 1);
		for (int i = 1; i <= n; i++)
		{
			double tmp = sqrt(pow(d, 2) - pow(stall[i].y, 2));
			ranges[i] = point{stall[i].x - tmp, stall[i].x + tmp};
		}
		sort(ranges + 1, ranges + n + 1);
		int ans = 0;
		for (int i = 1; i <= n; i++)
		{
			ans++;
			double curtstd = ranges[i].y;
			for (int j = i + 1; j <= n; j++)
				if (ranges[j].x <= curtstd)
				{
					if (ranges[j].y < curtstd)
						curtstd = ranges[j].y;
					i++;
				}
				else
					break;
		}
		printf("Case %d: %d\n", cnt++, ans);
	}
	return 0;
}