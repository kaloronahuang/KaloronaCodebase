// day4 aft
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int D(int n)
{
	if(n == 1)
		return 0;
	else if(n == 2)
		return 1;
	else if(n == 3)
		return 2;
	else
		return (n-1)*(D(n-1)+D(n-2));
}

int levelMultiply(int n)
{
	if(n == 0)
		return 1;
	if(n == 1)
		return 1;
	if(n==2)
		return 2;
	if(n == 3)
		return 6;
	return n*levelMultiply(n-1);
}

int E(int n)
{
	int rightPart = 1;
	
	for(int i = 1;i<n+1;i++)
	{
		rightPart += (pow(-1,i)/levelMultiply(i));
	}
	
	return rightPart*levelMultiply(n);
}

double F(int n)
{
	return ( ( pow((1+sqrt(5))/2,n) - pow((1-sqrt(5))/2,n) ) / sqrt(5) );	
}

void rabbit()
{
	int times = 0;
	cin>>times;
	for(int t = 0;t<times;t++)
	{
		int xa,ya;
		cin>>xa>>ya;
		int xb,yb;
		cin>>xb>>yb;
		// special occ;
		if(xa == xb || ya == yb)
		{
			if(abs(xa - xb) == 1 || abs(ya - yb) == 1)
				cout<<"no";
			else
				cout<<"yes";
			continue;
		}
		// normal
		if(xa<xb)
		{ swap(xa,xb); swap(ya,yb); }
		bool ex_tree = false;
		for(int x = xa + 1;x<xb;x++)
		{
			if(
			((ya - yb) / (xa - xb))*x + (ya - ((ya - yb) / (xa - xb))*xa) - 
			floor(((ya - yb) / (xa - xb))*x + (ya - ((ya - yb) / (xa - xb))*xa))
			== 0
			) // k = (ya - yb) / (xa - xb); b = ya - k*xa;
			{
				ex_tree = true;
				break;
			}
		}
		if(ex_tree)
		{
			cout<<"yes"<<endl;
		}
		else
		{
			cout<<"no"<<endl;
		}
	}
}

int main()
{
	int n;
	cin>>n;
	cout<<fixed<<setprecision(2)<<F(n);
	return 0;
}
