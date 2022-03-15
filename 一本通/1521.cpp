#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
#define re register
#define ll long long
using namespace std;
const int oo=1e9,M=1e5+5;
int n,m,
    num_edge,head[M],
    dfn[M],low[M],st[M],top,
    root,dfstime,
    bt,cnt;
bool gedian[M];
struct Edge
{
	int next,to;
} edge[M<<1];
vector<int>block[M];
inline void add_edge(int from,int to)
{
	edge[num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge++;
}
inline void tarjan(int x)
{
	low[x]=dfn[x]=++dfstime;
	st[++top]=x;
	int cnt=0;
	for(re int i=head[x]; i!=-1; i=edge[i].next)
	{
		int y=edge[i].to;
		if(!dfn[y])
		{
			cnt++;
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if((x==root&&cnt>1)||(x!=root&&dfn[x]<=low[y]))
				gedian[x]=1;
			if(dfn[x]<=low[y])
			{
				bt++;
				block[bt].clear();
				do
				{
					block[bt].push_back(st[top--]);
				}
				while(st[top+1]!=y);
				block[bt].push_back(x);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
int T;
int main()
{
	while(scanf("%d",&m)&&m)
	{
		n=0;
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(head,-1,sizeof(head));
		memset(gedian,0,sizeof(gedian));
		num_edge=top=dfstime=bt=0;
		for(re int i=1,a,b; i<=m; i++)
		{
			scanf("%d%d",&a,&b);
			n=max(n,max(a,b));
			add_edge(a,b);
			add_edge(b,a);
		}
		for(re int i=1; i<=n; i++)
			if(dfn[i]==0)
			{
				root=i;
				tarjan(i);
			}
		ll res=0,num=1;
		for(re int i=1,len,gnum; i<=bt; i++)
		{
			gnum=0;
			len=block[i].size();
			for(re int j=0; j<len; j++)
				if(gedian[block[i][j]])
					gnum++;
			if(gnum==0)
			{
				res+=2;
				num=num*(len-1)*len>>1;
			}
			else if(gnum==1)
			{
				res++;
				num=num*(len-1);
			}
		}
		printf("Case %d: %lld %lld\n",++T,res,num);
	}
}
