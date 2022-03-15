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
const int N=505,mod=998244353;
#define Mod(x) (int)(((x)%mod+mod)%mod)
int n;
using std::bitset;
struct Matrix
{
	bitset<N>g[N];
	inline Matrix operator *(const Matrix &rhs)const
	{
		Matrix now,ans;
		for(re int i=1; i<=n; ++i)
			for(re int j=1; j<=n; ++j)
				now.g[i][j]=rhs.g[j][i];
		for(re int i=1; i<=n; ++i)
			for(re int j=1; j<=n; ++j)
				ans.g[i][j]=(g[i]&now.g[j]).any();
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
//	inline void print()
//	{
//		for(re int i=1; i<=n; ++i)
//		{
//			for(re int j=1; j<=n; ++j)
//				printf(" %d",(int)g[i][j]);
//			putchar('\n');
//		}
//
//	}
};
int p[N];
signed main()
{
	int day;
	read(n,day);
	Matrix a;
	for(re int i=1; i<=n; ++i)
	{
		read(p[i]);
		int m,val;
		read(m);
		for(re int j=1; j<=m; ++j)
		{
			read(val);
			a.g[i][val]=1;
		}
	}
	Matrix ans=a^day;
//	ans.print();
	int answer=0;
	for(re int i=1; i<=n; ++i)
	{
//		printf("%d :",i);
		int res=1;
		for(re int j=1; j<=n; ++j)
			if(ans.g[i][j])
			{
				res=Mod(1ll*res*Mod(1-p[j]));
//				printf("%d ",Mod(1-p[j]));
			}
		answer=Mod(answer+Mod(1-res));
//		printf("\n%d\n",Mod(1-res));
	}
	printf("%d\n",answer);
	return 0;
}


