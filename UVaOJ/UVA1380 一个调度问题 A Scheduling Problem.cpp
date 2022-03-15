#include<cstdio>
#include<string>
#include<vector>
#include<climits>
#include<sstream>
#include<cstring>
#include<cassert>
#include<iostream>
#include<algorithm>
#define re register
using namespace std;
const int maxn=205,INF=INT_MAX/2;
struct Edge
{
	int u,v,d;
	Edge(int u=0,int v=0,int d=0):u(u),v(v),d(d) {}
};
vector<Edge>edge[maxn];
int n,root,maxlen,f[maxn],g[maxn];
bool have_father[maxn];
inline int dfs(int u)
{
	int ans=0;
	for(re int i=0; i<edge[u].size(); ++i)
	{
		int &v=edge[u][i].v;
		if(edge[u][i].d==1)
			ans=max(ans,dfs(v)+1);
	}
	return ans;
}
inline bool read_solve()
{
	bool have_date=false;
	int a,b;
	n=0;
	for(re int i=0; i<maxn; ++i)
		edge[i].clear();
	memset(have_father,false,sizeof(have_father));
	while(cin>>a&&a)
	{
		string str;
		have_date=true;
		if(a>n)
			n=a;
		while(cin>>str&&str!="0")
		{
			int len=str.length();
			char dir=str[len-1];
			if(dir=='u'||dir=='d')
				str=str.substr(0,len-1);
			stringstream ss(str);
			ss>>b;
			if(b>n)
				n=b;
			have_father[b]=true;
			if(dir=='d')
			{
				edge[a].push_back(Edge(a,b,1));
				edge[b].push_back(Edge(b,a,2));
			}
			else if(dir=='u')
			{
				edge[a].push_back(Edge(a,b,2));
				edge[b].push_back(Edge(b,a,1));
			}
			else
				edge[a].push_back(Edge(a,b,0));
		}
	}
	if(have_date)
	{
		for(re int i=1; i<=n; ++i)
			if(!have_father[i]&&!edge[i].empty())
			{
				root=i;
				break;
			}
		return true;
	}
	return false;
}
struct undirected_son
{
	int v,f,g;
	undirected_son(int v=0,int f=0,int g=0):v(v),f(f),g(g) {}
};
struct cmp_f
{
	inline bool operator () (const undirected_son &a,const undirected_son &b)
	{
		return a.f<b.f;
	}
};
struct cmp_g
{
	inline bool operator () (const undirected_son &a,const undirected_son &b)
	{
		return a.g<b.g;
	}
};
inline bool dp(int u,int fa)
{
	if(edge[u].empty())
	{
		f[u]=g[u]=0;
		return true;
	}
	vector<undirected_son>son;
	int f0=0,g0=0;
	for(re int i=0; i<edge[u].size(); ++i)
	{
		int &v=edge[u][i].v, &d=edge[u][i].d;
		if(v==fa)
			continue;
		dp(v,u);
		if(d==0)
			son.push_back(undirected_son(v,f[v],g[v]));
		else if(d==1)
			g0=max(g0,g[v]+1);
		else if(d==2)
			f0=max(f0,f[v]+1);
	}
	//printf("%d %d\n",f0,g0);
	if(son.empty())
	{
		if(f0+g0>maxlen)
		{
			f[u]=g[u]=INF;
			return false;
		}
		else
		{
			f[u]=f0;
			g[u]=g0;
			return true;
		}
	}
	f[u]=g[u]=INF;
	int s=son.size();
	sort(son.begin(),son.end(),cmp_f());
	int maxg[maxn];
	maxg[s-1]=son[s-1].g;
	for(re int i=s-2; i>=0; --i)
		maxg[i]=max(maxg[i+1],son[i].g);
	assert(son.size()==s);
	for(re int i=0; i<=s; ++i)
	{
		int ff=f0,gg=g0;
		if(i>0)
			ff=max(ff,son[i-1].f+1);
		if(i<s)
			gg=max(gg,maxg[i]+1);
		if(ff+gg<=maxlen)
			f[u]=min(f[u],ff);
	}
	sort(son.begin(),son.end(),cmp_g());
	int maxf[maxn];
	maxf[s-1]=son[s-1].f;
	for(re int i=s-2; i>=0; --i)
		maxf[i]=max(maxf[i+1],son[i].f);
	for(re int i=0; i<=s; ++i)
	{
		int ff=f0,gg=g0;
		if(i>0)
			gg=max(gg,son[i-1].g+1);
		if(i<s)
			ff=max(ff,maxf[i]+1);
		if(ff+gg<=maxlen)
			g[u]=min(g[u],gg);
	}
//	for(int p=0;p<s;++p)
//	printf("%d\n",maxf[p]);
	return f[u]<INF;

}
int main()
{
//	freopen("ans.in","r",stdin); 
	ios::sync_with_stdio(false);
	while(read_solve())
	{
		maxlen=0;
		for(re int i=1; i<=n; ++i)
			maxlen=max(maxlen,dfs(i));
		printf("%d\n",maxlen+(dp(root,-1)?1:2));
	}
	return 0;
}
