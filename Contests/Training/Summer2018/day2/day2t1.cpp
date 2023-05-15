#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
	// i.e. 1
	/*
	int NumOfCards;
	cin>>NumOfCards;
	// A&B, A first
	int pivot = NumOfCards % 4;
	if(pivot == 0)
		cout<<"The first wins;"<<endl;
	else
		cout<<"The second wins"<<endl;
	*/
	// i.e. 2
	/*
	int NumOfCards, maxCards, minCards;
	cin>>NumOfCards>>maxCards>>minCards;
	if(NumOfCards%(maxCards+minCards)!=0)
		cout<<"The First wins;";
	else
		cout<<"The second wins;";
	return 0;
	*/
	
	/*
	for(;;)
	{
		int M,N;
		cin>>M>>N;
		if(M%(1+N) == 0)
			cout<<"Second;";
		else
			cout<<"First;";
	}
	return 0;
	*/
	
	// 
	// for(;;) { int M,N; cin>>M>>N; if(M%2 == 0 || N%2==0) cout<<"A"<<endl; else cout<<"B"endl; } return 0;

	// Circle question:
	/*
	int A,B,R;
	cin>>A>>B>>R;
	
	if(A<2*R || B<2*R)
		cout<<"Bob wins";
	else
		cout<<"Alice wins";
	return 0;
	*/
	
	int N,M;
	cin>>N>>M;
	
	// judge it;
	if(M>=N)
	{
		for(int i = N;i<= M;i++)
			cout<<i<<" ";
	}
	else
		if(N%(1+M)==0)
			cout<<"none"<<endl;
		else
			cout<<(N%(1+M))<<endl;
	
	return 0;
} 
