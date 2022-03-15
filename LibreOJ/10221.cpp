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
struct node
{
	int n,m;
	long long g[4][4];
} c,f,a;
int n,mod;
inline node operator * (const node&a,const node&b)
{
	c.n=a.n;
	c.m=b.m;
	for(re int i=1; i<=3; i++)
		for(re int j=1; j<=3; j++)
			c.g[i][j]=0ll;
	for(re int i=1; i<=c.n; i++)
		for(re int j=1; j<=c.m; j++)
			for(re int k=1; k<=a.m; k++)
				c.g[i][j]=(c.g[i][j]+a.g[i][k]*b.g[k][j])%mod;
	return c;
}
inline node matrix_muli(node a,int b)
{
	node res;
	res.n=res.m=3;
	for(re int i=1; i<=res.n; i++)
		for(re int j=1; j<=res.m; j++)
			if(i==j)
				res.g[i][j]=1ll;
			else
				res.g[i][j]=0ll;
	while(b)
	{
		if(b&1)
			res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
int main()
{
	read(n);
	read(mod);
	if(n==1)
	{
		printf("1\n");
		return 0;
	}
	for(re int i=1; i<=3; i++)
		a.g[i][1]=1ll;
	a.g[2][2]=a.g[3][2]=a.g[2][3]=f.g[1][2]=f.g[1][3]=1ll;
	a.m=a.n=f.m=3;
	f.n=1;
	f.g[1][1]=2;
	printf("%d\n",(f*matrix_muli(a,n-2)).g[1][1]);
	return 0;
}

