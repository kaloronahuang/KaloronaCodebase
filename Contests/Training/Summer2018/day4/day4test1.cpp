// dynamic scduling
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/*
int main()
{
	int T;
	int marks[10000];
	memset(marks,0,sizeof(marks));
	int farthest;
	cin>>T;
	for(int i = 0;i<T;i++)
	{
		int pos;
		cin>>pos;
		marks[pos] = 1;
		farthest = pos;
	}
	
	int tower[T][farthest];
	memset(tower,0,sizeof(tower));
	for(int j = farthest - 1;j>-1;j--)
	{
		tower[T-1][j] = marks[j-1];
	}
	for(int i = T-1;i>-1;i--)
	{
		for(int j = farthest - 1;j>0;j--)
		{
			if(j==1)
				tower[i-1][j-1] += max(tower[i][j],tower[i][j-1]);
			else
				tower[i-1][j-1] += max(max(tower[i][j],tower[i][j-1]),tower[i][j-2]);
		}
	}
	
	for(int i = T-1;i>-1;i--)
	{
		for(int j = farthest - 1;j>0;j--)
		{
			if(j==1)
				tower[i-1][j-1] += max(tower[i][j],tower[i][j-1]);
			else
				tower[i-1][j-1] += max(max(tower[i][j],tower[i][j-1]),tower[i][j-2]);
		}
	}
	
	for(int x = 0;x<T;x++)
	{
		for(int y = 0;y<farthest;y++)
			cout<<tower[x][y]<<" ";
		cout<<endl;
	} 
	cout<<endl;
	
	
	cout<<tower[0][0]<<" ";
}
*/

int main()
{
	int T;
	cin>>T;
	int marks[T];
	int farthest = 0;
	for(int i = 0;i<T;i++)
	{
		cin>>marks[i];
		farthest = max(farthest, marks[i]);
	}
	
	int tower[T][farthest];
	memset(tower,0,sizeof(tower));
	for(int i = 0;i<T;i++)
	{
		//cout<<i<<" "<<marks[i]-1<<endl;
		tower[i][marks[i] - 1] = 1;
		//cout<<"TP1 passed"<<endl;
	}
	/*
	for(int x= 0;x<T;x++)
	{
		for(int y = 0;y<farthest;y++)
			cout<<tower[x][y]<<" ";
		cout<<endl;
	}
	*/
	//cout<<"TP1 passed"<<endl;
	for(int i = T-1;i>0;i--)
	{
		for(int k = farthest - 1;k>0;k--)
		{
			if(k == 1)
				tower[i-1][k-1] += max(tower[i][k],tower[i][k-1]);
			else
				tower[i-1][k-1] += max(max(tower[i][k],tower[i][k-1]),tower[i][k-2]);
		}
	}
	cout<<tower[0][0];
}
