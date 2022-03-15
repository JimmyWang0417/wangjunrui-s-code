#include<bits/stdc++.h>
#define ll double
using namespace std;
inline ll gcd(ll n,ll m)
{
	if(m==0)
		return n;
	return gcd(m,fmod(n,m));
}
const int N=5e5+5;
int n,m;
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
int in[N],out[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
struct node
{
	ll a,b;
	node(ll _a=0,ll _b=1):a(_a),b(_b) {}
	inline void update()
	{
		ll g=gcd(a,b);
		a/=g,b/=g;
	}
	inline node friend operator + (node a,node b)
	{
		ll lcm=a.b/gcd(a.b,b.b)*b.b;
		a.a*=lcm/a.b;
		b.a*=lcm/b.b;
		return node(a.a+b.a,lcm);
	}
} a[N];
int main()
{
	//freopen("water.in","r",stdin),freopen("water.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
	{
		int cnt;
		scanf("%d",&cnt);
		if(i<=m)
			a[i]=node(1,1);
		else
			a[i]=node(0,1);
		out[i]=cnt;
		while(cnt--)
		{
			int v;
			scanf("%d",&v);
			add_edge(i,v);
			++in[v];
		}
	}
//	cout<<(node(0,1)+node(1,1)).a<<' '<<(node(0,1)+node(1,3)).b<<endl;
	queue<int>q;
	for(int i=1; i<=n; ++i)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		if(!out[u])
			continue;
		node add(a[u].a,a[u].b*out[u]);
		add.update();
//		cout<<u<<':'<<add.a<<' '<<add.b<<' '<<out[u]<<endl;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			a[v]=a[v]+add;
			a[v].update();
			--in[v];
			if(!in[v])
				q.push(v);
		}
	}
//	for(int i=1; i<=n; ++i)
//		printf("%d ",out[i]);
//	putchar('\n');
	for(int i=1; i<=n; ++i)
		if(!out[i])
		{
			a[i].update();
			printf("%.0lf %.0lf\n",a[i].a,a[i].b);
		}
	return 0;
}