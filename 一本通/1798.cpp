#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define re register
using namespace std;
namespace IO
{
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=getchar();
		while(!isdigit(ch)&&ch^'-')
			ch=getchar();
		if(ch=='-')
		{
			b=true;
			ch=getchar();
		}
		while(isdigit(ch))
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=getchar();
		}
		if(b)
			x=~x+1;
		return;
	}
	char Out[(int)2e5+10],*fe=Out,ch[25];
	int num=0;
	template<typename T>
	inline void write(T x)
	{
		if(!x)
			*fe++='0';
		if(x<0)
		{
			*fe++='-';
			x=-x;
		}
		while(x)
		{
			ch[++num]=x%10+'0';
			x/=10;
		}
		while(num)
			*fe++=ch[num--];
		*fe++='\n';
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
using namespace IO;
int f,a,b,c,d,p;
int T;
long long n;
struct matrix
{
	int n,m;
	int g[3][3];
	inline void init(int _n,int _m)
	{
		n=_n;
		m=_m;
		memset(g,0,sizeof(g));
		return;
	}
	inline matrix operator *(const matrix &b)
	{
		matrix res;
		res.init(n,b.m);
		for(re int i=1; i<=res.n; i++)
			for(re int j=1; j<=res.m; j++)
				for(re int k=1; k<=b.n; k++)
					res.g[i][j]=(res.g[i][j]+1ll*g[i][k]*b.g[k][j])%p;
		return res;
	}
	template<typename T>
	inline matrix operator ^ (T b)
	{
		matrix res,a=(*this);
		res.init(2,2);
		res.g[1][1]=res.g[2][2]=1;
		while(b)
		{
			if(b&1)
				res=res*a;
			a=a*a;
			b>>=1;
		}
		return res;
	}
} A,B;
inline void exgcd(int a,int b,int &d,int &x,int &y)
{
	if(!b)
	{
		d=a;
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,d,y,x);
	y-=a/b*x;
}
int main()
{
	IO::read(T);
	while(T--)
	{
		read(f);
		read(a);
		read(b);
		read(c);
		read(d);
		read(n);
		read(p);
		f=(f%p+p)%p;
		a=(a%p+p)%p;
		b=(b%p+p)%p;
		c=(c%p+p)%p;
		d=(d%p+p)%p;
		A.init(1,2);
		A.g[1][1]=f;
		A.g[1][2]=1;
		B.init(2,2);
		B.g[1][1]=a;
		B.g[2][1]=b;
		B.g[1][2]=c;
		B.g[2][2]=d;
		A=A*(B^n);
		int d,x,y;
		exgcd(A.g[1][2],p,d,x,y);
		x=(x%p+p)%p;
		write(1ll*A.g[1][1]*x%p);
	}
	flush();
	return 0;
}

