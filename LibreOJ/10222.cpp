#include<cstdio>
#define re register
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
int n,mod;
struct Matrix
{
	int n,m;
	long long g[5][5];
} res,f,a,c;
inline Matrix operator * (const Matrix&a,const Matrix&b)
{
	c.n=a.n;
	c.m=b.m;
	for(re int i=1; i<=c.n; i++)
		for(re int j=1; j<=c.m; j++)
			c.g[i][j]=0;
	for(re int i=1; i<=c.n; i++)
		for(re int j=1; j<=c.m; j++)
			for(re int k=1; k<=a.m; k++)
				c.g[i][j]=(c.g[i][j]+a.g[i][k]*b.g[k][j])%mod;
	return c;
}
inline Matrix operator ^ (Matrix a,int b)
{
	res.n=res.m=4;
	for(re int i=1; i<=4; i++)
		for(re int j=1; j<=4; j++)
			res.g[i][j]=(i==j);
	while(b)
	{
		if(b&1)
			res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
inline void print(Matrix a)
{
	for(re int i=1; i<=a.n; i++)
	{
		for(re int j=1; j<=a.m; j++)printf("%d ",a.g[i][j]);
		putchar('\n');
	}
	return;
}
int main()
{
	read(n);
	read(mod);
	if(n==1)
	{
		printf("%d\n",n%mod);
		return 0;
	}
	f.n=1;
	f.m=4;
	for(re int i=1; i<=4; i++)
		f.g[1][i]=1ll;
	f.g[1][1]=0ll;
	a.m=a.n=4;
	a.g[1][1]=a.g[2][1]=a.g[2][2]=a.g[3][2]=a.g[3][3]=a.g[3][4]=a.g[4][3]=1ll;
	f=f*(a^(n-1));
	//print(f);
	printf("%d\n",(f.g[1][2]*n-f.g[1][1]+mod)%mod);
	return 0;
}

