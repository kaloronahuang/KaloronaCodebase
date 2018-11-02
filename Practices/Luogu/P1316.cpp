// P1316.cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 100010;
long long A, B;
long long arr[maxn];

bool check(long long num)
{
	long long last = arr[0];
	long long cnt = 1;
	for (long long i = 1; i < A; i++)
		if (arr[i] - last >= num)
			cnt++, last = arr[i];
	if (cnt >= B)
		return true;
	return false;
}

int main()
{
	cin >> A >> B;
	for (int i = 0; i < A; i++)
		cin >> arr[i];
	sort(arr, arr + A);
	long long l = 0;
	long long r = arr[A - 1] - arr[0];
	long long ans = 0;
	while (l <= r)
	{
		long long mid = (l + r) / 2;
		if (check(mid))
			l = mid + 1;
		else
			r = mid - 1;
	}
	cout << l - 1;
	return 0;
}