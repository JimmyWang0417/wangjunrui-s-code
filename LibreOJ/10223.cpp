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
const int mod=1e4;
struct node
{
	int n,m,g[3][3];
} f,a,c;
inline node operator *(const node&a,const node&b)
{
	c.n=a.n;
	c.m=b.m;
	c.g[1][1]=c.g[1][2]=c.g[2][1]=c.g[2][2]=0ll;
	for(re int i=1; i<=c.n; i++)
		for(re int j=1; j<=c.m; j++)
			for(re int k=1; k<=a.m; k++)
				c.g[i][j]=(c.g[i][j]+(a.g[i][k])*(b.g[k][j]))%mod;
	return c;
}
inline node matrix_muli(node a,int b)
{
	node res;
	res.g[1][1]=res.g[2][2]=1ll;
	res.g[2][1]=res.g[1][2]=0ll;
	res.n=res.m=2;
	while(b)
	{
		if(b&1)
			res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
int n;
int main()
{
	while(read(n),(~n))
	{
		if(n<1)
		{
			printf("0\n");
			continue;
		}
		if(n<3)
		{
			printf("1\n");
			continue;
		}
		a.g[1][1]=a.g[1][2]=a.g[2][1]=f.g[1][1]=f.g[1][2]=f.n=1;
		f.m=a.m=a.n=2;
		a.g[2][2]=0ll;
		f=f*matrix_muli(a,n-2);
		printf("%d\n",f.g[1][1]);
	}
	return 0;
}

