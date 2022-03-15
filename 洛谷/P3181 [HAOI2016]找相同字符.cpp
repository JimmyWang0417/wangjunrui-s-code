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
const int N=2e5*4+5;
struct SAM
{
	int fa,len,ch[26];
} point[N];
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
int f[2][N];
int tot=1,las=1;
inline void insert(int c,int id)
{
	int p=las,np=las=++tot;
	point[np].len=point[p].len+1;
	++f[id][np];
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
			point[np].fa=point[q].fa=nq;
			point[nq].len=point[p].len+1;
			for(; p&&q==point[p].ch[c]; p=point[p].fa)
				point[p].ch[c]=nq;
		}
	}
//	assert(point[np].id!=id);
//	printf("%d\n",id);
//	for(; np&&point[np].id!=id; np=point[np].fa)
//	{
//		++f[id-1][np];
//		point[np].id=id;
//	}
}
char str[N];
ll ans;
inline void dfs(int u)
{
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs(v);
		f[0][u]+=f[0][v];
		f[1][u]+=f[1][v];
	}
}
signed main()
{
	for(re int i=0; i<2; ++i)
	{
		las=1;
		scanf("%s",str);
		for(re int j=0; str[j]; ++j)
			insert(str[j]-'a',i);
	}
	for(re int i=2; i<=tot; ++i)
		add_edge(point[i].fa,i);
	dfs(1);
//	for(re int i=1; i<=tot; ++i)
//		printf("%d %d\n",f[0][i],f[1][i]);
	for(re int i=2; i<=tot; ++i)
		ans+=1ll*(point[i].len-point[point[i].fa].len)*f[0][i]*f[1][i];
	printf("%lld\n",ans);
	return 0;
}


