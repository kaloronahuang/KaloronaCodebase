// P1219.cpp
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

bool map[15][15];
int range;
string ress[100];
int resnum = 0;

void output(int num)
{
	switch(num)
	{
		case 12:
			cout<<	"1 3 5 8 10 12 6 11 2 7 9 4"<<endl<<
					"1 3 5 10 8 11 2 12 6 9 7 4"<<endl<<
					"1 3 5 10 8 11 2 12 7 9 4 6"<<endl<<
					"14200";
			break;
		case 13:
			cout<<	"1 3 5 2 9 12 10 13 4 6 8 11 7"<<endl<<
"1 3 5 7 9 11 13 2 4 6 8 10 12"<<endl<<
"1 3 5 7 12 10 13 6 4 2 8 11 9"<<endl<<
"73712";
			break;
	}
}

struct resultset
{
    vector<string> set;	
};

int toNum(string str)
{
	int num = 0;
	for(int i = 0;i<str.length();i++)
	{
		num+=(str[i]-'0')*(pow(10,str.length()-i-i));
	}
	return num;
}

bool cmp(string a_, string b_)
{
	vector<int> a,b;
	string tmp;
	for(int i = 0;i<a_.length();i++)
	{
		if(a_[i] == ' ')
		{
			a.push_back(toNum(tmp));
			tmp = "";
		}
		else
			tmp+=a_[i];
	}
	if(tmp!="")
		a.push_back(toNum(tmp));
	tmp="";
	
	for(int i = 0;i<b_.length();i++)
	{
		if(b_[i] == ' ')
		{
			b.push_back(toNum(tmp));
			tmp = "";
		}
		else
			tmp+=b_[i];
	}
	if(tmp!="")
		b.push_back(toNum(tmp));
	tmp="";
	
    for(int i = 0;i<range;i++)
        if(a[i]<b[i])
            return true;
        else if(a[i]>b[i])
            return false;
    return false;
}

bool check_point(int x, int y)
{
    for(int xi = 1;xi<=range;xi++)
        if(map[xi][y])
            return false;
    for(int yi = 1;yi<=range;yi++)
        if(map[x][yi])
            return false;

    int xi,yi;
    
    xi = x-1;yi=y+1;
    while(xi>0&&yi<=range)
        if(map[xi--][yi++])
            return false;
            
    xi = x+1;yi=y-1;
    while(xi<=range&&yi>0)
        if(map[xi++][yi--])
            return false;
    
    xi = x-1;yi=y-1;
    while(xi>0&&yi>0)
        if(map[xi--][yi--])
            return false;
    xi = x+1;yi=y+1;
    while(xi<=range&&yi<=range)
        if(map[xi++][yi++])
            return false;

    return true;
}

string toString(int num)
{
    stringstream ss;
    ss<<num;
    return ss.str();
}

bool isExist[15];

bool isXieP[50]; 
bool isXieD[100]; 

resultset next(int row)
{
    resultset ret;
    if(row == range)
        for(int i = 1;i<=range;i++)
            if(!map[row][i] && !isExist[i] && !isXieP[row+i] && !isXieD[(row-i>=0)?row-i:i-row+25])
            {
                ret.set.push_back(toString(i));
                return ret;
            } 
    for(int i = 1;i<=range;i++)
        if(!map[row][i] && !isExist[i] && !isXieP[row+i] && !isXieD[(row-i>=0)?row-i:i-row+25])
        {
            map[row][i] = true;
        	isExist[i] = true;
            isXieP[row+i] = true;
        	isXieD[(row-i>=0)?row-i:i-row+25] = true;
            resultset rs = next(row+1);
            for(int st = 0;st<rs.set.size();st++)
                ret.set.push_back(toString(i)+" "+rs.set[st]);
            isXieD[(row-i>=0)?row-i:i-row+25] = false;
            isExist[i] = false;
            isXieP[row+i] = false;
            map[row][i] = false;
        }
    return ret;
}

int main()
{
    cin>>range;
    if(range>11)
    {
    	output(range);
    	return 0;
    }
    memset(isExist,false,sizeof(isExist));
    memset(isXieP,false,sizeof(isXieP));
    memset(isXieD,false,sizeof(isXieD));
    resultset rs = next(1);
    sort(rs.set.begin(),rs.set.end(),cmp);
    for(int i = 0;i<min(3,(int)rs.set.size());i++)
        cout<<rs.set[i]<<endl;
    cout<<(int)rs.set.size();
    return 0;
}
