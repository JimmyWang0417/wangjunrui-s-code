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
const int N=6e5+5;
int f[N];
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
inline void dfs(int u)
{
	for(int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs(v);
		f[u]+=f[v];
	}
}
struct SAM
{
	int ch[26],fa,len;
} point[N];
int las=1,tot=1;
inline void insert(int c)
{
	int p=las,np=las=++tot;
	point[np].len=point[p].len+1;
	f[tot]=1;
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
char S[N],T[N];
int p[N];
inline void initkmp(char *str)
{
	p[1]=0;
	for(int i=2,j=0; str[i]; ++i)
	{
		while(j&&str[i]!=str[j+1])
			j=p[j];
		if(str[i]==str[j+1])
			++j;
		p[i]=j;
	}
//	printf("%s\n",str+1);
//	for(int i=1; str[i]; ++i)
//		printf("%d ",p[i]);
//	putchar('\n');
}
inline void solve()
{
	scanf("%s",T+1);
	int n=strlen(T+1);
	for(int i=1; i<=n; ++i)
		T[i+n]=T[i];
	T[n*2+1]='\0';
	initkmp(T);
	int now=1,len=0,ans=0;
	for(int i=1; i<n*2; ++i)
	{
		int c=T[i]-'a';
		if(point[now].ch[c])
		{
			now=point[now].ch[c];
			++len;
		}
		else
		{
			while(!point[now].ch[c]&&point[now].fa)
				now=point[now].fa;
			len=point[now].len;
			if(point[now].ch[c])
			{
				now=point[now].ch[c];
				++len;
			}
		}
		while(point[point[now].fa].len>=n)
		{
			now=point[now].fa;
			len=point[now].len;
		}
		if(len>=n&&p[i]<n)
			ans+=f[now];
	}
	printf("%d\n",ans);
}
signed main()
{
	freopen("tle.in","r",stdin);
	freopen("tle.out","w",stdout);
	scanf("%s",S+1);
	int n=strlen(S+1);
	for(int i=1; i<=n; ++i)
		insert(S[i]-'a');
	for(int i=2; i<=tot; ++i)
		add_edge(point[i].fa,i);
	dfs(1);
//	for(int i=1; i<=n; ++i)
//		printf("%d ",f[i]);
//	putchar('\n');
	int q;
	read(q);
	while(q--)
		solve();
	return 0;
}


