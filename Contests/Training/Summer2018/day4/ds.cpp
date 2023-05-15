// ZJOI 2005;
#include <iostream>
#include <vector>

using namespace std;

#define tuple vector<int>

vector<tuple> ds(vector<tuple> v)
{
	int size = v.size();
	vector<tuple> tmp;
	if(v.size() == 1)
		return v;
	
	if(size % 2 == 0)
	{
		// Even;
		for(int i = 0;i<v.size();i+=2)
		{
			vector<int> comb;
			vector<int> current = v[i];
			vector<int> next = v[i+1];
			int posa = 0; int posb = 0;
			bool enda,endb;
			enda = false;
			endb = false;
			
			for(;!enda || !endb;)
			{
				if(enda)
				{
					comb.push_back(next[posb]);
					posb++;
				}
				else if(endb)
				{
					comb.push_back(next[posa]);
					posb++;
				}
				else if(current[posa]>next[posb])
				{
					comb.push_back(next[posb]);
					posb++;
				}
				else
				{
					comb.push_back(current[posa]);
					posa++;
				}
				
				enda = (posa == current.size());
				endb = (posb == next.size());
			}
			tmp.push_back(comb);
		}
	}
	else
	{
		// Odd;
		vector<int> ret = ds(v);
		for(int i = 0;i<ret.size();i++)
		{
			tmp.push_back(*ret[i]);
		}
		tmp.push_back(v.back());
	}
	return tmp;
}

int main()
{
	int N;
	cin>>N;
	vector<vector<int>> database;
	for(int i = 0;i<N;i++)
	{
		vector<int> arr;
		int inp;
		cin>>inp;
		arr.push_back(inp);
		database.push_back(*arr);
	}
	
	ds(database);
}
