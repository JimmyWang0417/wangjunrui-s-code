#include<cstdio>
#include<cstring>
#include<cassert>
#define re register
#define ll long long
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int mod=1e9+7;
struct Matrix
{
	int n,m,g[20][20];
	Matrix() {}
	Matrix(int nn=0,int mm=0):n(nn),m(mm)
	{
		memset(g,0,sizeof(g));
	}
	inline Matrix operator *(const Matrix &rhs)
	{
		Matrix c=Matrix(n,rhs.m);
		//assert(m==rhs.n);
		for(re int i=1; i<=c.n; ++i)
			for(re int j=1; j<=c.m; ++j)
				for(re int k=1; k<=m; ++k)
					c.g[i][j]=(c.g[i][j]+1ll*g[i][k]*rhs.g[k][j]%mod)%mod;
		return c;
	}
	inline void print()
	{
		for(re int i=1; i<=n; ++i)
		{
			for(re int j=1; j<=m; ++j)
				printf("%d ",g[i][j]);
			printf("\n");
		}

	}
};
inline Matrix operator^(Matrix a,ll b)
{
	Matrix ans=Matrix(a.n,a.m);
	for(re int i=1; i<=a.n; ++i)
		ans.g[i][i]=1;
	while(b)
	{
		if(b&1)
			ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
int main()
{
	static ll n;
	static int m;
	read(n);
	read(m);
	++m;
	if(n<=m)
	{
		printf("%d\n",n+1);
		return 0;
	}
	Matrix f=Matrix(1,m),a=Matrix(m,m);
	for(re int i=1; i<=m; ++i)
		f.g[1][i]=i+1;
	for(re int i=2; i<=m; ++i)
		a.g[i][i-1]=1;
	a.g[1][m]=a.g[m][m]=1;
	printf("%d\n",(f*(a^(n-m))).g[1][m]);
	return 0;
}
