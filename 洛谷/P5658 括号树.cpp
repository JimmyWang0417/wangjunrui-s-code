#include<cstdio>
#define re register
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
const int N=5e5+10;
char s[N];
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge,fa[N],lst[N];
int top,st[N],n;
long long answer,ans[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
inline void dfs(int u)
{
	int nxt=0;
	if(s[u]==')')
	{
		if(top)
		{
			nxt=st[top--];
			lst[u]=lst[fa[nxt]]+1;
		}
	}
	else
		st[++top]=u;
	ans[u]=ans[fa[u]]+lst[u];
	for(re int i=head[u]; i; i=edge[i].next)
		dfs(edge[i].to);
	if(nxt)
		st[++top]=nxt;
	else if(top)
		--top;
}
int main()
{
	read(n);
	scanf("%s",s+1);
	for(re int i=2; i<=n; ++i)
	{
		int f;
		read(f);
		fa[i]=f;
		add_edge(f,i);
	}
	dfs(1);
	for(re int i=1; i<=n; ++i)
		answer^=ans[i]*i;
	printf("%lld\n",answer);
	return 0;
}
