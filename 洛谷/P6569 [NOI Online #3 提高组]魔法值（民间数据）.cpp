#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ui unsigned int
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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=105;
struct Matrix
{
	int g[N][N],n,m;
	Matrix(int _n=0,int _m=0):n(_n),m(_m)
	{
		memset(g,0,sizeof(g));
	};
	inline Matrix operator *(const Matrix &rhs)const
	{
		Matrix ans=Matrix(n,rhs.m);
		for(re int i=1; i<=ans.n; ++i)
			for(re int j=1; j<=ans.m; ++j)
				for(re int k=1; k<=m; ++k)
					ans.g[i][j]=(ans.g[i][j]+g[i][k]*rhs.g[k][j])&1;
		return ans;
	}
} power[35];
int n,m,q;
ui val[N];
inline void work()
{
	ui day;
	read(day);
	if(day==0)
	{
		printf("%u\n",val[1]);
		return;
	}
	--day;
	Matrix f=Matrix(1,n);
	for(re int i=1; i<=n; ++i)
		f.g[1][i]=power[0].g[1][i];
	for(re int i=31; i>=0; --i)
		if((day>>i)&1)
			f=f*power[i];
	ui ans=0;
	for(re int i=1; i<=n; ++i)
		if(f.g[1][i])
			ans^=val[i];
	printf("%u\n",ans);
}
signed main()
{
	read(n,m,q);
	for(re int i=1; i<=n; ++i)
		read(val[i]);
	power[0]=Matrix(n,n);
	for(re int i=1; i<=m; ++i)
	{
		int u,v;
		read(u,v);
		power[0].g[u][v]=power[0].g[v][u]=1;
	}
	for(re int i=1; i<=31; ++i)
		power[i]=power[i-1]*power[i-1];
	while(q--)
		work();
	return 0;
}


