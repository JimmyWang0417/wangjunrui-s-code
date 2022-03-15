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
const int N=1005;
const int mod=1e9+9;
int ch[N][4],tot,nxt[N];
int len[N];
inline int calc(char s)
{
	if(s=='A')
		return 0;
	else if(s=='T')
		return 1;
	else if(s=='C')
		return 2;
	else return 3;
}
inline void insert(char *s)
{
	int u=0,i;
	for(i=0; s[i]; ++i)
	{
		int c=calc(s[i]);
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	len[u]=i;
}
inline void build()
{
	queue<int>q;
	for(int i=0; i<4; ++i)
		if(ch[0][i])
			q.push(ch[0][i]);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		len[u]=max(len[u],len[nxt[u]]);
		for(int i=0; i<4; ++i)
			if(ch[u][i])
			{
				nxt[ch[u][i]]=ch[nxt[u]][i];
				q.push(ch[u][i]);
			}
			else
				ch[u][i]=ch[nxt[u]][i];
	}
}
int n,m;
int dp[N][15][105];
signed main()
{
	read(n,m);
	for(int i=1; i<=m; ++i)
	{
		static char opt[15];
		scanf("%s",opt);
		insert(opt);
	}
	build();
	dp[0][0][0]=1;
//	printf("%d\n",ch[1][0]);
	for(int i=0; i<n; ++i)
		for(int j=0; j<10; ++j)
			for(int u=0; u<=tot; ++u)
				if(dp[i][j][u])
				{
					for(int c=0; c<4; ++c)
						if(ch[u][c])
							(dp[i+1][len[ch[u][c]]>j?0:j+1][ch[u][c]]+=dp[i][j][u])%=mod;
				}
	int ans=0;
	for(int u=0; u<=tot; ++u)
		(ans+=dp[n][0][u])%=mod;
	printf("%d\n",ans);
	return 0;
}


