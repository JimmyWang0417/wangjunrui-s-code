#include<cstdio>
#include<vector>
#include<iostream>
#include<algorithm>
#define re register
#define int long long
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
const int N=105;
int a[N];
inline void work()
{
	int n;
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	sort(a+1,a+1+n);
	for(re int i=n; i>=1; --i)
		printf("%lld ",a[i]);
	putchar('\n');
	return;
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}
