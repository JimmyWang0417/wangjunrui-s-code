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
char str[N];
int sa[N];
signed main()
{
	scanf("%d%s",&n,str+1);
	int l=1,r=n;
	for(int i=2,las=1; i<=n+1; ++i)
	{
		if(str[i]==str[las])
			continue;
		if(str[i-1]<str[i])
		{
			for(int j=i-1; j>=las; --j)
				sa[r--]=j;
		}
		else
			for(int j=las; j<i; ++j)
				sa[l++]=j;
		las=i;
	}
	for(int i=1; i<=n; ++i)
		printf("%d ",sa[i]);
	putchar('\n');
	return 0;
}


