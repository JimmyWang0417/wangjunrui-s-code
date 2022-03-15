#include<cstdio>
#include<algorithm>
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
#define ll long long
const int N=1e6+10;
ll c[N],l[N],r[N],ans1,ans2;
int pos[N];
int a[N];
int n;
inline void update(ll *s,re int x,int v)
{
	for(; x<=n; x+=lowbit(x))
		s[x]+=v;
	return;
}
inline ll sum(ll *s,re int x)
{
	long long res=0;
	for(; x; x-=lowbit(x))
		res+=s[x];
	return res;
}
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
	{
		read(a[i]);
		pos[a[i]]=i;
		update(c,a[i],1);
		l[i]=sum(c,a[i]-1);
	}
	/*for(re int i=1; i<=n; i++)
		printf("%d\n",c[i]);*/
	fill(c,c+1+n,0);
	for(re int i=n; i>=1; i--)
	{
		update(c,a[i],1);
		r[i]=sum(c,n)-sum(c,a[i]);
		ans1+=r[i]*l[i];
	}
	fill(c,c+1+n,0);
	for(re int i=n; i>=1; i--)
	{
		const int &x=pos[i];
		long long cnt=sum(c,n)-sum(c,x);
		ans2+=cnt*(cnt-1)>>1;
		update(c,x,1);
	}
	printf("%lld\n",ans2-ans1);
	return 0;
}

