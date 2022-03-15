#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
template <typename T>
inline void read(T&x)
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
}
const int N=1000+5,SIZE=60+6;
ll d[SIZE];
int ans,n;
inline bool add(ll x)
{
	for(re int i=60; i>=0; --i)
		if((x>>i)&1)
		{
			if(!d[i])
			{
				d[i]=x;
				return true;
			}
			else
				x=x^d[i];
		}
	return false;
}
struct node
{
	ll number;
	int magic;
	inline bool operator < (const node &rhs)const
	{
		return magic>rhs.magic;
	}
} a[N];
int main()
{
	read(n);
	for(re int i=0; i<n; ++i)
	{
		read(a[i].number);
		read(a[i].magic);
	}
	sort(a,a+n);
	for(re int i=0; i<n; ++i)
		if(add(a[i].number))
			ans+=a[i].magic;
	printf("%d\n",ans);
	return 0;
}
