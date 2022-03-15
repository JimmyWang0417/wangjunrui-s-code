#include <cmath>
#include <cstdio>
#include <vector>
#include <cctype>
#include <cstring>
#include <algorithm>
#define re register
using namespace std;
const int N=1e5+5,M=2200;
namespace IO
{
	const int SIZE=15*N+25*N;
	char ibuf[SIZE],*iS,*iT;
#define gc() (char)(iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
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
	char Out[15*N],*fe=Out,ch[25];
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
			ch[++num]=(char)(x%10+'0');
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
int num,block,l[M],r[M];
int belong[N];
int n,a[N],p[N],tot;
int f[M][M];
vector<int>cnt[N];
inline void init()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}
	sort(p+1,p+1+n);
	tot=(int)(unique(p+1,p+1+n)-p-1);
	for(re int i=1; i<=n; ++i)
	{
		a[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
		cnt[a[i]].push_back((int)i);
	}
}
int sum[N];
inline void build()
{
	block=(int)pow(n,1.0/3.0);
	num=n/block;
	if(n%block)
		++num;
	for(re int i=1; i<=num; ++i)
	{
		l[i]=(i-1)*block+1;
		r[i]=i*block;
	}
	r[num]=n;
	for(re int i=1; i<=n; ++i)
		belong[i]=(i-1)/block+1;
	for(re int i=1; i<=num; ++i)
	{
		int res=0;
		for(re int j=i; j<=num; ++j)
		{
			for(re int k=l[j]; k<=r[j]; ++k)
			{
				++sum[a[k]];
				if(sum[a[k]]>sum[res]||(sum[a[k]]==sum[res]&&a[k]<res))
					res=a[k];
			}
			f[i][j]=res;
		}
		memset(sum,0,sizeof(sum));
	}
}
inline int Count(int x,int y,int val)
{
	return (int)(upper_bound(cnt[val].begin(),cnt[val].end(),y)-lower_bound(cnt[val].begin(),cnt[val].end(),x));
}
inline int query(int x,int y)
{
	if(belong[x]==belong[y])
	{
		int res=0,maxx=0;
		for(re int i=x; i<=y; ++i)
		{
			int now=Count(x,y,a[i]);
			if(now>maxx||(now==maxx&&a[i]<res))
			{
				res=a[i];
				maxx=now;
			}
		}
	}
	int res=f[belong[x]+1][belong[y]-1],maxx=Count(x,y,res);
//	printf("%d\n",res);
	for(re int i=x; i<=r[belong[x]]; ++i)
	{
		int now=Count(x,y,a[i]);
		if(now>maxx||(now==maxx&&a[i]<res))
		{
			res=a[i];
			maxx=now;
		}
	}
	for(re int i=l[belong[y]]; i<=y; ++i)
	{
		int now=Count(x,y,a[i]);
		if(now>maxx||(now==maxx&&a[i]<res))
		{
			res=a[i];
			maxx=now;
		}
	}
	return res;
}
inline void solve()
{
	for(re int i=1; i<=n; ++i)
	{
		int x,y;
		read(x),read(y);
		write(p[query(x,y)]);
	}
	IO::flush();
}
int main()
{
	init();
	build();
	solve();
	return 0;
}

