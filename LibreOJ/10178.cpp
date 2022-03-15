#include<cstdio>
#include<cstring>
#define re register
#define ll long long
#define max(x,y)((x)>(y)?(x):(y))
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
	return;
}
const int N=1e6+5;
bool ans[N];
int n,p[N],d[N],a[N<<1],q[N<<1],pos[N<<1];
ll sum[N<<1];
#define m (n<<1)
inline void solve()
{
	re int head=1,tail=0;
	memset(q,0,sizeof(q));
	for(re int i=1; i<=m; ++i)
		sum[i]=sum[i-1]+a[i];
	for(re int i=1; i<=m; ++i)
	{
		while(head<=tail&&q[head]<i-n+1)
			++head;
		while(head<=tail&&sum[q[tail]]>=sum[i])
			--tail;
		q[++tail]=i;
		if(i>=n&&sum[q[head]]-sum[i-n]>=0)
			ans[pos[i-n+1]]|=true;
	}
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(p[i]),read(d[i]);
		a[i]=a[i+n]=p[i]-d[i];
		pos[i]=pos[i+n]=i;
	}
	solve();
	re int cnt=1;
	a[1]=a[1+n]=p[1]-d[n];
	pos[1]=pos[1+n]=1;
	for(re int i=n; i>=2; i--)
	{
		++cnt;
		a[cnt]=a[cnt+n]=p[i]-d[i-1];
		pos[cnt]=pos[cnt+n]=i;
	}
	/*for(re int i=1;i<=n;++i)
	printf("%d %d\n",a[i],pos[i]);*/
	solve();
	for(re int i=1;i<=n;++i)
		puts(ans[i]?"TAK":"NIE");
	return 0;
}
