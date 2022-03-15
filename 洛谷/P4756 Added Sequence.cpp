#include<cstdio>
#include<cmath>
#include<cctype>
#define re register
using namespace std;
namespace IO
{
	const int SIZE=1<<25;
	char ibuf[SIZE],*iS,*iT;
#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=gc();
		while(!isdigit(ch)&&ch^'-')
			ch=gc();
		if(ch=='-')
		{
			b=true;
			ch=gc();
		}
		while(isdigit(ch))
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=gc();
		}
		if(b)
			x=~x+1;
		return;
	}
#undef gc
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
	inline void write_str(char *s)
	{
		for(re int i=0; s[i]; i++)
			*fe++=s[i];
		*fe++='\n';
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
using namespace IO;
#define ll long long
const int N=200010;
int n,m,a[N];
ll x[N],pre[N],max_st[N],min_st[N],max_top=1,min_top=1,maxi,mini,maxx,minn;
inline bool check(int a,int b,int c)
{
	return (pre[a]-pre[b])*(b-c)<=(pre[b]-pre[c])*(a-b);
}
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=n; i++)
	{
		read(a[i]);
		pre[i]=pre[i-1]+a[i];
	}
	for(re int i=1; i<=n; i++)
	{
		while(max_top>1&&check(max_st[max_top-1],max_st[max_top],i))
			max_top--;
		max_st[++max_top]=i;
		while(min_top>1&&!check(min_st[min_top-1],min_st[min_top],i))
			min_top--;
		min_st[++min_top]=i;
	}
	re ll l,r,mid;
	for(re int i=1; i<=m; i++)
	{
		read(x[i]);
		x[i]=(x[i]+x[i-1])%(4*n+1)-2*n;
		l=2,r=max_top,maxi=0;
		while(l<=r)
		{
			mid=(l+r)/2;
			if((double)(pre[max_st[mid-1]]-pre[max_st[mid]])/(double)(max_st[mid-1]-max_st[mid])>=-x[i])
			{
				maxi=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		maxx=pre[max_st[maxi]]+x[i]*max_st[maxi];
		l=2,r=min_top,mini=0;
		while(l<=r)
		{
			mid=(l+r)/2;
			if((double)(pre[min_st[mid-1]]-pre[min_st[mid]])/(double)(min_st[mid-1]-min_st[mid])<=-x[i])
			{
				mini=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		minn=pre[min_st[mini]]+x[i]*min_st[mini];
		write(x[i]=fabs(maxx-minn));
	}
	flush();
	return 0;
}
