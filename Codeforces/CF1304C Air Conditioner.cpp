#include<cstdio>
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
const int N=105;
int t[N],n,m;
int l[N],r[N];
inline void work()
{
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
		read(t[i]),read(l[i]),read(r[i]);
	int left=max(l[1],m-t[1]),right=min(r[1],m+t[1]);
	if(left>right)
	{
		printf("NO\n");
		return;
	}
	for(re int i=2; i<=n; ++i)
	{
		left=max(left-(t[i]-t[i-1]),l[i]),right=min(right+(t[i]-t[i-1]),r[i]);
		if(left>right)
		{
			printf("NO\n");
			return;
		}
	}
	printf("YES\n");
	return;
}
int main()
{
	int T;
	read(T);
	while(T--)
		work();
}
