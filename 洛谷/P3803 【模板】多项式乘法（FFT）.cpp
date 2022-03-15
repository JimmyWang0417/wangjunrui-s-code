#include<cmath>
#include<cstdio>
#include<algorithm>
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
template<typename T>
inline T getread()
{
	T x;
	read(x);
	return x;
}
const double PI=acos(-1.0);
const int maxn=4e6+5;
struct complex
{
	double a,b;
	complex(double aa=0,double bb=0):a(aa),b(bb) {}
	inline complex operator + (const complex &rhs)const
	{
		return complex(a+rhs.a,b+rhs.b);
	}
	inline complex operator - (const complex &rhs)const
	{
		return complex(a-rhs.a,b-rhs.b);
	}
	inline complex operator * (const complex &rhs)const
	{
		return complex(a*rhs.a-b*rhs.b,a*rhs.b+b*rhs.a);
	}
};
int rk[maxn],limit,n,m;
complex a[maxn],b[maxn];
inline void FFT(complex *a,int type)
{
	for(re int i=0; i<limit; ++i)
		if(i<rk[i])
			swap(a[i],a[rk[i]]);
	for(re int mid=1; mid<limit; mid<<=1)
	{
#define len (mid<<1)
		complex Wn(cos(PI/mid),type*sin(PI/mid));
		for(re int j=0; j<limit; j+=len)
		{
			complex w(1.0,0.0);
			for(re int i=0; i<mid; ++i,w=w*Wn)
			{
				complex x=a[i+j],y=a[i+j+mid]*w;
				a[i+j]=x+y;
				a[i+j+mid]=x-y;
			}
		}
#undef len
	}
}
int main()
{
	read(n);
	read(m);
	for(re int i=0; i<=n; ++i)
		a[i].a=getread<int>();
	for(re int i=0; i<=m; ++i)
		b[i].a=getread<int>();
	re int len=0;
	for(limit=1; limit<=n+m; limit<<=1,++len);
	for(re int i=0; i<limit; ++i)
		rk[i]=(rk[i>>1]>>1)|((i&1)<<(len-1));
	FFT(a,1);
	FFT(b,1);
	for(re int i=0; i<=limit; ++i)
		a[i]=a[i]*b[i];
	FFT(a,-1);
	for(re int i=0; i<=n+m; ++i)
		printf("%d ",(int)(a[i].a/limit+0.5));
	printf("\n");
	return 0;
}
