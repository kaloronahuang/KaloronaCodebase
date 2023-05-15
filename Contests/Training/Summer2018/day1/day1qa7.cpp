#include <iostream>
using namespace std;

struct StudentInfo{
	char StudentName[40];
	int FinalAvg;
	int ClassScore;
	bool IsWestern;
	bool IsMoniter;
	int EssayNum;
	int Scholorship = 0;
};

struct Set{
	StudentInfo* infos;
};

int main(){
	// input part;
	int testSet,studentNum;
	cin>>testSet;
	cin>>studentNum;
	Set ss[testSet];
	ss[0].infos = new StudentInfo[studentNum];
	int total = 0;
	for(int i = 0;i<studentNum;i++)
	{
		cin>>ss[0].infos[i].StudentName;
		cin>>ss[0].infos[i].FinalAvg;
		cin>>ss[0].infos[i].ClassScore;
		char a,b;
		cin>>a>>b;
		ss[0].infos[i].IsMoniter = (a=='Y');
		ss[0].infos[i].IsWestern = (b=='Y');
		cin>>ss[0].infos[i].EssayNum;
		
		//process
		if(ss[0].infos[i].FinalAvg>80 && ss[0].infos[i].EssayNum>0)
			ss[0].infos[i].Scholorship += 8000;
		if(ss[0].infos[i].FinalAvg>85 && ss[0].infos[i].ClassScore>80)
			ss[0].infos[i].Scholorship += 4000;
		if(ss[0].infos[i].FinalAvg>90)
			ss[0].infos[i].Scholorship+=2000;
		if(ss[0].infos[i].FinalAvg>85 && ss[0].infos[i].IsWestern)
			ss[0].infos[i].Scholorship +=1000;
		if(ss[0].infos[i].FinalAvg>80 && ss[0].infos[i].IsMoniter)
			ss[0].infos[i].Scholorship += 850;
		total += ss[0].infos[i].Scholorship;
	}
	
	// sort;
	for(int i = 0;i<studentNum - 1;i++)
	{
		for(int j = 0;j<studentNum -1 -i;j++)
		{
			if(ss[0].infos[j].Scholorship < ss[0].infos[j+1].Scholorship)
				swap(ss[0].infos[j],ss[0].infos[j+1]);
		}
	}
	
	// output;
	StudentInfo si = ss[0].infos[0];
	cout<<si.StudentName<<endl<<si.Scholorship<<endl;
	
	int bench = ss[0].infos[0].Scholorship;
	int counter = 0;
	for(int est = 0;est<studentNum;est++)
	{
		if(ss[0].infos[est].Scholorship == bench)
			counter++;
	}
	cout<<total;
	return 0;
} 
