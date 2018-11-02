// P1023
#include <iostream> 
#include <cstring>

using namespace std;

int main()
{
	int desirePrice, proCost, procostNum;
	cin>>desirePrice>>proCost>>procostNum;
	int table[1000][2];
	memset(table,0,sizeof(table));
	int counter = 0;
	for(;;)
	{
		int first;
		int second;
		cin>>first>>second;
		if(first == -1)
			break;			// go to process part;
		table[counter][0] = first;
		table[counter][1] = second;
		counter++;
	}
	
	int extra;
	cin>>extra;
	
	// I/O end;
	// start to process;
}
