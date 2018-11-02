// day6:mor:string
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

bool isSnakeShape(string str)
{
	// odd;
	for(int i = 0;i<(int)(str.length()/2);i++)
	{
		int end = str.length() - i - 1;
		if(str[i] != str[end])
			return false;
	}
	return true;
}

int main()
{
	/*
	string str;
	cin>>str;
	if(str.length()%2)
	{
		cout<<str.length();
		return 0;
	} 
	int i = 1; 
	int standard = (log(str.length())/log(2));
	for(i = 1;i<standard+1;i++)
	{
		if(!isSnakeShape(str.substr(0,str.length()/i)))
		{
			break;
		}
	}
	cout<<str.length()/i;
	return 0;
	*/
	
	/*
	int *p;
	cout<<sizeof(p);
	return 0;
	*/
}
