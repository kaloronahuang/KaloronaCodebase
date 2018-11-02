#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define MAX 100
#define INF 10000000

int arr[MAX][MAX];//����ͼ 
int dist[MAX];//���浽���ж����Ȩֵ 
bool visit[MAX];//����Ƿ񱻷��ʹ� 

int v,e;

void init(){
	for(int i=1;i<=v;i++){
		for(int j=1;j<=v;j++){
			arr[i][j]=INF; 
		}
		arr[i][i]=0;
		dist[i]=INF;
		visit[i] = false;
	}
}

void c(){
	for(int i=1;i<=e;i++){
		int v1,v2,weight;
		cin >> v1 >> v2 >> weight;
		if(arr[v1][v2]>weight)		
			arr[v1][v2]=arr[v2][v1]=weight;
	}
}

void dijkstra(){
	dist[1]=0;
	for(int i=1;i<=v;i++)
	{
		int tmp = INF,pos = -1;
		//�ҳ�����·������̵�һ�� 
		for(int j=1;j<=v;j++)
		{
			if(dist[j]<tmp && !visit[j])
			{
				tmp=dist[j];
				pos=j;
			
			}
		}
		visit[pos]=true;//����dist����Ȩֵ
		for(int j=1;j<=v;j++)
		{
			if(!visit[j])
			{
				dist[j]=min(dist[j],dist[pos]+arr[pos][j]);	
			}	
		} 
	}
} 

int main(){
	cin >> v >> e;
	init();
	c();
	dijkstra();	
	
	for(int i=1;i<=v;i++)
	{
		cout << dist[i]<<" ";
	}
}
