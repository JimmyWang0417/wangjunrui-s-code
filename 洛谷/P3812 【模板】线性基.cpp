#include <cstdio>
#define re register
#define ll long long
using namespace std;
template <typename T>
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
const int N=55;
int n;
class Linear_basis
{
	private:
		ll d[N];
	public:
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
		inline ll getmax()
		{
			ll ans=0;
			for(re int i=50; i>=0; --i)
				if((ans^d[i])>ans)
					ans^=d[i];
			return ans;
		}
} L;
int main()
{
	read(n);
	ll val;
	while(n--)
	{
		read(val);
		L.add(val);
	}
	printf("%lld\n",L.getmax());
	return 0;
}
