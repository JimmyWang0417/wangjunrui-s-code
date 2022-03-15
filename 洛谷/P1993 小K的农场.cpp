#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;
int n,m;
int dis[3010];
int w[6050],u[6050],v[6050];
int deep_dark_blue[100001];
int f,t;
int main()
{
	int p;
	scanf("%d",&p);
	while(p--)
	{
		scanf("%d%d",&n,&m);
		int pos=0;
		for(register int i=1; i<=m; i++)
		{
			pos++;
			scanf("%d%d%d",&w[pos],&u[pos],&v[pos]);
			if(v[pos]>=0)
			{
				w[pos+1]=u[pos];
				u[pos+1]=w[pos];
				pos++;
				v[pos]=v[pos-1];
			}
		}
		for(register int i=1; i<=n; i++)
		{
			dis[i]=INF;
		}
		dis[1]=0;
		for(register int i=1; i<=n-1; i++)
		{
			for(register int j=1; j<=pos; j++)
			{
				if(dis[u[j]] > dis[w[j]] + v[j])
				{
					dis[u[j]] = dis[w[j]] + v[j];
				}
			}
		}
		bool f=false;
		for(register int j=1; j<=pos; j++)
		{
			if(dis[u[j]] > dis[w[j]] + v[j])
				f=true;
		}
		if(f)
		{
			printf("YE5\n");
		}
		else
		{
			printf("N0\n");
		}
	}
	return 0;
}
