// POJ1321.cpp
#include <iostream>
#include <cstring>

using namespace std;

enum point
{
	free_area,
	wall,
	placed
};

struct node
{
	int x,y;
	point type;
	node* next;
	
	node()
	{
		next = NULL;
	}
};

struct dataset
{
	point map[9][9];
	int n,k,empty_point;
	node *first;
	node *end;
	
	dataset()
	{
		n = 0;
		k = 0;
		empty_point = 0;
		first = NULL;
		end = NULL;
	}
};

point parsePoint(char c)
{
	switch(c)
	{
		case '#':
			return wall;
		case '.':
			return free_area;
	}
}

dataset input_dataset()
{
	dataset ret;
	cin>>ret.n>>ret.k;
	if(ret.n == -1)
		return ret;
	for(int i = 0;i<ret.n;i++)
		for(int j = 0;j<ret.n;j++)
		{
			char current;
			cin>>current;
			ret.map[i][j] = parsePoint(current);
			if(ret.map[i][j] == free_area)
			{
				node *n = new node();
				n->x = i; n->y = j;
				n->type = free_area;
				if(ret.first == NULL)
					ret.first = n;
				else if(ret.end == NULL)
				{
					ret.first->next = n;
					ret.end = n;
				}
				else
				{
					ret.end->next = n;
					ret.end = n;
				}
				ret.empty_point++;
			}
		}
	cout<<"read"<<endl;
	return ret;
}

point current_map[9][9];

bool check_point(dataset ds, int x_, int y_)
{
	for(int x = 0;x<ds.n;x++)
		if(ds.map[x][y_] == placed || current_map[x][y_] == placed)
			return false;
	return true;
}

int process(dataset ds)
{
	int ret = 0;
	int inuse = 0;
	int xstart, ystart;
		for(node *cursor = ds.first;
		cursor->next != NULL && ds.empty_point - inuse >= ds.k; 
		cursor = cursor->next)
	{
		xstart = cursor->x;
		ystart = cursor->y;
		int lastx = xstart;
		int apossibly = 1;
		for(node *comparison = cursor; comparison != NULL ; comparison = comparison->next)
			if(comparison->x != lastx && check_point(ds, comparison->x, comparison->y))
			{
				apossibly++;
				lastx = comparison->x;
				current_map[comparison->x][comparison->y] = placed;
			}
		if(apossibly>=ds.k)
			ret++;
			memset(current_map, free_area, sizeof(current_map));
		inuse++;
	}
	return ret;
}

int main()
{
	dataset res = input_dataset();
	int a = 10;
	while(res.n != -1)
	{
		cout<<process(res);
		res = input_dataset();
	}
	return 0;
} 
