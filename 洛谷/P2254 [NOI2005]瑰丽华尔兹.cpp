#include <cstdio>
#include <cstring>
#define max(x,y) ((x)>(y)?(x):(y))
#define re register
#define calc(x) (q[x].ans-q[x].id)
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}

int ans=-1;
const int N=205;
int dx[5]= {0,-1,1,0,0},dy[5]= {0,0,0,-1,1};
int dp[N][N],n,m;
struct node
{
	int ans,id;
	node() {}
	node(int a,int i):ans(a),id(i) {}
} q[N];
char str[N][N];
inline void solve(int x,int y,int len,int d)
{
	int head=1,tail=0;
	for(re int i=1; 1<=x&&x<=n&&1<=y&&y<=m; ++i,x+=dx[d],y+=dy[d])
		if(str[x][y]=='x')
		{
			head=1;
			tail=0;
		}
		else
		{
			while(head<=tail&&calc(tail)<dp[x][y]-i)
				--tail;
			q[++tail]=node(dp[x][y],i);
			while(head<=tail&&q[head].id<i-len)
				++head;
			dp[x][y]=calc(head)+i;
			ans=max(ans,dp[x][y]);
		}
}
int main()
{
	int sx,sy,qq;
	memset(dp,~0x3f3f3f3f,sizeof(dp));
//	printf("%d\n",dp[1][1]);
	read(n),read(m),read(sx),read(sy),read(qq);
	for(re int i=1; i<=n; ++i)
		scanf("%s",str[i]+1);
	dp[sx][sy]=0;
//	for(re int i=1; i<=n; ++i)
//	{
//		for(re int j=1; j<=m; ++j)
//			printf("\t%d",dp[i][j]);
//		putchar('\n');
//	}
	while(qq--)
	{
		int s,t,d;
		read(s),read(t),read(d);
		int len=t-s+1;
//		putchar('\n');
		if(d==1)
			for(re int i=1; i<=m; ++i)
				solve(n,i,len,d);
		else if(d==2)
			for(re int i=1; i<=m; ++i)
				solve(1,i,len,d);
		else if(d==3)
			for(re int i=1; i<=n; ++i)
				solve(i,m,len,d);
		else if(d==4)
			for(re int i=1; i<=n; ++i)
				solve(i,1,len,d);
//		for(re int i=1; i<=n; ++i)
//		{
//			for(re int j=1; j<=m; ++j)
//				printf("\t%d",dp[i][j]);
//			putchar('\n');
//		}
	}
	printf("%d\n",ans);
	return 0;
}
