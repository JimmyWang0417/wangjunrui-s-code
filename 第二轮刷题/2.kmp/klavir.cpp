#include<cstdio>
#define re register
#define Mod(x) (((x)%mod+mod)%mod)
using namespace std;
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
const int N=1e6+5,mod=1e9+7;
int n,m,a[N];
int power[N],p[N];
int ans;
inline void solve(int pre,int nxt)
{
	while(pre!=nxt)
	{
		if(pre>nxt)
		{
			ans=Mod(ans-power[pre]);
			pre=p[pre];
		}
		if(nxt>pre)
		{
			ans=Mod(ans+power[nxt]);
			nxt=p[nxt];
		}
	}
}
int main()
{
	read(n);
	read(m);
	power[0]=1;
	for(re int i=1; i<=m; ++i)
		power[i]=(int)(1ll*power[i-1]*n%mod);
	for(re int i=1; i<=m; ++i)
		read(a[i]);
	for(re int i=2,j; i<=m; ++i)
	{
		j=p[i-1];
		while(j&&a[j+1]!=a[i])
			j=p[j];
		if(a[j+1]==a[i])
			++j;
		p[i]=j;
	}
	for(re int i=1; i<=m; ++i)
	{
		solve(i-1,i);
		printf("%d\n",ans);
	}
	return 0;
}
