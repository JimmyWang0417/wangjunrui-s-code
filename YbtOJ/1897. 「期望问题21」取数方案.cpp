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
const int mod=998244353;
vector<pair<int,int> >add[N],del[N];
int n,m,a[N];
int cnt[N],len[N];
ll inv[N];
struct Tree_array
{
	int sum[N];
	inline void update(int pos,int val)
	{
		for(int i=pos; i<=1e5; i+=lowbit(i))
			sum[i]+=val;
	}
	inline int query(int pos)
	{
		int res=0;
		for(int i=pos; i; i-=lowbit(i))
			res+=sum[i];
		return res;
	}
} tree;
signed main()
{
	freopen("date.in","r",stdin);
	freopen("date.out","w",stdout);
	read(n,m);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=1; i<=m; ++i)
	{
		int l,r,f;
		read(l,r,f);
		del[l-1].push_back(make_pair(f,i));
		add[r].push_back(make_pair(f,i));
		len[i]=r-l+1;
	}
	inv[1]=1;
	for(int i=2; i<=n; ++i)
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1; i<=n; ++i)
	{
		tree.update(a[i],1);
		for(auto v:del[i])
			cnt[v.second]-=tree.query(1e5)-tree.query(v.first-1);
		for(auto v:add[i])
			cnt[v.second]+=tree.query(1e5)-tree.query(v.first-1);
	}
	for(int i=1; i<=m; ++i)
		printf("%lld\n",cnt[i]*inv[len[i]]%mod*inv[len[i]-cnt[i]+1]%mod);
	return 0;
}


