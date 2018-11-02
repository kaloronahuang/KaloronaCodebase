// P1019.cpp
#include <iostream>
#include <cstring>

using namespace std;

string mem[21][21];
char key;

string *words;
short *timeTable;
int range;

void generate()
{
	for(int i = 0;i<range;i++)
		for(int j = 0;j<range;j++)
		{
			string prev_wd = words[i];
			string back_wd = words[j];
			
			int st = prev_wd.length()-1;	int ed = 0;
			string storage;
			while(st > 0 && ed < back_wd.length()-1)
			{
				string pr,bk;
				pr = prev_wd.substr(st);
				bk = back_wd.substr(0,ed+1);
				if(pr == bk)
					storage = pr;
				st--;	ed++;
			}
			mem[i][j] = storage;
		}
}

string max(string a, string b)
{
	return (a.length()>b.length())?a:b;
}

bool isAllOccupied()
{
	for(int i = 0;i<range;i++)
		if(timeTable[i]!=2)
			return false;
	return true;	
}

string next(int curt)
{
	timeTable[curt]++;
	string ret = words[curt];
	
	if(isAllOccupied())
		return words[curt];
	
	for(int idx = 0;idx<range;idx++)
		if(timeTable[idx]<2&&mem[curt][idx]!="")
		{
			string gres = next(idx);
			string res = words[curt] + gres.substr(mem[curt][idx].length());
			ret = max(res, ret);
		}
	timeTable[curt]--;
	return ret;
}

string getLargest()
{
	string ret;
	for(int i = 0;i<range;i++)
		if(words[i][0] == key)
		{
			string res = next(i);
			ret = (ret.length()>res.length())?ret:res;
		}
	return ret;
}

void init()
{
	for(int i = 0;i<range;i++)
		timeTable[i] = 0;
}

int main()
{
	cin>>range;
	words = new string[range];
	timeTable = new short[range];
	init();
	for(int i = 0;i<range;i++)
		cin>>words[i];
	cin>>key;
	generate();
	cout<<getLargest();
	return 0;
}
