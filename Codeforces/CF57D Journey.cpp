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
inline ll calc(int n,int m,int *a)
{
	ll ans=0;
	for(int i=1; i<=n; ++i)
	{
		ll sum=0;
		for(int j=1; j<=n; ++j)
			sum+=abs(i-j)*(m-(bool)a[j]);
		ans+=sum*(m-(bool)a[i]);
		if(a[i])
		{
			sum=m-a[i];
			int up=i-1,down=i+1;
			while(up>=1&&a[up]>a[up+1])
				sum+=m-a[up--];
			while(down<=n&&a[down]>a[down-1])
				sum+=m-a[down++];
			ans+=4*sum*(a[i]-1);
		}
	}
	return ans;
}
int n,m,hang[N],lie[N];
char str[N];
signed main()
{
	read(n,m);
	int tot=n*m;
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",str+1);
		for(int j=1; j<=m; ++j)
			if(str[j]=='X')
			{
				hang[i]=j;
				lie[j]=i;
				--tot;
			}
	}
	printf("%lf\n",(double)(calc(n,m,hang)+calc(m,n,lie))/tot/tot);
	return 0;
}


