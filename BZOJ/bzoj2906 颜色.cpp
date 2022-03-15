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
const int N=5e4+5,M=2e4+5;
unsigned int n,m,q,c[N];
unsigned int block,num,L[N],R[N],belong[N];
unsigned int cntblock[40][40][M];
unsigned int sum[40][40][M];
inline void init()
{
	block=(int)pow(n,2.0/3.0);
	num=(n-1)/block+1;
	for(unsigned int i=1; i<=num; ++i)
	{
		L[i]=R[i-1]+1;
		R[i]=R[i-1]+block;
		if(i==num)
			R[i]=n;
		for(unsigned int j=L[i]; j<=R[i]; ++j)
			belong[j]=i;
	}
	for(unsigned int i=1; i<=num; ++i)
		for(unsigned int j=i; j<=num; ++j)
		{
			memcpy(cntblock[i][j],cntblock[i][j-1],sizeof(cntblock[i][j]));
			memcpy(sum[i][j],sum[i][j-1],sizeof(sum[i][j]));
			for(unsigned int k=L[j]; k<=R[j]; ++k)
			{
				sum[i][j][c[k]]+=cntblock[i][j][c[k]]<<1|1;
				++cntblock[i][j][c[k]];
			}
		}
	for(unsigned int i=1; i<=num; ++i)
		for(unsigned int j=i; j<=num; ++j)
			for(unsigned int k=2; k<=m; ++k)
				sum[i][j][k]+=sum[i][j][k-1];
}
unsigned int cnt[M];
inline unsigned int query(unsigned int l,unsigned int r,unsigned int a,unsigned int b)
{
	if(belong[r]-belong[l]<=1)
	{
		unsigned int res=0;
		for(unsigned int i=l; i<=r; ++i)
		{
			if(a<=c[i]&&c[i]<=b)
			{
				res+=cnt[c[i]]<<1|1;
				++cnt[c[i]];
			}
		}
		for(unsigned int i=l; i<=r; ++i)
			if(a<=c[i]&&c[i]<=b)
				cnt[c[i]]=0;
		return res;
	}
	else
	{
		unsigned int res=sum[belong[l]+1][belong[r]-1][b]-sum[belong[l]+1][belong[r]-1][a-1];
		for(unsigned int i=l; i<=R[belong[l]]; ++i)
		{
			if(a<=c[i]&&c[i]<=b)
			{
				res+=(cnt[c[i]]+cntblock[belong[l]+1][belong[r]-1][c[i]])<<1|1;
				++cnt[c[i]];
			}
		}
		for(unsigned int i=L[belong[r]]; i<=r; ++i)
		{
			if(a<=c[i]&&c[i]<=b)
			{
				res+=(cnt[c[i]]+cntblock[belong[l]+1][belong[r]-1][c[i]])<<1|1;
				++cnt[c[i]];
			}
		}
		for(unsigned int i=L[belong[r]]; i<=r; ++i)
			if(a<=c[i]&&c[i]<=b)
				cnt[c[i]]=0;
		for(unsigned int i=l; i<=R[belong[l]]; ++i)
			if(a<=c[i]&&c[i]<=b)
				cnt[c[i]]=0;
		return res;
	}
}
signed main()
{
	read(n,m,q);
	for(unsigned int i=1; i<=n; ++i)
		read(c[i]);
	init();
	// for(int i=1; i<=num; ++i)
		// printf("%u %u\n",L[i],R[i]);
	// for(int i=1; i<=n; ++i)
		// printf("%u ",belong[i]);
	// putchar('\n');
	unsigned int lastans=0;
	for(unsigned int i=1; i<=q; ++i)
	{
		unsigned int l,r,a,b;
		read(l,r,a,b);
		l^=lastans,r^=lastans,a^=lastans,b^=lastans;
//		printf("%u %u %u %u\n",l,r,a,b);
		printf("%u\n",lastans=query(l,r,a,b));
	}
	return 0;
}


