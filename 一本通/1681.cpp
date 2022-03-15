#include<cstdio>
#include<map>
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
const int N=(1<<16)+10;
map<int,int>cnt;
int p,c,n,a[10010];
const int mod=1e9+7;
long long ans;
inline long long quickpow(long long a,int b)
{
	long long res=1ll;
	while(b)
	{
		if(b&1)
			res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res;
}
inline void search1(int t,long long yu)
{
	if(t==(n>>1)+1)
	{
		cnt[yu]++;
		return;
	}
	search1(t+1,yu);
	search1(t+1,(a[t]*yu)%p);
}
inline void search2(int t,long long yu)
{
	if(t>n)
	{
		ans=(ans+cnt[yu])%mod;
		return;
	}
	long long temp=yu*(quickpow(a[t]%p,p-2))%p;
	//ans=(ans+cnt[temp])% mod;
	search2(t+1,temp);
	search2(t+1,yu);
}
int main()
{
	read(n);
	read(p);
	read(c);
	if(c>=p)
	{
		printf("0\n");
		return 0;
	}
	for(re int i=1; i<=n; i++)
		read(a[i]);
	search1(1,1);
	//cnt[1]++;
	//printf("%d\n",cnt[1]);
	search2((n>>1)+1,c);
	if(c==1)
		ans--;
	printf("%lld\n",ans);
	return 0;
}
