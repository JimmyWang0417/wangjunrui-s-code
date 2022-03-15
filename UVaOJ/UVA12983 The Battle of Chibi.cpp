#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define re register
#define ll long long
#define ull unsigned long long
#define lowbit(x) (x&(-x))
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
const int N=1e3+5,mod=1e9+7;
int c[N][N],n,m,tot;
inline void update(int x,int pos,int val)
{
	for(re int i=pos; i<=tot; i+=lowbit(i))
		(c[x][i]+=val)%=mod;
}
inline int query(int x,int pos)
{
	int res=0;
	for(re int i=pos; i; i-=lowbit(i))
		(res+=c[x][i])%=mod;
	return res;
}
int a[N],p[N];
inline void work()
{
}
signed main()
{
	int T;
	read(T);
	for(re int kase=1; kase<=T; ++kase)
	{
		read(n,m);
		for(re int i=1; i<=n; ++i)
		{
			read(a[i]);
			p[i]=a[i];
		}
		sort(p+1,p+1+n);
		tot=(int)(unique(p+1,p+1+n)-p-1);
		for(re int i=1; i<=n; ++i)
		{
			a[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
			update(1,a[i],1);
			for(re int j=1; j<m; ++j)
			{
				int ans=query(j,a[i]-1);
				update(j+1,a[i],ans);
//				printf("%d dp[%d][%d]=%d\n",a[i],i,j+1,ans);
			}
		}
		printf("Case #%d: %d\n",kase,query(m,tot));
		memset(c,0,sizeof(c));
	}
	return 0;
}
