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
const int N=15;
double f[N][N],a[N],ans[N];
int n;
inline void Gauss()
{
	for(re int i=1; i<=n; ++i)
	{
		int pos=i;
		for(re int j=i+1; j<=n; ++j)
			if(fabs(f[pos][i])<fabs(f[j][i]))
				pos=i;
		if(i!=pos)
			std::swap(f[i],f[pos]);
		for(re int j=i+1; j<=n; ++j)
		{
			double tmp=f[j][i]/f[i][i];
			for(re int k=i; k<=n+1; ++k)
				f[j][k]-=tmp*f[i][k];
		}
	}
	for(re int i=n; i>=1; --i)
	{
		ans[i]=f[i][n+1];
		for(re int j=i+1; j<=n; ++j)
			ans[i]-=(f[i][j]*ans[j]);
		ans[i]/=f[i][i];
	}
}
using std::cin;
signed main()
{
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(re int i=1; i<=n; ++i)
		cin>>a[i];
	for(re int i=1; i<=n; ++i)
	{
		for(re int j=1; j<=n; ++j)
		{
			double val;
			cin>>val;
			f[i][j]=2*(val-a[j]);
			f[i][n+1]+=val*val-a[j]*a[j];
		}
	}
	Gauss();
	for(re int i=1; i<=n; ++i)
		printf("%.3lf ",ans[i]);
	putchar('\n');
	return 0;
}


