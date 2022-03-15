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
const int N=2e5+5;
int n,k;
struct node
{
	int val,id;
	inline bool operator <(const node &rhs)const
	{
		return val<rhs.val;
	}
} a[N];
int c[N];
inline void update(int pos,int val)
{
	for(int i=pos; i<=n; i+=lowbit(i))
		c[i]+=val;
}
inline int query(int pos)
{
	int res=0;
	for(int i=pos; i; i-=lowbit(i))
		res+=c[i];
	return res;
}
inline int query(int l,int r)
{
	return query(r)-query(l-1);
}
#define rank Rank
int rank[N];
int dp[N];
int ans[N];
signed main()
{
	freopen("fable.in","r",stdin);
	freopen("fable.out","w",stdout);
	read(n,k);
	for(int i=1; i<=n; ++i)
	{
		read(a[i].val);
		a[i].id=i;
	}
	sort(a+1,a+1+n);
	rank[a[1].id]=1;
	for(int i=2; i<=n; ++i)
		rank[a[i].id]=(a[i].val==a[i-1].val?rank[a[i-1].id]:i);
	for(int i=1; i<=n; ++i)
	{
		update(rank[i],1);
		dp[i]=query(rank[i]+1,n);
		if(dp[i]>=k)
			ans[i-k]=a[rank[i]].val;
	}
	int head=1;
	for(int i=1; i<=n; ++i)
		if(dp[a[i].id]<k)
		{
			while(ans[head])
				++head;
			ans[head]=a[i].val;
		}
	for(int i=1; i<=n; ++i)
		printf("%d\n",ans[i]);
	return 0;
}


