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
const int N=5e6+5;
inline int calc(char s)
{
	if(s=='A')
		return 1;
	if(s=='T')
		return 2;
	if(s=='C')
		return 3;
	if(s=='G')
		return 4;
	return 5;
}
struct PAM
{
	int fa,len,half,ch[6];
} point[N];
int las=1,cnt=1;
int n;
char str[N];
inline int gethalf(int x,int l)
{
	while(point[x].len+2>l||str[n]!=str[n-point[x].len-1])
		x=point[x].fa;
	return x;
}
inline int getfa(int x)
{
	while(str[n]!=str[n-point[x].len-1])
		x=point[x].fa;
	return x;
}
int dp[N];
inline void insert(int c)
{
	int cur=getfa(las);
	int now=point[cur].ch[c];
	if(!now)
	{
		now=++cnt;
		point[now].len=point[cur].len+2;
		point[now].fa=point[getfa(point[cur].fa)].ch[c];
		if(point[now].len<2)
			point[now].half=0;
		else
			point[now].half=point[gethalf(point[cur].half,point[now].len>>1)].ch[c];
		point[cur].ch[c]=now;
	}
	las=now;
}
inline void work()
{
	point[0].fa=1,point[0].len=0;
	point[1].fa=0,point[1].len=-1;
	scanf("%s",str+1);
	for(n=1; str[n]; ++n)
		insert(calc(str[n]));
	--n;
	clear(dp,1,cnt,0x3f);
	queue<int>q;
	q.push(0);
	dp[0]=0;
	int ans=0x3f3f3f3f;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		ans=min(ans,n-point[u].len+dp[u]);
//		printf("%d %d %d\n",u,point[u].len,dp[u]);
		for(int i=1; i<=4; ++i)
		{
			int &v=point[u].ch[i];
			if(v)
			{
				if(u)
					dp[v]=min(dp[v],dp[u]+1);
				else
					dp[v]=2;
				if(point[point[v].half].len%2==0)
					dp[v]=min(dp[v],dp[point[v].half]+(point[v].len>>1)-point[point[v].half].len+1);
				q.push(v);
			}
		}
	}
//	putchar('\n');
	printf("%d\n",ans);
	clear(point,0,cnt,0);
	las=cnt=1;
}
signed main()
{
	freopen("virus.in","r",stdin);
	freopen("virus.out","w",stdout);
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}

