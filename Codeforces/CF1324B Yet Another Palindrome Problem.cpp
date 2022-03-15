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
const int N=5005;
int a[N],n;
inline void work()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=3; i<=n; ++i)
	{
		for(re int j=i-2; j>=1; --j)
			if(a[i]==a[j])
			{
				printf("YES\n");
				return;
			}
	}
	printf("NO\n");
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}

