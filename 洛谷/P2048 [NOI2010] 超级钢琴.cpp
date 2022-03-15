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
const int N=5e5+5;
int n,k,L,R,sum[N],a[N];
struct node
{
	int l,r,x,y;
	node(int _l=0,int _r=0,int _x=0,int _y=0):l(_l),r(_r),x(_x),y(_y) {}
	inline bool operator <(const node &rhs)const
	{
		return sum[y]-sum[x]<sum[rhs.y]-sum[rhs.x];
	}
};
int f[N][25],LOG[N];
inline int calcmin(int l,int r)
{
	return sum[l]<sum[r]?l:r;
}
inline int query(int l,int r)
{
	int len=LOG[r-l+1];
	return calcmin(f[l][len],f[r-(1<<len)+1][len]);
}
signed main()
{
	read(n,k,L,R);
	LOG[0]=-1;
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		f[i][0]=i;
		sum[i]=sum[i-1]+a[i];
		LOG[i]=LOG[i>>1]+1;
	}
	LOG[n+1]=LOG[(n+1)>>1]+1;
	for(int i=1; i<=20; ++i)
		for(int j=0; j+(1<<i)-1<=n; ++j)
			f[j][i]=calcmin(f[j][i-1],f[j+(1<<(i-1))][i-1]);
	priority_queue<node>q;
	for(int i=1; i<=n; ++i)
	{
		int l=i-R,r=i-L;
		l=max(l,0);
		if(r<l)
			continue;
		int x=query(l,r),y=i;
//		printf("%d %d %d %d\n",i,l,r,x);
		q.push(node(l,r,x,y));
	}
	ll ans=0;
	while(k--)
	{
		node u=q.top();
		q.pop();
		ans+=sum[u.y]-sum[u.x];
//		printf(" %d %d %d\n",u.x+1,u.y,sum[u.y]-sum[u.x]);
		if(u.l<u.x)
		{
			q.push(node(u.l,u.x-1,query(u.l,u.x-1),u.y));
		}
		if(u.x<u.r)
		{
			q.push(node(u.x+1,u.r,query(u.x+1,u.r),u.y));
		}
	}
	printf("%lld\n",ans);
	return 0;
}


