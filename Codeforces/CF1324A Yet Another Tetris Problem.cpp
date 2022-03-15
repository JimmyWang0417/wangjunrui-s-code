#include<cstdio>
#define re register
#define ll long long
#define int ll
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
	return;
}
const int N=105;
int a[N],n;
inline void work()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=2; i<=n; ++i)
		if(a[i]%2!=a[i-1]%2)
		{
			printf("NO\n");
			return;
		}
	printf("YES\n");
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}
