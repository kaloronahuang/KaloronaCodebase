#include <iostream>
#include <vector>
using namespace std;

vector<int> expr;

void debug_log()
{
	cout<<"Log:"<<endl;
	for(int e = 0;e<expr.size();e++)
		cout<<expr[e]<<" ";
	cout<<endl;
}

int calc(int start, int end)
{
	for(int i = start;i<end;i++)
	{
		if(expr[i] == -1)
		{
			// process {}
			int counter = 0;
			for(int j = i+1;j<end+1;j++)
			{
				if(expr[j] == -2 && counter == 1) // end
				{
					calc(i+1,j-1);
					expr.erase(expr.begin()+i);
					expr.erase(expr.begin()+j);
					// debug_log();
				}
				else if(expr[j] == -1)
				{
					counter++;
				}
				else if(expr[j] == -2 && counter != 1)
				{
					counter--;
				}
			}
		}
		else if(expr[i] == -3)
		{
			expr[i] = max(expr[i-1], expr[i+1]);
			expr.erase(expr.begin()+i + 1);
			expr.erase(expr.begin()+i-1);
		}
	}
}

int main()
{
	string str;
	cin>>str;
	int counter = 0;
	for(int i = 0;i<str.length();i++)
	{
		// -1 for left, -2 for right, -3 for |
		switch(str[i])
		{
			case 'a':
				counter++;
				if(i == str.length() || str[i+1] != 'a')
					expr.push_back(counter);
				break;
			case '|':
				counter = 0;
				expr.push_back(-3);
				break;
			case '(':
				counter = 0;
				expr.push_back(-1);
				break;
			case ')':
				counter=0;
				expr.push_back(-2);
				break;
		}
	}
	calc(0,expr.size()-1);
	debug_log();
}
