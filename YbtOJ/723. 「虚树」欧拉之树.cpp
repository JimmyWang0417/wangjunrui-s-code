#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
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
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=2e5+5,mod=1e9+7;
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
inline void minu(int &x,int y)
{
	x-=y;
	if(x<0)
		x+=mod;
}
inline int times(int x,int y)
{
	return (int)((ll)x*y%mod);
}
inline int quickpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=times(res,a);
		a=times(a,a);
		b>>=1;
	}
	return res;
}
int prime[N],tot,phi[N],mul[N];
bitset<N>vis;
inline void getprime(int n)
{
	mul[1]=1;
	phi[1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			phi[i]=i-1;
			mul[i]=-1;
		}
		for(int j=1; j<=tot; ++j)
		{
			if(prime[j]*i>n)
				break;
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				mul[i*prime[j]]=0;
				break;
			}
			else
			{
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
				mul[i*prime[j]]=-mul[i];
			}
		}
	}
}
int n;
int a[N];
struct Edge
{
	int next,to;
} edge[N*2];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
int id[N];
int dfn[N],dep[N],dfstime;
int size[N],son[N];
int fa[N];
inline void dfs1(int u,int _fa)
{
	dep[u]=dep[_fa]+1;
	size[u]=1;
	fa[u]=_fa;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==_fa)
			continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])
			son[u]=v;
	}
}
int top[N];
inline void dfs2(int u,int topf)
{
	top[u]=topf;
	dfn[u]=++dfstime;
	if(!head[u])
		return;
	dfs2(son[u],topf);
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(top[v])
			continue;
		dfs2(v,v);
	}
}
inline int getlca(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	return u;
}
int vir[N];
int par[N];
int st[N];
inline bool cmp(int rhsa,int rhsb)
{
	return dfn[rhsa]<dfn[rhsb];
}
int ans=0;
int sum[N];
inline void calc(int u)
{
	if(vis[u])
	{
		sum[u]=phi[a[u]];
		minu(ans,times(times(dep[u],2),times(phi[a[u]],phi[a[u]])));
	}
	else
		sum[u]=0;
	int res=0;
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		calc(v);
		add(res,times(sum[u],sum[v]));
		add(sum[u],sum[v]);
	}
	minu(ans,times(4,times(res,dep[u])));
}
int g[N];
inline void work(int val)
{
	int sum1=0;
	for(int i=val; i<=n; i+=val)
		add(sum1,phi[i]);
	int sum2=0;
	tot=0;
	for(int i=val; i<=n; i+=val)
	{
		add(sum2,times(dep[id[i]],phi[i]));
		vir[++tot]=id[i];
		vis[id[i]]=true;
	}
	ans=times(sum1,sum2);
	add(ans,ans);
//	printf("%d %d %d\n",ans,sum1,sum2);
	sort(vir+1,vir+1+tot,cmp);
	tot=(int)(unique(vir+1,vir+1+tot)-vir-1);
	int cnt=tot;
	int tp=0;
	for(int i=1; i<=tot; ++i)
	{
		const int &u=vir[i];
		if(!tp)
		{
			par[u]=0;
			st[++tp]=u;
			continue;
		}
		int lca=getlca(st[tp],u);
		while(dep[st[tp]]>dep[lca])
		{
			if(dep[st[tp-1]]<dep[lca])
				par[st[tp]]=lca;
			--tp;
		}
		if(lca!=st[tp])
		{
			vir[++cnt]=lca;
			par[lca]=st[tp];
			st[++tp]=lca;
		}
		par[u]=lca;
		st[++tp]=u;
	}
//	printf("nmsl\n");
	tot=cnt;
	sort(vir+1,vir+1+tot,cmp);
	for(int i=1; i<=tot; ++i)
		head[vir[i]]=0;
	num_edge=0;
	for(int i=1; i<=tot; ++i)
		add_edge(par[vir[i]],vir[i]);
//	for(int i=1; i<=tot; ++i)
//		printf(" %d",par[vir[i]]);
//	putchar('\n');
//	for(int i=1; i<=tot; ++i)
//		printf(" %d",vir[i]);
//	putchar('\n');
	calc(vir[1]);
	for(int i=1; i<=tot; ++i)
		vis[vir[i]]=false;
	g[val]=ans;
}
signed main()
{
	freopen("sm.in","r",stdin);
	freopen("sm.out","w",stdout);
	read(n);
	getprime(n);
//	for(int i=1; i<=n; ++i)
//		printf(" %d %d\n",mul[i],phi[i]);
//	putchar('\n');
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		id[a[i]]=i;
	}
	for(int i=1; i<n; ++i)
	{
		int u,v;
		read(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	vis.reset();
	for(int i=1; i<=n; ++i)
		work(i);
//	for(int i=1; i<=n; ++i)
//		printf("%d ",g[i]);
//	putchar('\n');
	int res=0;
	for(int t=1; t<=n; ++t)
	{
		int cnt=0;
		for(int d=t; d<=n; d+=t)
			cnt=((cnt+mul[d/t]*g[d])%mod+mod)%mod;
//		printf("%d ",cnt);
		add(res,times(cnt,times(t,quickpow(phi[t],mod-2))));
	}
//	putchar('\n');
	printf("%d\n",times(res,quickpow(times(n,n-1),mod-2)));
//	printf("%d\n",res);
	return 0;
}

