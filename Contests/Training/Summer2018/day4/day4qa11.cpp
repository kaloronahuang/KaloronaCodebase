#include <iostream>
#include <algorithm>

using namespace std;

struct hw
{
	int timeCost = 0;
	int hwValue = 0;
	float ratio;
};

hw calc(hw h)
{
	h.ratio = (h.hwValue / h.timeCost);
	return h;
}

bool complm(hw a,hw b)
{
	return (a.ratio>b.ratio);
}

int main()
{
	int N,M,K,R;
	cin>>N>>M>>K>>R;
	int ets[N];
	hw hs[M];
	for(int i = 0;i<N;i++)
		cin>>ets[i];
	for(int i = 0;i<M;i++)
		cin>>hs[i].timeCost;
	for(int i = 0;i<M;i++)
		cin>>hs[i].hwValue;
	for(int i = 0;i<M;i++)
		hs[i].ratio = (hs[i].hwValue / hs[i].timeCost);
	
	sort(hs,hs+M,complm);
	int totalTime = 0;
	int scores = 0;
	for(int i = 0;i<M;i++)
	{
		totalTime += hs[i].timeCost;
		scores += hs[i].hwValue;
		
		if(scores>=K)
			break;
	}
	
	sort(ets,ets+N);
	int est_count = 0;
	for(int i = 0;i<N;i++)
	{
		if(totalTime + ets[i] > R)
			break;
		else
		{
			totalTime +=ets[i];
			est_count++;
		}
	}
	
	cout<<est_count;
}
