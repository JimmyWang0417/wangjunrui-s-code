#include<cstdio>
#include<cstring>
#define re register
using namespace std;
const int mod=1000000007,N=1e6+5;
int num[N],p[N];
char s[N];
inline void solve()
{
	scanf("%s",s+1);
	int len=(int)strlen(s+1),ans=1;
	num[1]=1;
	for(re int i=2,j=0,t=0; i<=len; ++i)
	{
		while(j&&s[i]!=s[j+1])
			j=p[j];
		if(s[i]==s[j+1])
			++j;
		num[i]=num[j]+1;
		p[i]=j;
		while(t&&s[i]!=s[t+1])
			t=p[t];
		if(s[i]==s[t+1])
			++t;
		while((t<<1)>i)
			t=p[t];
		ans=1ll*ans*(num[t]+1)%mod;
//		printf("%d %d %d\n",i,p[i],num[i]);
	}
	printf("%d\n",ans);
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
		solve();
}
