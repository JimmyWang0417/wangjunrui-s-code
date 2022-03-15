#include <cstdio>
#define re register
#define ll long long
using namespace std;
template <typename T>
inline void read(T&x)
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
}
const int N=30;
ll c[N][N],d[N],ans[N];
inline void init()
{
	d[1]=0,d[2]=1;
	for(re int i=3; i<=25; ++i)
		d[i]=(i-1)*(d[i-1]+d[i-2]);
	for(re int i=0; i<=25; ++i)
	{
		for(re int j=c[i][0]=1; j<=i; ++j)
			c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
//	for(re int i=0; i<=13; ++i)
//	{
//		for(re int j=0; j<=i; ++j)
//			printf(" c(%d)(%d)=%d",i,j,c[i][j]);
//		putchar('\n');
//	}

}
inline void solve(int now)
{
	ans[now]=1;
	for(re int i=1; i<=(now/2); ++i)
		ans[now]+=d[i]*c[now][i];
}
int main()
{
	init();
	for(re int i=1; i<=25; ++i)
		solve(i);
//	for(re int i=1; i<=25; ++i)
//		printf("%lld ",ans[i]);
	int n;
	while(read(n),n)
		printf("%lld\n",ans[n]);
	return 0;
}
