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
const int mod= 998244353;
const int R[16] = {0, 4, 8, -1, 16, -10, 4, -12, -48, 26, -44, 15, -16, -4, -4, -1};
int a[16] = {0, 0, 0, 24, 4, 240, 204, 1316, 2988, 6720, 26200, 50248, 174280, 436904, 1140888, 3436404};
signed main()
{
	freopen("a.in","r",stdin),freopen("a.out","w",stdout);
	int n;
	read(n);
	for(int i=16; i<=n; ++i)
	{
		int x=0;
		for(int j=0; j<16; ++j)
			x=(x+(ll)R[(i-j-1)&15]*a[j]%mod)%mod;
		a[i&15]=x;
//		printf("%d\n",x);
	}
	printf("%d\n",(a[n&15]%mod+mod)%mod);
	return 0;
}


