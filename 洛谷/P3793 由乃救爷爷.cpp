#include <cstdio>
#include <algorithm>
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
namespace GenHelper
{
	unsigned z1,z2,z3,z4,b;
	unsigned rand_()
	{
		b=((z1<<6)^z1)>>13;
		z1=((z1&4294967294U)<<18)^b;
		b=((z2<<2)^z2)>>27;
		z2=((z2&4294967288U)<<2)^b;
		b=((z3<<13)^z3)>>21;
		z3=((z3&4294967280U)<<7)^b;
		b=((z4<<3)^z4)>>12;
		z4=((z4&4294967168U)<<13)^b;
		return (z1^z2^z3^z4);
	}
}
void srand(unsigned x)
{
	using namespace GenHelper;
	z1=x;
	z2=(~x)^0x233333333U;
	z3=x^0x1234598766U;
	z4=(~x)+51;
}
int read()
{
	using namespace GenHelper;
	int a=rand_()&32767;
	int b=rand_()&32767;
	return a*32768+b;
}
const int N=2e7+5;
int n,m,s;
struct Tree
{
	int val;
	int ch[2];
} tree[N];
int st[N],top;
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define val(x) tree[x].val
int root;
inline void build()
{
	for(re int i=1; i<=n; ++i)
	{
		val(i)=read();
		while(top&&val(st[top])<val(i))
			lc(i)=st[top--];
		if(top)
			rc(st[top])=i;
		st[++top]=i;
	}
	root=st[1];
}
inline int query(int l,int r)
{
	int now=root;
	while(now<l||now>r)
		now=tree[now].ch[now<l];
	return val(now);
}
ull ans;
signed main()
{
	read(n,m,s);
	srand(s);
	build();
	while(m--)
	{
		int l=read()%n+1,r=read()%n+1;
		if(l>r)
			swap(l,r);
		ans+=query(l,r);
	}
	printf("%llu\n",ans);
	return 0;
}


