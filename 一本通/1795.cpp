#include<cstdio>
#include<cstring>
#include<cctype>
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
	char Out[25],*fe=Out,ch[25];
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
using IO::read;
using IO::write;
const int N=55,mod=1e9+7;
int h[N],inv[N],n,m;
struct matrix
{
	int n,m,g[N][N];
	inline void init(int _n,int _m)
	{
		memset(g,0,sizeof(g));
		n=_n;
		m=_m;
	}
	inline matrix operator *(const matrix &b)
	{
		matrix res;
		res.init(n,b.m);
		for(re int i=1; i<=res.n; i++)
			for(re int j=1; j<=res.m; j++)
				for(re int k=1; k<=b.n; k++)
					res.g[i][j]=(res.g[i][j]+1ll*g[i][k]*b.g[k][j])%mod;
		return res;
	}
	inline matrix operator ^ (int b)
	{
		matrix res=(*this),a=(*this);
		b--;
		while(b)
		{
			if(b&1)
				res=res*a;
			a=a*a;
			b>>=1;
		}
		return res;
	}
	inline void print()
	{
		for(re int i=1; i<=n; i++)
		{
			for(re int j=1; j<=m; j++)
				printf("%lld ",g[i][j]);
			putchar('\n');
		}
		return;
	}
} a,b;
int main()
{
	read(n);
	read(m);
	n>>=1;
	m>>=1;
	a.init(1,m);
	a.g[1][1]=1;
	b.init(m,m);
	inv[1]=1;
	for(re int i=2; i<=m+1; i++)
		inv[i]=(1ll*(mod-mod/i)*inv[mod%i])%mod;
	h[0]=2;
	for(re int i=1; i<=m-1; i++)
		h[i]=(1ll*h[i-1]*(4*i-2)%mod*inv[i+1])%mod;
	b.init(m,m);
	for(re int i=1; i<=m; i++)
		b.g[i][1]=h[i-1];
	for(re int i=1; i<=m-1; i++)
		b.g[i][i+1]=1;
	//b.print();
	a=a*(b^n);
	printf("%lld\n",a.g[1][1]);
	return 0;
}

