#include<cmath>
#include<cstdio>
#include<cstring>
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
	double x,y;	//x表示实部，y表示虚部
	complex(double xx=0,double yy=0):x(xx),y(yy) {}
	inline complex operator + (const complex &rhs)const
	{
		return complex(x+rhs.x,y+rhs.y);
	}
	inline complex operator - (const complex &rhs)const
	{
		return complex(x-rhs.x,y-rhs.y);
	}
	inline complex operator * (const complex &rhs)const
	{
		return complex(x*rhs.x-y*rhs.y,x*rhs.y+y*rhs.x);
	}
};
int rk[maxn],limit,n,m;
complex a[maxn],b[maxn];
char str[maxn];
int ans[maxn];
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
	scanf("%s",str);
	n=strlen(str)-1;
	for(re int i=0; i<=n; ++i)
		a[i].x=str[n-i]-'0';
//	for(re int i=0; i<=n; ++i)
//		printf("%d",(int)a[i].x);
	scanf("%s",str);
	m=strlen(str)-1;
	for(re int i=0; i<=m; ++i)
		b[i].x=str[m-i]-'0';
//	for(re int i=0; i<=m; ++i)
//		printf("%d",(int)b[i].x);
	re int len=0;
	for(limit=1; limit<=n+m; ++len,limit<<=1);
	for(re int i=0; i<limit; ++i)
		rk[i]=(rk[i>>1]>>1)|((i&1)<<(len-1));
	FFT(a,1);
	FFT(b,1);
	for(re int i=0; i<=limit; ++i)
		a[i]=a[i]*b[i];
	FFT(a,-1);
	for(re int i=0; i<=n+m; ++i)
		ans[i]=(int)(a[i].x/limit+0.5);
	for(re int i=0; i<n+m; ++i)
	{
		ans[i+1]+=ans[i]/10;
		ans[i]%=10;
	}
	for(re int i=n+m; i; --i)
		printf("%d",ans[i]);
	printf("%d\n",ans[0]);
	return 0;
}
