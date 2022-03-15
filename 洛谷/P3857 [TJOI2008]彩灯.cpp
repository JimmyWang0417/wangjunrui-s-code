#include <cstdio>
#define re register
#define ll long long
using namespace std;
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}
const int N=50+5;
int n,m;
ll d[N];
inline void add(ll x)
{
	for(re int i=50; i>=0; --i)
		if((x>>i)&1)
		{
			if(!d[i])
			{
				d[i]=x;
				break;
			}
			else
				x=x^d[i];
		}
}
char str[N];
int main()
{
	read(n),read(m);
	while(m--)
	{
		scanf("%s",str+1);
		ll val=0ll;
		for(re int i=0; i<n; ++i)
			if(str[n-i]=='O')
				val|=1ll<<i;
		add(val);
	}
	int cnt=0;
	for(re int i=0; i<=50; ++i)
		if(d[i])
			++cnt;
	printf("%d\n",(1ll<<cnt)%2008);
	return 0;
}
