#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define eps 1e-4
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
const int N=1505;
int n,m;
char T[N],S[N];
int size[N];
double sum[N];
int ch[N][10],nxt[N],tot;
inline void insert(char *s,double val)
{
	int u=0;
	for(int i=1; s[i]; ++i)
	{
		int c=s[i]-'0';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	++size[u];
	sum[u]+=val;
}
inline void init()
{
	queue<int>q;
	for(int i=0; i<10; ++i)
		if(ch[0][i])
			q.push(ch[0][i]);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		sum[u]+=sum[nxt[u]];
		size[u]+=size[nxt[u]];
		for(int i=0; i<10; ++i)
			if(ch[u][i])
			{
				nxt[ch[u][i]]=ch[nxt[u]][i];
				q.push(ch[u][i]);
			}
			else
				ch[u][i]=ch[nxt[u]][i];
	}
}
double val[N];
double dp[N][N];
int pre[N][N],g[N][N];
inline bool check(double mid)
{
	for(int i=1; i<=tot; ++i)
		val[i]=sum[i]-mid*size[i];
	memset(dp,-127/3,sizeof(dp));
//	cout<<dp[0][0]<<endl;
	dp[0][0]=0;
	for(int i=0; i<n; ++i)
		for(int j=0; j<=tot; ++j)
			if(dp[i][j]>-1e99)
				for(int k=0; k<10; ++k)
					if(T[i+1]==k+'0'||T[i+1]=='.')
					{
						int c=ch[j][k];
						if(dp[i+1][c]<dp[i][j]+val[c])
							dp[i+1][c]=dp[i][j]+val[c];
					}
//	for(int i=0; i<=n; ++i)
//	{
//		for(int j=0; j<=tot; ++j)
//			printf("%.2lf ",dp[i][j]);
//		putchar('\n');
//	}
	for(int i=0; i<=tot; ++i)
		if(dp[n][i]>0)
			return true;
	return false;
}
inline void print(int pos,int u)
{
	if(pos==0)
		return;
	print(pos-1,pre[pos][u]);
	printf("%d",g[pos][u]);
}
inline void solve(double mid)
{
	for(int i=1; i<=tot; ++i)
		val[i]=sum[i]-mid*size[i];
	memset(dp,-127/3,sizeof(dp));
//	cout<<dp[0][0]<<endl;
	dp[0][0]=0;
	for(int i=0; i<n; ++i)
		for(int j=0; j<=tot; ++j)
			if(dp[i][j]>-1e99)
				for(int k=0; k<10; ++k)
					if(T[i+1]==k+'0'||T[i+1]=='.')
					{
						int c=ch[j][k];
						if(dp[i+1][c]<dp[i][j]+val[c])
						{
							dp[i+1][c]=dp[i][j]+val[c];
							pre[i+1][c]=j;
							g[i+1][c]=k;
						}
					}
//	for(int i=0; i<=n; ++i)
//	{
//		for(int j=0; j<=tot; ++j)
//			printf("%.2lf ",dp[i][j]);
//		putchar('\n');
//	}
	int pos=0;
	for(int i=1; i<=tot; ++i)
		if(dp[n][pos]<dp[n][i])
			pos=i;
	print(n,pos);
}
signed main()
{
	read(n,m);
	scanf("%s",T+1);
	for(int i=1; i<=m; ++i)
	{
		int x;
		scanf("%s%d",S+1,&x);
		insert(S,log(x));
	}
	init();
	double l=0,r=log(1e9),ans=0;
	while(abs(r-l)>eps)
	{
		double mid=(l+r)/2;
		if(check(mid))
		{
			ans=mid;
			l=mid;
		}
		else
			r=mid;
	}
//	printf("%d\n",check(log(1e9)));
//	printf("%lf\n",ans);
	solve(ans);
	return 0;
}


