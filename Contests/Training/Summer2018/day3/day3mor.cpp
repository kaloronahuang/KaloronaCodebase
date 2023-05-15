#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <string>
#include <sstream>
#include <set>

using namespace std;

void stringSearch()
{
	string wordFinding;
	string article;
	getline(cin,wordFinding);
	getline(cin,article);
	
	transform(wordFinding.begin(),wordFinding.end(),wordFinding.begin(),::tolower);
	transform(article.begin(),article.end(),article.begin(),::tolower);
	int firstpos = article.find(wordFinding);
	int counter = 0;
	if(firstpos != -1)
	{
		int pos = 0;
		for(;;)
		{
			int pos_ = article.find(wordFinding,pos);
			if(pos_ != -1)
			{
				// judge if it is a word;
				if(pos_>0)
				{
					if(article[pos_-1] == ' ' && article[pos_ + wordFinding.length()] == ' ')
					{
						counter++;
					}	
				}
				else
					if(article[pos_ + wordFinding.length()] == ' ')
						counter++;
				
						
				pos = pos_ + wordFinding.length() - 1;	
			}
			else
				break;
		}
		if(counter>0)
			cout<<counter<<" ";
	} 
	if(counter == 0)
		cout<<-1;
	else
		cout<<firstpos;
}

bool isRepeated(string a);

void ex1()
{
	// input;
	string input;
	getline(cin,input);
	transform(input.begin(),input.end(),input.begin(),::tolower);
	
	// for to search;
	int str_length = 0;
	for(int i = 0;i<input.length();i++)
	{
		for(int j = 1;j<input.length()-i;j++)
		{
			if(!isRepeated(input.substr(i,j)))
				str_length = max(str_length,j);
		}
	}
	cout<<str_length;
}

bool isRepeated(string a)
{
	for(int i = 0;i < a.length();i++)
	{
		for(int j = 0;j < a.length();j++)
		{
			if(i!=j && a[i] == a[j])
				return true;
		}
	}
	return false;
}

string to_string(int i)
{
	ostringstream os;
	os<<i;
	return os.str();
}

void ex2()
{
	int num;
	string numstr;
	bool negative;
	
	cin>>num;
	numstr = to_string(num);
	negative = num<0;
	if(negative)
		numstr = numstr.substr(1,numstr.length()-1);
	if(num == 0)
		cout<<"0";
	string rev_str = "";
	bool isN = false;
	for(int i = 0;i<numstr.length();i++)
	{
		char current = numstr[numstr.length() - 1 - i];
		if(current != '0')
			isN = true;
		if(isN)
		{
			rev_str += current;	
		}
	}
	if(negative)
		rev_str = "-" + rev_str;
	cout<<rev_str;
}

set<string> ss;
string str;

void looping(int fix)
{
	if(fix == str.length())
		return;
	for(int j = fix;j<str.length();j++)
	{
		looping(j+1);
		string s_ = str;
		swap(str[j],str[fix]);
		ss.insert(s_);
	}
}

int main()
{
	cin>>str;
	ss.insert(str);
	looping(0);
	for(set<string>::iterator i = ss.begin();i!=ss.end();i++)
		cout<<*i<<endl;
	return 0;
} 
