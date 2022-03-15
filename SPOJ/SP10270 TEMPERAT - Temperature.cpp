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
const int N=1e6+5;
int n;
struct node
{
	int x,y;
} a[N];
int q[N];
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i].x,a[i].y);
	int ans=0,las=1;
	int head=1,tail=0;
	for(int i=1; i<=n; ++i)
	{
		while(head<=tail&&a[q[tail]].x<=a[i].x)
			--tail;
		q[++tail]=i;
		while(las<=i&&a[q[head]].x>a[i].y)
		{
			while(head<=tail&&q[head]<=las)
				++head;
			++las;
		}
		ans=max(ans,i-las+1);
	}
	printf("%d\n",ans);
	return 0;
}


