#include <cstdio>
#include <cstring>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
}
int mod;
struct Matrix
{
	int n,m;
	int g[3][3];
	Matrix(int nn=0,int mm=0)
	{
		n=nn,m=mm;
		memset(g,0,sizeof(g));
	}
	inline Matrix operator * (const Matrix &rhs)const
	{
		Matrix ans=Matrix(n,rhs.m);
		for(re int i=1; i<=ans.n; ++i)
			for(re int j=1; j<=ans.m; ++j)
				for(re int k=1; k<=m; ++k)
					ans.g[i][j]=(int)((ans.g[i][j]+1ll*g[i][k]*rhs.g[k][j])%mod);
		return ans;
	}
	inline Matrix operator ^ (int power)const
	{
		Matrix res=Matrix(n,m),a=*this;
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
	inline void print()
	{
		for(re int i=1; i<=n; ++i)
		{
			for(re int j=1; j<=m; ++j)
				printf("%d ",g[i][j]);
			putchar('\n');
		}
	}
} f,a;
int n,a1,a2,p,q;
int main()
{
	f=Matrix(1,2);
	read(p),read(q),read(a1),read(a2),read(n),read(mod);
	f.g[1][1]=a2,f.g[1][2]=a1;
	a=Matrix(2,2);
	a.g[1][1]=p,a.g[2][1]=q;
	a.g[1][2]=1;
//	a.print();
	if(n==1)
	{
		printf("%d\n",a1);
		return 0;
	}
	if(n==2)
	{
		printf("%d\n",a2);
		return 0;
	}
	printf("%d\n",(f*(a^(n-2))).g[1][1]);
	return 0;
}
