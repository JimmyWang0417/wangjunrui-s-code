#include<cstdio>
#define re register
#define lowbit(x) (x&(-x))
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
const int N=2e6+10;
const long long mod=20170927;
long long x[N],y[N],x2[N],y2[N],xy[N];
int n,m;
inline void update(int a,long long b,long long c)
{
	long long tx2=x[a]*x[a]%mod,ty2=y[a]*y[a]%mod,txy=x[a]*y[a]%mod;
	int tmp=a;
	while(a<=n)
	{
		x2[a]=(x2[a]-tx2+mod)%mod;
		y2[a]=(y2[a]-ty2+mod)%mod;
		xy[a]=(xy[a]-txy+mod)%mod;
		a+=lowbit(a);
	}
	a=tmp;
	tx2=b*b%mod;
	ty2=c*c%mod;
	txy=b*c%mod;
	while(a<=n)
	{
		x2[a]=(x2[a]+tx2)%mod;
		y2[a]=(y2[a]+ty2)%mod;
		xy[a]=(xy[a]+txy)%mod;
		a+=lowbit(a);
	}
	x[tmp]=b;
	y[tmp]=c;
}
inline long long query(int l,int r)
{
	long long sumx2=0,sumy2=0,sumxy=0;
	while(r)
	{
		sumx2=(sumx2+x2[r])%mod;
		sumy2=(sumy2+y2[r])%mod;
		sumxy=(sumxy+xy[r])%mod;
		r-=lowbit(r);
	}
	while(l)
	{
		sumx2=(sumx2-x2[l]+mod)%mod;
		sumy2=(sumy2-y2[l]+mod)%mod;
		sumxy=(sumxy-xy[l]+mod)%mod;
		l-=lowbit(l);
	}
	long long ans=(sumx2*sumy2)%mod;
	ans=(ans-(sumxy*sumxy)%mod+mod)%mod;
	return ans;
}
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=n; i++)
	{
		read(x[i]);
		read(y[i]);
		int a=i;
		const long long tx2=x[i]*x[i]%mod,ty2=y[i]*y[i]%mod,txy=x[i]*y[i]%mod;
		while(a<=n)
		{
			x2[a]=(x2[a]+tx2)%mod;
			y2[a]=(y2[a]+ty2)%mod;
			xy[a]=(xy[a]+txy)%mod;
			a+=lowbit(a);
		}
	}
	int op;
	long long a,b,c;
	while(m--)
	{
		read(op);
		read(a);
		read(b);
		if(op==1)
		{
			read(c);
			update(a,b,c);
		}
		else
			printf("%lld\n",query(a-1,b));
	}
	return 0;
}

