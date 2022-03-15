#include<cstdio>
#include<queue>
#include<iostream>
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
#define ll long long
#define li ll
const ll MAXN=2e5+51,MOD=998244353,inf=0x3f3f3f3f;
struct Edge
{
	ll to,prev;
};
Edge ed[MAXN<<1];
ll nc,tot,from,to,p,r,x;
queue<ll>q;
ll last[MAXN],deg[MAXN];
inline ll qpow(ll base,ll exponent)
{
	li res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
// Functions
inline void addEdge(ll from,ll to)
{
	ed[++tot].prev=last[from];
	ed[tot].to=to;
	last[from]=tot;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>nc;
	for(register int i=0; i<nc-1; i++)
	{
		cin>>from>>to;
		addEdge(from,to),addEdge(to,from);
		deg[from]++,deg[to]++;
	}
	for(register int i=1; i<=nc; i++)
	{
		if(deg[i]==1)
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		p=q.front(),q.pop();
		if(!q.empty())
		{
			r=q.front(),q.pop();
		}
		else
		{
			cout<<"! "<<p<<endl;
			exit(0);
		}
		cout<<"? "<<p<<" "<<r<<endl,cin>>x;
		if(x==p||x==r)
		{
			cout<<"! "<<x<<endl;
			exit(0);
		}
		for(register int i=last[p]; i; i=ed[i].prev)
		{
			if(--deg[ed[i].to]==1)
			{
				q.push(ed[i].to);
			}
		}
		for(register int i=last[r]; i; i=ed[i].prev)
		{
			if(--deg[ed[i].to]==1)
			{
				q.push(ed[i].to);
			}
		}
	}
}
