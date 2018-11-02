// P1316.cpp
#include <iostream>
#include <algorithm> 
using namespace std;

int axis[100010];
int n,acb;

int find(int desire, int st, int ed)
{
	if(desire > axis[n-1])
		return -1;
	int mid = (st+ed)/2;
	if(mid>=n)
		int a = 0; 
	int mid_val = axis[mid];
	if(ed - st == 1)
		return ed;
	if(desire == mid_val)
		return mid;
	else if(desire > mid_val)
		return find(desire, mid+1, ed);
	else
		return find(desire, st, mid);
}

int getBiggerThanNum(int bias) 
{
	int standard = axis[bias] - axis[0];
	int last = bias;
	int ans = 2;
	int l = bias;	int r = n-1;
	while(true)
	{
		int res = find(axis[last] + standard, l, r);
		if(res==-1)
			break;
		else
		{
			ans++;
			l = res+1;
			r = n-1;
			last = res; 
		}
	}
	return ans;
}

int main()
{
	cin>>n>>acb;
	for(int i = 0;i<n;i++)
		cin>>axis[i];
	sort(axis,axis+n);
	int ans = 0;
	for(int i = 1;i<n;i++)
		if(getBiggerThanNum(i)>=acb)
			ans = max(ans,i);
	cout<<(axis[ans]-axis[0]);
	return 0;
}
