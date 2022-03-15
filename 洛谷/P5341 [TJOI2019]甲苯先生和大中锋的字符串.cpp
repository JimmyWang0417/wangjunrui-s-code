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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=2e5+5;
char str[N];
int cnt;
class SAM
{
	private:
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
		int f[N];
		int diff[N],sum[N];
		inline void update(int l,int r)
		{
			++diff[l],--diff[r+1];
		}
		struct Point
		{
			int fa,len,ch[26];
		} point[N];
		int las=1,tot=1;
		inline void dfs(int u)
		{
			for(re int i=head[u]; i; i=edge[i].next)
			{
				int &v=edge[i].to;
				dfs(v);
				f[u]+=f[v];
			}
			if(f[u]==cnt)
				update(point[point[u].fa].len+1,point[u].len);
		}
	public:
		inline void insert(int c)
		{
			int p=las,np=las=++tot;
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
					point[nq].len=point[p].len+1;
					point[q].fa=point[np].fa=nq;
					for(; p&&point[p].ch[c]==q; p=point[p].fa)
						point[p].ch[c]=nq;
				}
			}
		}
		inline int solve(int len)
		{
			for(re int i=2; i<=tot; ++i)
				add_edge(point[i].fa,i);
			dfs(1);
			int ans=0;
			for(re int i=1; i<=len; ++i)
				sum[i]=sum[i-1]+diff[i];
			for(re int i=len; i>=1; --i)
				if(sum[ans]<sum[i])
					ans=i;
			return !ans?-1:ans;
		}
		inline void clean()
		{
			memset(diff,0,sizeof(diff));
			memset(f,0,sizeof(f));
			memset(head,num_edge=0,sizeof(head));
			memset(point,0,sizeof(point));
			las=tot=1;
		}
} tree;
inline void work()
{
	scanf("%s",str);
	read(cnt);
	int len=(int)strlen(str);
	for(re int i=0; i<len; ++i)
		tree.insert(str[i]-'a');
	printf("%d\n",tree.solve(len));
	tree.clean();
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


