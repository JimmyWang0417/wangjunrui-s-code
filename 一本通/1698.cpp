#include<cstdio>
#include<cstring>
#include<cctype>
#define re register
using namespace std;
namespace IO
{
	const int SIZE=1<<30;
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
	char Out[1<<25],*fe=Out,ch[25];
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
	}
	inline void write_char(char s)
	{
		*fe++=s;
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
using namespace IO;
#define solve(x,len) (x<len?x:0)
const int LEN=1e6+10;
int a[LEN],b[LEN],p[LEN],t[LEN],s[LEN],n,m,last[LEN],T,C,ans[LEN],top;
inline void pre()
{
	p[1]=0;
	for(re int i=1,j=0; i<m; i++)
	{
		while(j&&solve(t[i+1],j+1)!=solve(t[j+1],j+1))
			j=p[j];
		if(solve(t[i+1],j+1)==solve(t[j+1],j+1))
			j++;
		p[i+1]=j;
	}
}
inline void kmp()
{
	for(re int i=0,j=0; i<n; i++)
	{
		while(j&&solve(s[i+1],j+1)!=solve(t[j+1],j+1))
			j=p[j];
		if(solve(s[i+1],j+1)==solve(t[j+1],j+1))
			j++;
		if(j==m)
		{
			ans[++top]=i+1-m+1;
			j=p[j];
		}
	}
	write(top);
	write_char('\n');
	for(re int i=1; i<=top; i++)
	{
		write(ans[i]);
		write_char(' ');
	}
	write_char('\n');
	top=0;
}
int main()
{
	read(T);
	read(C);
	while(T--)
	{
		read(n);
		read(m);
		for(re int i=1; i<=n; i++)
		{
			read(a[i]);
			s[i]=i-last[a[i]];
			last[a[i]]=i;
		}
		memset(last,0,sizeof(last));
		for(re int i=1; i<=m; i++)
		{
			read(b[i]);
			t[i]=i-last[b[i]];
			last[b[i]]=i;
		}
		memset(last,0,sizeof(last));
		/*for(re int i=1; i<=n; i++)
			printf("%d %d\n",s[i],t[i]);*/
		pre();
		kmp();
		/*for(re int i=1; i<=m; i++)
			printf("%d ",p[i]);
		putchar('\n');*/
	}
	flush();
	return 0;
}
