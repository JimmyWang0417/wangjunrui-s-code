#include <cstdio>
#include <algorithm>
#define re register
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
const int N=105,M=15,CNT=600+5;
int n,m,tot;
struct Status
{
	int status,val;
	Status() {}
	Status(int S)
	{
		this->status=S;
		this->val=0;
		for(re int i=0; i<m; ++i)
			if((S>>i)&1)
				++this->val;
	}
} status[CNT];
int a[N];
int dp[N][CNT][CNT];
char str[M];
int main()
{
	read(n),read(m);
	for(re int S=1; S<(1<<m); ++S)
		if((S&(S<<1))==0&&(S&(S<<2))==0)
			status[++tot]=Status(S);
//	for(re int i=0; i<=tot; ++i)
//		printf("%d %d\n",status[i].status,status[i].val);
	a[0]=(1<<m)-1;
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str);
		for(re int j=0; j<m; ++j)
			a[i]|=(str[m-j-1]=='H')<<j;
	}
//	for(re int i=1; i<=n; ++i)
//		printf("%d\n",a[i]);
	for(re int i=0; i<=tot; ++i)
		if((status[i].status&a[1])==0)
			dp[1][0][i]=status[i].val;
//	for(re int i=0; i<=tot; ++i)
//		printf("%d ",dp[1][0][i]);
	for(re int pos=2; pos<=n; ++pos)
		for(re int i=0; i<=tot; ++i)
			if((status[i].status&a[pos-2])==0)
				for(re int j=0; j<=tot; ++j)
					if((status[j].status&a[pos-1])==0&&(status[i].status&status[j].status)==0)
						for(re int k=0; k<=tot; ++k)
							if((status[k].status&a[pos])==0&&(status[i].status&status[k].status)==0&&(status[j].status&status[k].status)==0)
								dp[pos][j][k]=max(dp[pos][j][k],dp[pos-1][i][j]+status[k].val);
	int ans=-1;
	for(re int i=0; i<=tot; ++i)
		if((status[i].status&a[n-1])==0)
			for(re int j=0; j<=tot; ++j)
				if((status[j].status&a[n])==0&&(status[i].status&status[j].status)==0)
					ans=max(ans,dp[n][i][j]);
	printf("%d\n",ans);
	return 0;
}
