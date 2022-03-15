#include<cstdio>
#include<cstring>
#include<iostream>
#define re register
#define ll __int128
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
short printt[1010],cnt;
template<typename T>
inline void print(T &x)
{
	while(x)
	{
		printt[++cnt]=x%10;
		x/=10;
	}
	while(cnt)
		putchar('0'^printt[cnt--]);
}
const int N=4e7+5;
ll sum[N];
int p[N],l[N],r[N],b[N],q[N],f[N],n,x,y,z,m;
bool type;
#define solve(x) ((sum[x]<<1)-sum[f[x]])
inline void init()
{
	read(n),read(type);
	if(!type)
	{
		for(re int i=1,tmp; i<=n; ++i)
		{
			read(tmp);
			sum[i]=sum[i-1]+tmp;
		}
	}
	else
	{
		read(x),read(y),read(z),read(b[1]),read(b[2]),read(m);
		for(re int i=1; i<=m; ++i)
			read(p[i]),read(l[i]),read(r[i]);
		for(re int i=3; i<=n; ++i)
			b[i]=(1ll*b[i-1]*x+1ll*b[i-2]*y+z)%(1<<30);
		for(re int j=1; j<=m; ++j)
			for(re int i=p[j-1]+1,tmp; i<=p[j]; ++i)
			{
				tmp=b[i]%(r[j]-l[j]+1)+l[j];
				sum[i]=sum[i-1]+tmp;
			}
	}
}
inline void work()
{
	re int head=1,tail=1;
	for(re int i=1; i<=n; ++i)
	{
		while(head<tail&&solve(q[head+1])<=sum[i])
			++head;
		f[i]=q[head];
		while(head<=tail&&solve(q[tail])>=solve(i))
			--tail;
		q[++tail]=i;
	}
	ll ans=0;
	for(re int i=n; i; i=f[i])
		ans+=(sum[i]-sum[f[i]])*(sum[i]-sum[f[i]]);
	print(ans);
}
int main()
{
	init();
	work();
	return 0;
}
