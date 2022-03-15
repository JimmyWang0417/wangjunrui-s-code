#include<cstdio>
#include<cstring>
//#include<iostream>
#define ull unsigned long long
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=70;
int zero[N],one[N],zeronum,onenum,d,n;
ull dp[N][N];
bool K[N];
inline bool can_zero(int i,int j)
{
	return i+1<=zeronum&&(onenum==j||one[j]+d>=zero[i]);
}
inline bool can_one(int i,int j)
{
	return j+1<=onenum&&(zeronum==i||zero[i]+d>=one[j]);
}
ull maxx,minn,k;
inline void get_max_and_min()
{
	maxx=minn=0;
	re int i=0,j=0;
	while(i<zeronum||j<onenum)
	{
		if(can_zero(i,j))
		{
			++i;
			minn<<=1;
		}
		else
		{
			++j;
			minn=minn<<1|1;
		}
	}
	i=j=0;
	while(i<zeronum||j<onenum)
	{
		if(can_one(i,j))
		{
			++j;
			maxx=maxx<<1|1;
		}
		else
		{
			++i;
			maxx=maxx<<1;
		}
	}
}
inline void DP()
{
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for(re int i=0; i<=zeronum; ++i)
		for(re int j=0; j<=onenum; ++j)
		{
			if(can_zero(i,j))
				dp[i+1][j]+=dp[i][j];
			if(can_one(i,j))
				dp[i][j+1]+=dp[i][j];
		}
}
int main()
{
	//ios::sync_with_stdio(false);
	int kase=0;
	while(read(n),n)
	{
		read(d);
		read(k);
		for(re int i=0; i<n; ++i)
		{
			K[n-i-1]=k&1;
			k>>=1;
		}
		onenum=zeronum=0;
		for(re int i=0; i<n; ++i)
			if(K[i])
				one[onenum++]=i;
			else
				zero[zeronum++]=i;
		DP();
		get_max_and_min();
		//cout<<"Case "<<++kase<<": "<<dp[zeronum][onenum]<<" "<<minn<<" "<<maxx<<"\n";
		printf("Case %d: %llu %llu %llu\n",++kase,dp[zeronum][onenum],minn,maxx);
	}
}
