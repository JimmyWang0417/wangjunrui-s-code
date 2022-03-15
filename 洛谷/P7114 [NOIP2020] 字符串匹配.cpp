#include <bits/stdc++.h>
#define hash nmsl
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
const int N=(1<<20)+5,base=29;
char str[N];
int n;
int nowans;
bool nowch[26];
int suf[N];
int pre[27];
ull power[N],hash[N];
inline ull calc(int l,int r)
{
	return hash[r]-hash[l-1]*power[r-l+1];
}
inline void work()
{
	scanf("%s",str+1);
	n=(int)strlen(str+1);
	power[0]=1;
	for(int i=1; i<=n; ++i)
		power[i]=power[i-1]*base;
	for(int i=1; i<=n; ++i)
		hash[i]=hash[i-1]*base+str[i]-'a';
	memset(nowch,nowans=0,sizeof(nowch));
	for(int i=n; i>=3; --i)
	{
		int c=str[i]-'a';
		nowch[c]^=1;
		if(nowch[c])
			++nowans;
		else
			--nowans;
		suf[i]=nowans;
	}
	memset(nowch,nowans=0,sizeof(nowch));
	memset(pre,0,sizeof(pre));
	ll ans=0;
	for(int i=2; i<n; ++i)
	{
		int c=str[i-1]-'a';
		nowch[c]^=1;
		if(nowch[c])
			++nowans;
		else
			--nowans;
		for(int j=nowans; j<=26; ++j)
			++pre[j];
		for(int j=1; j+i-1<n&&calc(1,i)==calc(j,j+i-1); j+=i)
			ans+=pre[suf[j+i]];
	}
	printf("%lld\n",ans);
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}


