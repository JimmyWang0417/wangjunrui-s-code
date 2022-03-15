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
const int N=1e5+5,BLOCK=650;
int n,m,a[N];
int cnt1[BLOCK][N],cnt2[BLOCK][N],tcnt[N];
int block,num,belong[N],L[N],R[N];
signed main()
{
	freopen("password.in","r",stdin);
	freopen("password.out","w",stdout);
	read(n);
	int maxv=0;
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		maxv=max(maxv,a[i]);
	}

	block=min((int)(sqrt(n)*2.25),n);
	num=n/block+(n%block!=0);
	for(int i=1; i<=num; ++i)
	{
		L[i]=R[i-1]+1;
		R[i]=min(R[i-1]+block,n);
		for(int j=L[i]; j<=R[i]; ++j)
			belong[j]=i;
		memcpy(cnt1[i]+1,cnt1[i-1]+1,sizeof(int)*maxv);
		memcpy(cnt2[i]+1,cnt2[i-1]+1,sizeof(int)*n);
		for(int j=L[i]; j<=R[i]; ++j)
			++cnt2[i][++cnt1[i][a[j]]];
	}
	read(m);
	for(int kase=1; kase<=m; ++kase)
	{
		int opt,x,y;
		read(opt,x,y);
		if(opt==1)
		{
			swap(x,y);
			if(y==a[x])
				continue;
			for(int i=belong[x]; i<=num; ++i)
			{
				--cnt2[i][cnt1[i][a[x]]--];
				++cnt2[i][++cnt1[i][y]];
			}
			a[x]=y;
		}
		else
		{
			if(x==1)
				printf("%d\n",a[y]);
			else if(x&1)
			{
				int cn=cnt1[belong[y]-1][a[y]];
				for(int i=L[belong[y]]; i<=y; ++i)
					if(a[i]==a[y])
						++cn;
				int res=cnt2[belong[y]-1][cn];
				for(int i=L[belong[y]]; i<=y; ++i)
				{
					if(++tcnt[a[i]]+cnt1[belong[y]-1][a[i]]==cn)
						++res;
				}
				for(int i=L[belong[y]]; i<=y; ++i)
					tcnt[a[i]]=0;
				printf("%d\n",res);
			}
			else
			{
				int res=cnt1[belong[y]-1][a[y]];
				for(int i=L[belong[y]]; i<=y; ++i)
					if(a[i]==a[y])
						++res;
				printf("%d\n",res);
			}
		}
	}
	return 0;
}


