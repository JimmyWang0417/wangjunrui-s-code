#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=3e6+5;
int n,m;
char str[N];
#define calc(i,j) ((i-1)*m+j)
char s[N];
int R[N],p[N];
bool l[N],r[N];
inline ll solve1()
{
	clear(R,1,3*m,0x3f);
	for(int now=1; now<=n; ++now)
	{
		int cnt;
		s[0]='~';
		s[cnt=1]='|';
		for(int i=1; i<=m; ++i)
		{
			s[++cnt]=str[calc(now,i)];
			s[++cnt]='|';
		}
		s[cnt+1]='\0';
//		printf("%s\n",s+1);
		clear(p,1,cnt,0);
		for(int i=1,maxx=0,mid=0; i<=cnt; ++i)
		{
			if(i<=maxx)
				p[i]=min(p[(mid<<1)-i],maxx-i+1);
			while(s[i-p[i]]==s[i+p[i]])
				++p[i];
			if(i+p[i]>maxx)
			{
				maxx=i+p[i]-1;
				mid=i;
			}
			R[i]=min(R[i],p[i]);
		}
//		for(int i=1; i<=cnt; ++i)
//			printf("%d ",R[i]);
//		putchar('\n');
	}
	for(int i=1; i<=m; ++i)
		p[i]=(R[i*2+1]-1)/2;
//	for(int i=1; i<=m; ++i)
//		printf("%d ",p[i]);
//	putchar('\n');
	l[0]=true;
	int last=0;
	for(int i=1; i<m; ++i)
		if(i-p[i]<=last)
		{
			last=i;
			l[i]=true;
		}
	r[m]=true;
	last=m;
	for(int i=m-1; i>=1; --i)
		if(i+p[i]>=last)
		{
			last=i;
			r[i]=true;
		}
	ll ans=0;
	int res=1;
	for(int i=1; i<=m; ++i)
	{
		ans+=r[i]*res;
		res+=l[i];
	}
	clear(l,0,m,0);
	clear(r,0,m,0);
	return ans;
}
inline ll solve2()
{

	clear(R,1,3*n,0x3f);
	for(int now=1; now<=m; ++now)
	{
		int cnt;
		s[0]='~';
		s[cnt=1]='|';
		for(int i=1; i<=n; ++i)
		{
			s[++cnt]=str[calc(i,now)];
			s[++cnt]='|';
		}
		s[cnt+1]='\0';
		clear(p,1,cnt,0);
		for(int i=1,maxx=0,mid=0; i<=cnt; ++i)
		{
			if(i<=maxx)
				p[i]=min(p[(mid<<1)-i],maxx-i+1);
			while(s[i-p[i]]==s[i+p[i]])
				++p[i];
			if(i+p[i]>maxx)
			{
				maxx=i+p[i]-1;
				mid=i;
			}
			R[i]=min(R[i],p[i]);
		}
//		printf("%s\n",s+1);
	}
	for(int i=1; i<=n; ++i)
		p[i]=(R[i*2+1]-1)/2;
//	for(int i=1; i<=n; ++i)
//		printf("%d ",p[i]);
//	putchar('\n');
	l[0]=true;
	int last=0;
	for(int i=1; i<n; ++i)
		if(i-p[i]<=last)
		{
			last=i;
			l[i]=true;
		}
	r[n]=true;
	last=n;
	for(int i=n-1; i>=1; --i)
		if(i+p[i]>=last)
		{
			last=i;
			r[i]=true;
		}
	ll ans=0;
	int res=1;
	for(int i=1; i<=n; ++i)
	{
		ans+=r[i]*res;
		res+=l[i];
	}
	clear(l,0,n,0);
	clear(r,0,n,0);
	return ans;
}
signed main()
{
	freopen("paper.in","r",stdin),freopen("paper.out","w",stdout);
	read(n,m);
	char s=getchar();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			while(!(s>='a'&&s<='z'))
				s=getchar();
			str[calc(i,j)]=s;
			s=getchar();
		}
	printf("%lld\n",solve1()*solve2());
	return 0;
}

