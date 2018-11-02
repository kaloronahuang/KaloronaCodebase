#include <iostream>
#include <string>
#include <cmath>
using namespace std;

bool isSnakeShape(string str)
{
	int i = 0; int j = str.length()-1;
	for(;;)
	{
		if(str[i] != str[j])
			return true;
		if(i == j - 1)
			break;
		i++; j--;
	}
	return true;
}

int main()
{
	int setNum;
	cin>>setNum;
	for(int i = 0;i<setNum;i++)
	{
		string strs;
		cin>>strs;
		int times = 0;
		if(strs.length() == 1)
		{
			cout<<"1"<<endl;
			continue;
		}
		for(int j = 1;j<log(strs.length())/log(2);j++)
		{
			if(isSnakeShape(strs.substr(0,strs.length()/pow(2,j)))) times++;
			else break;
		}
		cout<<times<<endl;
	}
} 
