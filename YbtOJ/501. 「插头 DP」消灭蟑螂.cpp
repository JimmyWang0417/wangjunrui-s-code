#include <bits/stdc++.h>
#define int ll
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
const int N=105,mod=1e9+7;
int cnt;
struct Matrix
{
	int g[N][N],n,m;
	Matrix(int _n=0,int _m=0):n(_n),m(_m)
	{
		memset(g,0,sizeof(g));
	}
	inline Matrix operator * (const Matrix &rhs)const
	{
		Matrix ans(n,rhs.m);
		for(int i=1; i<=ans.n; ++i)
			for(int j=1; j<=ans.m; ++j)
				for(int k=1; k<=m; ++k)
					(ans.g[i][j]+=(int)((ll)g[i][k]*rhs.g[k][j]))%=mod;
		return ans;
	}
	inline Matrix operator ^ (ll power)const
	{
		Matrix ans(cnt,cnt),a=*this;
		for(int i=1; i<=cnt; ++i)
			ans.g[i][i]=1;
		while(power)
		{
			if(power&1)
				ans=ans*a;
			a=a*a;
			power>>=1;
		}
		return ans;
	}
};
const int up[]= {0,0,1,1,1,0,0};
const int dn[]= {0,0,1,0,0,1,1};
const int lt[]= {0,1,0,1,0,1,0};
const int rt[]= {0,1,0,0,1,0,1};
int e[N][N];
int n,m;
int g[N];
inline void dfs(int pos)
{
	if(pos>m)
	{
		++cnt;
		for(int i=1; i<=m; ++i)
			e[cnt][i]=g[i];
		return;
	}
	for(int i=0; i<7; ++i)
	{
		if(pos==1&&lt[i])
			continue;
		if(pos==m&&rt[i])
			continue;
		if(rt[g[pos-1]]^lt[i])
			continue;
		g[pos]=i;
		dfs(pos+1);
	}
}
int p[N],tot;
struct Point
{
	int x,y;
} c[N],d[N];
int ccnt,dcnt;
int mp[N][N];
signed main()
{
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
	read(n,m,ccnt,dcnt);
	for(int i=1; i<=ccnt; ++i)
	{
		read(c[i].x,c[i].y);
		p[++tot]=c[i].x;
	}
	for(int i=1; i<=dcnt; ++i)
	{
		read(d[i].x,d[i].y);
		p[++tot]=d[i].x;
	}
	p[++tot]=1;
	sort(p+1,p+1+tot);
	tot=(int)(unique(p+1,p+1+tot)-p-1);
	for(int i=1; i<=ccnt; ++i)
		mp[(lower_bound(p+1,p+1+tot,c[i].x)-p)][c[i].y]=1;
	for(int i=1; i<=dcnt; ++i)
		mp[(lower_bound(p+1,p+1+tot,d[i].x)-p)][d[i].y]=2;
	dfs(1);
//	printf("%d\n",cnt);
	Matrix a(1,cnt),b(cnt,cnt),C;
	Matrix powb[60];
	for(int i=1; i<=cnt; ++i)
		for(int j=1; j<=cnt; ++j)
		{
			bool flag=true;
			for(int k=1; k<=m; ++k)
				if(dn[e[i][k]]^up[e[j][k]])
				{
					flag=false;
					break;
				}
			if(flag)
				++b.g[i][j];
		}
	for(int i=1; i<=cnt; ++i)
	{
		bool flag=true;
		for(int j=1; j<=m; ++j)
			if(up[e[i][j]]||(mp[1][j]==1&&e[i][j])||(mp[1][j]==2&&!e[i][j]))
			{
				flag=false;
				break;
			}
		if(flag)
			++a.g[1][i];
	}
	powb[0]=b;
	for(int i=0; i<59; ++i)
		powb[i+1]=powb[i]*powb[i];
//	a.print();
	for(int dep=2; dep<=tot; ++dep)
	{
		int power=p[dep]-p[dep-1]-1;
		assert(power>=0);
		for(int k=59; k>=0; --k)
			if((power>>k)&1)
				a=a*powb[k];
//		printf(":");
		C=b;
		for(int i=1; i<=cnt; ++i)
			for(int j=1; j<=m; ++j)
				if((mp[dep][j]==1&&e[i][j])||(mp[dep][j]==2&&!e[i][j]))
				{
					for(int k=1; k<=cnt; ++k)
						C.g[k][i]=0;
					break;
				}
//		printf("?");
		a=a*C;
//		printf("!");
	}
	int power=n-p[tot];
	int ans=0;
//	printf("%d\n",power);
//	(b^power).print();
	for(int k=59; k>=0; --k)
		if((power>>k)&1)
			a=a*powb[k];
//	a.print();
	for(int i=1; i<=cnt; ++i)
	{
		bool flag=true;
		for(int j=1; j<=m; ++j)
			if(dn[e[i][j]])
			{
				flag=false;
				break;
			}
		if(flag)
			ans=(ans+a.g[1][i])%mod;
	}
	printf("%lld\n",ans);
	return 0;
}

