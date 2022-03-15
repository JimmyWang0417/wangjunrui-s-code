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
inline void ckmax(int &x,int y)
{
	if(x<y)
		x=y;
}
using namespace std;
const int N=305;
struct node
{
	int l,p,r;
	inline bool operator < (const node &rhs)const
	{
		return p<rhs.p;
	}
} a[N];
int p[N],tot;
int dp[N][N],pre[N];
int n;
signed main()
{
	read(n);
	p[0]=-1e9;
	for(int i=1; i<=n; ++i)
	{
		int l;
		read(a[i].p,l);
		a[i].l=a[i].p-l;
		a[i].r=a[i].p+l;

		p[++tot]=a[i].l;
		p[++tot]=a[i].p;
		p[++tot]=a[i].r;
	}
	sort(p+1,p+1+tot);
	tot=(int)(unique(p+1,p+1+tot)-p-1);
//	for(int i=1; i<=tot; ++i)
//		printf("%d ",p[i]);
//	putchar('\n');
	for(int i=1; i<=n; ++i)
	{
		a[i].l=(int)(lower_bound(p+1,p+1+tot,a[i].l)-p);
		a[i].p=(int)(lower_bound(p+1,p+1+tot,a[i].p)-p);
		a[i].r=(int)(lower_bound(p+1,p+1+tot,a[i].r)-p);
	}
	sort(a+1,a+1+n);
	for(int i=1; i<=n; ++i)
	{
		memcpy(dp[i],dp[i-1],sizeof(dp[i]));
		memset(pre,0,sizeof(pre));
//		printf("%d %d %d\n",a[i].l,a[i].p,a[i].r);

		int where=a[i].p;
		pre[where]=dp[i-1][a[i].l]+p[a[i].p]-p[a[i].l];
		for(int j=i-1; j>=1; --j)
		{
			ckmax(where,a[j].r);
			ckmax(pre[where],dp[j-1][a[i].l]-p[a[i].l]+p[where]);
		}
		for(int j=tot; j>=a[i].l; --j)
		{
			ckmax(dp[i][j],pre[j]);
			ckmax(pre[j-1],pre[j]+p[j-1]-p[j]);
		}

		for(int j=a[i].p; j<=a[i].r; ++j)
			ckmax(dp[i][j],dp[i-1][a[i].p]+p[j]-p[a[i].p]);
		for(int j=1; j<=tot; ++j)
			ckmax(dp[i][j],dp[i][j-1]);

//		for(int j=1; j<=tot; ++j)
//			printf("%d ",dp[i][j]);
//		putchar('\n');
	}
	printf("%d\n",dp[n][tot]);
	return 0;
}


