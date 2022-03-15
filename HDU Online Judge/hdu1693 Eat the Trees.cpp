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
const int N=15,S=(1<<12)+5;
int n,m,a[N][N];
ll f[2][S],*f0,*f1;
signed main()
{
	int T;
	read(T);
	for(int kase=1; kase<=T; ++kase)
	{
		read(n,m);
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j)
				read(a[i][j]);
		f0=f[0];
		f1=f[1];
		fill(f1,f1+(1<<(m+1)),0);
		f1[0]=1;
		for(int i=1; i<=n; ++i)
		{
			for(int j=1; j<=m; ++j)
			{
				swap(f0,f1);
				fill(f1,f1+(1<<(m+1)),0);
				for(int s=0; s<(1<<(m+1)); ++s)
				{
					int left=(s>>(j-1))&1,up=(s>>j)&1;
					if(a[i][j])
					{
						f1[s^(1<<(j-1))^(1<<j)]+=f0[s];
						if(left!=up)
							f1[s]+=f0[s];
					}
					else
					{
						if(!left&&!up)
							f1[s]+=f0[s];
					}
				}
			}
			swap(f0,f1);
			fill(f1,f1+(1<<(m+1)),0);
			for(int s=0; s<(1<<m); ++s)
				f1[s<<1]=f0[s];
		}
		printf("Case %d: There are %lld ways to eat the trees.\n",kase,f1[0]);
	}
	return 0;
}


