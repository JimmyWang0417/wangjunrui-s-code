#include <cmath>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>
#define lowbit(x) (x&(-x))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
signed main()
{
	int n;
	read(n);
	vector<int>v;
	for(re int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		v.insert(lower_bound(v.begin(),v.end(),val),val);
		if(i&1)
			printf("%d\n",v[i>>1]);
	}
	return 0;
	return 0;
}


