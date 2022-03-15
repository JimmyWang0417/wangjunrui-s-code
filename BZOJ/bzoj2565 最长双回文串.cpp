#include<cstdio>
#include<algorithm>
#include<cstring>
#define re register
#define ll long long
#define length (n<<1|1)
using namespace std;
const int N=2e6+10;
char str[N],s[N];
int p[N],ans;
int suf[N],pre[N];
int l[N],r[N];
int n;
inline void manacher()
{
	for(re int i=1,mid=0,maxx=0; i<=length; ++i)
	{
		p[i]=maxx>i?min(maxx-i,p[(mid<<1)-i]):1;
		while(str[i-p[i]]==str[i+p[i]])
			++p[i];
		if(i+p[i]>maxx)
		{
			maxx=i+p[i];
			mid=i;
		}
		pre[i-p[i]+1]=max(p[i]-1,pre[i-p[i]+1]);
		suf[i+p[i]-1]=max(p[i]-1,suf[i+p[i]-1]);
	}
}
inline void solve()
{
//	for(int i=1; i<=length; ++i)
//		printf("%d %d\n",l[i],r[i]);
	for(re int i=1; i<=length; i+=2)
		pre[i]=max(pre[i],pre[i-2]-2);
	for(re int i=length; i>=1; i-=2)
		suf[i]=max(suf[i],suf[i+2]-2);
	for(re int i=1; i<=length; i+=2)
		if(suf[i]&&pre[i])
			ans=max(ans,suf[i]+pre[i]);
	printf("%d\n",ans);
}
int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=n; i>=1; i--)
	{
		str[i<<1]=s[i];
		str[i<<1|1]='|';
	}
//	printf("%d %s\n",length,str);
	str[0]='$';
	str[1]='|';
	str[length+1]='#';
	manacher();
	solve();
	return 0;
}
