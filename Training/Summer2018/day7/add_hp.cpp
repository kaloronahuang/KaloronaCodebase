// A+B problem
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

string rev(string a)
{
	string ret = "";
	for(int i = a.length() - 1;i>-1;i--)
	{
		//cout<<i<<endl;
		ret = ret + a[i];
		//cout<<i<<endl; 
	}
	return ret;
}

int main()
{
	string a;
	string b;
	getline(cin,a);
	getline(cin,b);
	a=rev(a); b = rev(b);
	if(a.length()<b.length())
		swap(a,b);
	int moreBit[max(a.length(),b.length())+1];
	memset(moreBit,0,sizeof(moreBit));
	string str = "";
	for(int i = 0;i<=a.length();i++)
	{
		str+='0';
	}
	for(int i = 0;i<=a.length();i++)
	{
		int currenta;
		int currentb;
		if(i>=a.length())
		{
			currenta = 0;
		}
		else
		{
			currenta = a[i] - '0';
		}
		if(i>=b.length())
		{
			currentb = 0;
		}
		else
		{
			currentb = b[i] - '0';
		}
		int res = currenta + currentb + moreBit[i];
		int ge = res%10;
		int shi = (int)(res/10);
		moreBit[i+1] = shi;
		str[i] = '0' + ge;
	}
	bool toShowZero = false;
	for(int i = 0;i<str.length();i++)
		if(toShowZero == true)
			cout<<str[str.length() - i - 1];
		else
		{
			if(str[str.length() - i - 1] != '0')
			{
				toShowZero = true;
				cout<<str[str.length()-i-1];
			}
		} 
}
