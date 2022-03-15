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
const int N=1e6+5;
struct node
{
	int l,r,cnt;
	node(int _l=0,int _r=0,int _cnt=0):l(_l),r(_r),cnt(_cnt) {}
	inline bool operator < (const node &rhs)const
	{
		return (ll)cnt*(rhs.r-rhs.l+1)<(ll)rhs.cnt*(r-l+1);
	}
	inline bool check(int k)const
	{
		return (ll)(r-l+1)*k<cnt;
	}
};
int n,m;
int cnt[N],dep[N];
int ed[N];
bitset<N>vis;
int ans[N];
int query[N];
signed main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	read(n,m);
	for(int i=1; i<=m; ++i)
		read(query[i]);
	++cnt[dep[1]=1];
	int res=1;
	for(int i=2; i<=n; ++i)
	{
		int fa;
		read(fa);
		++cnt[dep[i]=dep[fa]+1];
		res=max(res,dep[i]);
	}
	priority_queue<node>q;
	for(int i=1; i<=n; ++i)
	{
		ed[i]=i;
		q.push(node(i,i,cnt[i]));
	}
	for(int k=1e6; k>=1; --k)
	{
		while(q.top().check(k))
		{
			node x=q.top();
			q.pop();
			if(vis[x.l])
				continue;
			vis[x.r+1]=true;
			res=max(res,ed[x.l]=ed[x.r+1]);
			cnt[x.l]+=cnt[x.r+1];
			q.push(node(x.l,ed[x.l],cnt[x.l]));
		}
		ans[k]=res;
	}
	for(int i=1; i<=m; ++i)
		printf("%d ",ans[query[i]]);
	putchar('\n');
	return 0;
}


