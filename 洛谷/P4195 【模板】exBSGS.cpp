#include<cstdio>
#include<cmath>
#include<map>
#include<cctype>
#include<unordered_map>
#define ll long long
#define re register
#define mul(a,b,p) (1ll*a*b%p)
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
	char Out[1<<30],*fe=Out,ch[25];
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
namespace ExBSGS
{
	template<typename T>
	inline T gcd(T a,T b)
	{
		return b?gcd(b,a%b):a;
	}
	unordered_map<ll,ll>Hash;
	inline ll exBSGS(ll a,ll b,ll p)
	{
		a%=p;
		b%=p;
		if(b==1)
			return 0;
		if(!b&&!a)
			return 1;
		if(!a)
			return -1;
		if(!b)
		{
			ll res=0,d;
			while((d=gcd(a,p))!=1)
			{
				++res;
				p/=d;
				if(p==1)
					return res;
			}
			return -1;
		}
		ll res=0,A=a,B=b,P=p,C=1,d;
		while((d=gcd(A,P))!=1)
		{
			if(B%d)
				return -1;
			P/=d;
			B/=d;
			C=mul(C,A/d,P);
			++res;
			if(C==B)
				return res;
		}
		Hash.clear();
		ll f=1,t=sqrt(P)+1;
		for(re int i=0; i<t; i++)
		{
			Hash[mul(f,B,P)]=i;
			f=mul(f,A,P);
		}
		int tf=f;
		f=mul(f,C,P);
		for(re int i=1; i<=t; i++)
		{
			if(Hash.find(f)!=Hash.end())
				return res+i*t-Hash[f];
			f=mul(f,tf,P);
		}
		return -1;
	}
}
int main()
{
	re ll a,b,p,ans;
	while(read(a),read(p),read(b),a&&b&&p)
	{
		ans=ExBSGS::exBSGS(a,b,p);
		if(~ans)
			printf("%lld\n",ans);
		else
			printf("No Solution\n");
	}
	return 0;
}
