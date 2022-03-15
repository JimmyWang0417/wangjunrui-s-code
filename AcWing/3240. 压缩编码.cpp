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
const int N=1005;
int n,sum[N];
int f[N][N];
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
	{
		read(sum[i]);
		sum[i]+=sum[i-1];
	}
	for(int len=2; len<=n; ++len)
	{
		for(int l=1; l+len-1<=n; ++l)
		{
			int r=l+len-1;
			f[l][r]=1e9;
			for(int k=l; k<r; ++k)
				f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]+sum[r]-sum[l-1]);
		}
	}
//	for(int i=1; i<=n; ++i)
//	{
//		for(int j=i; j<=n; ++j)
//			printf("%lld ",f[i][j]);
//		putchar('\n');
//	}
	printf("%d\n",f[1][n]);
	return 0;
}


