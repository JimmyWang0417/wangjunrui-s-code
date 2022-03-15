#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
const int N=505,M=1005;
vector<bitset<M> >tree[M*4];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void update(int rt,int l,int r,int x,int y,const bitset<M>&bit)
{
	if(r<x||l>y)
		return;
	if(x<=l&&r<=y)
	{
//		cout<<l<<' '<<r<<' '<<x<<' '<<y<<' '<<bit<<endl;
		tree[rt].push_back(bit);
		return;
	}
	int mid=(l+r)>>1;
	update(lc,l,mid,x,y,bit);
	update(rc,mid+1,r,x,y,bit);
}

int st[M];
int top;
bitset<M> ans[M],bit[M];
inline void solve(int rt,int l,int r)
{
	int lastop=top;
	for(int kase=0; kase<(int)tree[rt].size(); ++kase)
	{
		bitset<M>now=tree[rt][kase];
		int pos=-1;
		for(int i=999; i>=0; --i)
		{
			if(now[i])
			{
				if(!bit[i][i])
				{
					bit[i]=now;
					pos=i;
					break;
				}
				else
					now^=bit[i];
			}
		}
		if(pos!=-1)
			st[++top]=pos;
	}
	if(l==r)
	{
		for(int i=999; i>=0; --i)
			if(!ans[l][i]&&bit[i][i])
				ans[l]^=bit[i];
	}
	else
	{
		int mid=(l+r)>>1;
		solve(lc,l,mid);
		solve(rc,mid+1,r);
	}
//	printf("%d %d %d %d\n",l,r,top,lastop);
	while(top>lastop)
		bit[st[top--]].reset();
}
int kase,n,m;
bitset<M> val[N];
int las[N];
inline void print(const bitset<M> &wdnmd)
{
	bool flag=false;
	for(int i=999; i>=0; --i)
	{
		if(wdnmd[i])
		{
			putchar('1');
			flag=true;
		}
		else
		{
			if(flag)
				putchar('0');
		}
	}
	if(!flag)
		putchar('0');
	putchar('\n');
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>kase>>n>>m;
	char opt[M];
	bitset<M>wdnmd;
	for(int i=1; i<=m; ++i)
	{
		int u,v;
		cin>>u>>v>>opt;

		wdnmd.reset();
		int len=(int)strlen(opt);
		for(int j=0; j<len; ++j)
			wdnmd[j]=opt[len-j-1]-'0';

		if(las[u])
			update(1,1,m,las[u],i-1,val[u]);
		if(las[v])
			update(1,1,m,las[v],i-1,val[v]);

		las[u]=las[v]=i;
		val[u]^=wdnmd,val[v]^=wdnmd;
//		cout<<val[u]<<endl<<val[v]<<endl<<endl;
	}
	for(int i=1; i<=n; ++i)
		update(1,1,m,las[i],m,val[i]);
	solve(1,1,m);
	for(int i=1; i<=m; ++i)
		print(ans[i]);
	return 0;
}


