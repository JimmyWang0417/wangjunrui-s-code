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
const int N=2200005;
struct SAM
{
	int fa,ch[2];
	int len;
} point[N];
int tot=1,las=1;
inline void insert(int c)
{
	int p=las,np=las=++tot;
	point[np].len=point[p].len+1;
	for(; p&&!point[p].ch[c]; p=point[p].fa)
		point[p].ch[c]=np;
	if(!p)
		point[np].fa=1;
	else
	{
		int q=point[p].ch[c];
		if(point[p].len+1==point[q].len)
			point[np].fa=q;
		else
		{
			int nq=++tot;
			point[nq]=point[q];
			point[nq].len=point[p].len+1;
			point[np].fa=point[q].fa=nq;
			for(; p&&point[p].ch[c]==q; p=point[p].fa)
				point[p].ch[c]=nq;
		}
	}
}
int n,m;
char str[N];
inline void init()
{
	las=1;
	scanf("%s",str+1);
	for(int i=1; str[i]; ++i)
		insert(str[i]-'0');
}
#define g(x) (dp[x]-(x))
int q[N];
int maxlen[N];
int dp[N];
int len;
inline bool check(int mid)
{
	int head=1,tail=0;
	for(int i=1; i<=len; ++i)
	{
		if(i>=mid)
			while(head<=tail&&g(q[tail])<g(i-mid))
				--tail;
		q[++tail]=i-mid;
		while(head<=tail&&q[head]<i-maxlen[i])
			++head;
		if(head<=tail)
			dp[i]=max(dp[i-1],i+g(q[head]));
		else
			dp[i]=dp[i-1];
	}
	return dp[len]>=0.9*len;
}
inline void work()
{
	scanf("%s",str+1);
	len=(int)strlen(str+1);
	int u=1,now=0;
	for(int i=1; i<=len; ++i)
	{
		int c=str[i]-'0';
		if(point[u].ch[c])
		{
			++now;
			u=point[u].ch[c];
		}
		else
		{
			while(u!=1&&!point[u].ch[c])
				u=point[u].fa;
			if(point[u].ch[c])
			{
				now=point[u].len+1;
				u=point[u].ch[c];
			}
			else
				now=0;
		}
		maxlen[i]=now;
	}
//	for(int i=1; str[i]; ++i)
//		printf("%d ",maxlen[i]);
//	putchar('\n');
	int l=1,r=len,ans=1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
		{
			ans=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
	printf("%d\n",ans);
}
signed main()
{
	read(n,m);
	for(int i=1; i<=m; ++i)
		init();
	for(int i=1; i<=n; ++i)
		work();
	return 0;
}


