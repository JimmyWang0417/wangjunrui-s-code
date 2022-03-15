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
const int N=2e5+5;
struct node
{
	int a,b,id;
	inline bool operator <(const node &rhs)const
	{
		return a>rhs.a;
	}
} a[N];
int n;
signed main()
{
	int T;
	read(T);
	while(T--)
	{

		read(n);
		for(int i=1; i<=n*2-1; ++i)
		{
			read(a[i].a,a[i].b);
			a[i].id=i;
		}
		sort(a+1,a+2*n);
		ll sum1=0,sum2=0;
		for(int i=1; i<=n*2-1; i+=2)
			sum1+=a[i].b;
		for(int i=2; i<=n*2-1; i+=2)
			sum2+=a[i].b;
		printf("YES\n");
		if(sum1<=sum2)
		{
			printf("%d",a[1].id);
			for(int i=2; i<=n*2-1; i+=2)
				printf(" %d",a[i].id);
		}
		else
		{
			for(int i=1; i<=n*2-1; i+=2)
				printf("%d ",a[i].id);
		}
		putchar('\n');
	}
	return 0;
}


