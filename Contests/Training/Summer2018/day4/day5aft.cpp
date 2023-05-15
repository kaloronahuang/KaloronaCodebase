// dynamic scheduling
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
	int height;
	cin>>height;
	int matrix[height][height];
	for(int i = 0;i<height;i++)
	{
		for(int j = 0;j<i+1;j++)
		{
			cin>>matrix[i][j];
		}
	}
	
	for(int i = height - 1;i>0;i--)
	{
		for(int j = i;j>0;j--)
		{
			//cout<<matrix[i][j]<<" ";
			matrix[i-1][j-1] += max(matrix[i][j],matrix[i][j-1]);
		}
		//cout<<endl;
	}
	
	cout<<matrix[0][0];
}
