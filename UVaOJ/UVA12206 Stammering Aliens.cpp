#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>
#define lowbit(x) (x&(-x))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*a,int l,int r,T val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=40005<<1;
struct SAM
{
	int ch[26],fa,len;
	int id;
} point[N];
int tot=1,las=1;
int f[N];
inline void insert(int c,int id)
{
	int p=las,np=las=++tot;
	point[np].id=id;
	point[np].len=point[p].len+1;
	f[np]=1;
	for(; p&&!point[p].ch[c]; p=point[p].fa)
		point[p].ch[c]=np;
	if(!p)
		point[np].fa=1;
	else
	{
		int q=point[p].ch[c];
		if(point[q].len==point[p].len+1)
			point[np].fa=q;
		else
		{
			int nq=++tot;
			point[nq]=point[q];
			point[q].fa=point[np].fa=nq;
			point[nq].len=point[p].len+1;
			for(; p&&point[p].ch[c]==q; p=point[p].fa)
				point[p].ch[c]=nq;
		}
	}
}
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int maxid[N];
int ans,pos;
int m;
char str[N];
inline void dfs(int u)
{
	maxid[u]=point[u].id;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs(v);
		f[u]+=f[v];
		maxid[u]=max(maxid[u],maxid[v]);
	}
	if(f[u]>=m)
	{
		if(point[u].len>ans)
		{
			ans=point[u].len;
			pos=maxid[u]-point[u].len+1;
		}
		else if(point[u].len==ans)
			pos=max(pos,maxid[u]-point[u].len+1);
	}
}
signed main()
{
//	freopen("ans.in","r",stdin),freopen("ans.out","w",stdout);
	while(read(m),m)
	{
		scanf("%s",str);
		las=tot=1;
		ans=pos=0;
		for(re int i=0; str[i]; ++i)
			insert(str[i]-'a',i);
		for(re int i=2; i<=tot; ++i)
			add_edge(point[i].fa,i);
		dfs(1);
		if(!ans)
			printf("none\n");
		else
			printf("%d %d\n",ans,pos);
		clear(head,1,tot,num_edge=0);
		clear(f,1,tot,0);
		clear(maxid,1,tot,0);
		for(re int i=1; i<=tot; ++i)
			memset(point[i].ch,point[i].fa=point[i].len=point[i].id=0,sizeof(point[i].ch));
	}
	return 0;
}


