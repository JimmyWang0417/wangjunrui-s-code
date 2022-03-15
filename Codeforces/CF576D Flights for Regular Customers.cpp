
// Problem : D. Flights for Regular Customers
// Contest : Codeforces - Codeforces Round #319 (Div. 1)
// URL : http://codeforces.com/problemset/problem/576/D
// Memory Limit : 256 MB
// Time Limit : 4000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=155;
int n,m;
struct Matrix
{
	std::bitset<N>g[N];
	inline Matrix operator *(const Matrix &_rhs)
	{
		Matrix ans,rhs;
		for(re int i=1; i<=n; ++i)
			for(re int j=1; j<=n; ++j)
				rhs.g[i][j]=_rhs.g[j][i];
		for(re int i=1; i<=n; ++i)
			for(re int j=1; j<=n; ++j)
				ans.g[i][j]=(g[i]&rhs.g[j]).any();
		return ans;
	}
	inline Matrix operator ^(int power)const
	{
		Matrix res,a=(*this);
		for(re int i=1; i<=n; ++i)
			res.g[i][i]=1;
		while(power)
		{
			if(power&1)
				res=res*a;
			a=a*a;
			power>>=1;
		}
		return res;
	}
} now,ans;
struct Edge
{
	int u,v,d;
	inline bool operator <(const Edge&rhs)const
	{
		return d<rhs.d;
	}
} a[N];
signed main()
{
	read(n,m);
	for(re int i=1; i<=m; ++i)
		read(a[i].u,a[i].v,a[i].d);
	std::sort(a+1,a+1+m);
	if(a[1].d)
	{
		printf("Impossible\n");
		return 0;
	}
	int cnt=0;
	for(re int i=1; i<=n; ++i)
		ans.g[i][i]=1;
	a[m+1].d=2147483647;
	for(re int i=1; i<=m; ++i)
	{
		now.g[a[i].u][a[i].v]=1;
		for(re int j=1; j<=i; ++j)
		{
			if(cnt>=a[i+1].d)
				break;
			ans=ans*now;
			++cnt;
			if(ans.g[1][n])
			{
				printf("%d\n",cnt);
				return 0;
			}
		}
		if(cnt<a[i+1].d)
			ans=ans*(now^(a[i+1].d-cnt));
		cnt=a[i+1].d;
	}
	printf("Impossible\n");
	return 0;
}


