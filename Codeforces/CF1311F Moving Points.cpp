#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#define re register
#define int long long
using namespace std;
const int N=2e5+5;
int n,len,mapv[N];
struct rec
{
	int a;
	int t;
	inline operator < (const rec&rhs)const
	{
		return a<rhs.a;
	}
} w[N];
inline void discrete()
{
	sort(mapv+1,mapv+1+len);
	len=unique(mapv+1,mapv+1+len)-mapv-1;
}
int c[N][2];
inline void add(int x,int val)
{
	for(; x<=n; x+=x&-x)
		c[x][0]++,
		c[x][1]+=val;
}
inline long long ask(int x,int k)
{
	long long ans=0;
	for(; x; x-=x&-x)ans+=c[x][k];
	return ans;
}
int ans;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(re int i=1; i<=n; i++)
		cin>>w[i].a;
	for(re int i=1; i<=n; i++)
	{
		cin>>w[i].t;
		mapv[++len]=w[i].t;
	}
	sort(w+1,w+1+n);
	sort(mapv+1,mapv+1+len);
	len=unique(mapv+1,mapv+1+len)-mapv-1;
	for(re int  i=1; i<=n; i++)
	{
		int mapval=lower_bound(mapv+1,mapv+1+len,w[i].t)-mapv;
		ans+=w[i].a*ask(mapval,0)-ask(mapval,1);
		add(mapval,w[i].a);
	}
	printf("%lld\n",ans);
	return 0;
}
