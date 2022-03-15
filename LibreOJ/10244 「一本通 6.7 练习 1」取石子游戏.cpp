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
int n,m,a[N],b[N];
int sg[N];
bitset<N>exist;
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	read(m);
	for(int i=1; i<=m; ++i)
		read(b[i]);
	sg[0]=0;

	for(int i=1; i<=1000; ++i)
	{
		for(int j=1; j<=m; ++j)
			if(b[j]<=i)
				exist[sg[i-b[j]]]=true;
		for(int j=0; j<=1001; ++j)
			if(!exist[j])
			{
				sg[i]=j;
				break;
			}
		exist.reset();
	}
	int ans=0;
	for(int i=1; i<=n; ++i)
		ans^=sg[a[i]];
//	printf(" %d\n",ans);
//	for(int i=0; i<=1000; ++i)
//		printf("%d ",sg[i]);
//	putchar('\n');
	if(ans)
	{
		printf("YES\n");
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j)
				if(a[i]>=b[j])
				{
					if(sg[a[i]-b[j]]==(ans^sg[a[i]]))
					{
						printf("%d %d\n",i,b[j]);
						return 0;
					}
				}
	}
	else
		printf("NO\n");
	return 0;
}


