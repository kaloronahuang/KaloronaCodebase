#include <iostream>
#include <algorithm>
using namespace std;

struct StudentInfo
{
	int ID;
	int chs;
	int mat;
	int eng;
	int total;
};

int main()
{
	int n;
	cin>>n;
	
	StudentInfo si[n];
	
	for(int i = 0;i<n;i++)
	{
		si[i].ID = i+1;
		cin>>si[i].chs;
		cin>>si[i].mat;
		cin>>si[i].eng;
		si[i].total = si[i].chs + si[i].mat + si[i].eng;
	}
	
	// sort
	for(int x=0;x<n-1;x++)
	{
		for(int y=0;y<n-1-x;y++)
		{
			if(
			(si[y].total<si[y+1].total) ||
			(si[y].total == si[y+1].total && si[y].chs<si[y+1].chs) ||
			(si[y].total == si[y+1].total && si[y].chs==si[y+1].chs && si[y].ID<si[y+1].ID)
			 )
			{
				swap(si[y],si[y+1]);
			}
		}
	}
	
	for(int j = 0;j<5;j++)
	{
		cout<<si[j].ID<<" "<<si[j].total<<endl;
	}
	return 0;
}
