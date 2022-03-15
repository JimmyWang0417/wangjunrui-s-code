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
const int N=2505;
int n;
char s[N];
bool del[N];
bool leaf[N][26];

vector<int>son[N];
int dp[N];
bool g[N][26];
bitset<N>vis;
int belong[N];

inline bool find(int u,int fa)
{
	for(auto v:son[fa])
	{
		if(vis[v]||!g[v][u])
			continue;
		vis.set(v);
		if(belong[v]==-1||find(belong[v],fa))
		{
			belong[v]=u;
			return true;
		}
	}
	return false;
}
inline bool tryfind(int u,int fa)
{
	for(auto v:son[fa])
	{
		if(vis[v]||!g[v][u])
			continue;
		vis.set(v);
		if(belong[v]==-1||tryfind(belong[v],fa))
			return true;
	}
	return false;
}
inline void dfs(int u)
{
	dp[u]=1;
	for(auto v:son[u])
	{
		dfs(v);
		dp[u]+=dp[v];
	}
	for(int i=0; i<26; ++i)
		if(leaf[u][i])
		{
			g[u][i]=true;
			vis.reset();
			dp[u]+=1-find(i,u);
		}
	for(auto v:son[u])
	{
		vis.reset();
		vis.set(v);
		if(belong[v]==-1||tryfind(belong[v],u))
			for(int i=0; i<26; ++i)
				g[u][i]|=g[v][i];
	}

}
int st[N],top;
int fa[N];
signed main()
{
	freopen("expr.in","r",stdin),freopen("expr.out","w",stdout);
	scanf("%s",s+1);
	n=(int)strlen(s+1);
	for(int i=1; i<=n; ++i)
	{
		belong[i]=-1;
		if(s[i]>='a'&&s[i]<='z')
			st[++top]=i;
		else
		{
			fa[st[top]]=fa[st[top-1]]=i;
			st[--top]=i;
		}
	}
	for(int i=1; i<n; ++i)
	{
		while(s[fa[i]]==s[fa[fa[i]]])
		{
			del[fa[i]]=true;
			fa[i]=fa[fa[i]];
		}
	}
	for(int i=1; i<n; ++i)
	{
		if(s[i]>='a'&&s[i]<='z')
			leaf[fa[i]][s[i]-'a']=true;
		else if(!del[i])
			son[fa[i]].push_back(i);
	}
	dfs(n);
	printf("%d\n",dp[n]);
	return 0;
}

