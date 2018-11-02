#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

//11

struct Jew
{
	int price;
	bool avaliable;
};

int Jewery()
{
	int w,n;
	cin>>w>>n;
	Jew j[n];
	
	for(int index = 0;index < n;index++)
	{
		cin>>j[index].price;
		j[index].avaliable = false;
	}
	
	
	// sorting
	for(int i = 0;i<n-1;i++)
	{
		for(int x = 0;x<n-1-i;x++)
		{
			if(j[x].price>j[x+1].price)
				swap(j[x],j[x+1]); 
		}
	}
	
	// groups;
	int groups = 0;
	int start = 0;
	int end=n-1;
	for(;start < end;start++)
	{
		for(;end>start;)
		{
			if(j[start].price+j[end].price<w)
			{
				groups++;
				end--;
				break;
			}
			else
			{
				groups++;
				end--;
			}
		}
	}
	
	cout<<groups;
	
	return 0;
}

int lineWater()
{
	int n;
	cin>>n;
	int Ti[n];
	int in[n];
	for(int i = 0;i<n;i++)
	{
		cin>>Ti[i];
		in[i] = i;
	} 
	
	for(int x = 0;x<n-1;x++)
	{
		for(int y = 0;y<n-1-x;y++)
		{
			if(Ti[y]>Ti[y+1])
			{
				swap(Ti[y],Ti[y+1]);
				swap(in[y],in[y+1]);
			}
		}
	}
	
	int total = 0;
	
	for(int index = 0;index<n;index++)
	{
		cout<<in[index]+1<<" ";
		total+=(Ti[index]*(9-index));
	}
	
	cout<<endl<<(float)total / n;
}

struct student{
	char name[40];
	int year;
	int month;
	int day;
};

bool comp(student a, student b)
{
	if(a.year != b.year)
		return (a.year < b.year);
	else
		if(a.month != b.month)
			return (a.month<b.month);
		else
			if(a.day != b.day)
				return (a.day<b.day);
			else
				return false;
}

int birthdaySort()
{
	int num;
	cin>>num;
	student stu[num];
	for(int index = 0;index<num;index++)
	{
		cin>>stu[index].name;
		cin>>stu[index].year;
		cin>>stu[index].month;
		cin>>stu[index].day;
	}
	sort(stu,stu+num,comp);
	for(int i = 0;i<num;i++)
	{
		cout<<stu[i].name<<endl;
	}
}

struct expoVolun{
	int ID;
	int score;
};

bool compExpo(expoVolun a, expoVolun b)
{
	if(a.score!=b.score)
	return (a.score>b.score);
	
	return a.ID<b.ID;
}

void expo()
{
	int n,m;
	cin>>n;
	cin>>m;
	
	expoVolun ev[n];
	for(int index = 0;index < n;index++)
	{
		cin>>ev[index].ID;
		cin>>ev[index].score;
	}
	
	sort(ev,ev+n,compExpo);
	int messure = ev[(int)(m*1.5)].score;
	cout<<messure<<" "<<m<<endl;
	for(int j = 0;j<n;j++)
		if(ev[j].score>=messure)
			cout<<ev[j].ID<<" "<<ev[j].score<<endl;
}

int levelMultiply(int base)
{
	int total = 1;
	for(int i = 1;i<=base;i++)
	{
		total*=i;
	}
	return total;
}

void levelMultiplyJudge()
{
	int m;
	cin>>m;
	int lm_table[10];
	for(int index = 1;index<11;index++)
	{
		lm_table[index-1] = levelMultiply(index);
	}
	
	for(int x = 0;x<m;x++)
	{
		int current;
		cin>>current;
		bool isIt = false;
		for(int i = 9;i>-1;i--)
		{
			if(current>=lm_table[i])
				current-=lm_table[i];
			if(current == 0)
			{
				cout<<"Yes";
				isIt = true;
			}
		}
		if(!isIt)
			cout<<"No";
	}
}

void ChessGame()
{
	int N,K;
	cin>>N>>K;
	
	int elements[N];
	for(int index = 0;index<N;index++)
	{
		cin>>elements[index];
	}
	sort(elements,elements+N);
	int ele[N-1];
	for(int i = 0;i<N-1;i++)
	{
		ele[i] = elements[i+1] - elements[i];
	}
	sort(ele,ele+N-1);
	int total = 0;
	for(int j = 0;j<K;j++)
	{
		total += ele[j];
	}
	cout<<total;
}

int main()
{
	ChessGame();
	return 0;
} 
