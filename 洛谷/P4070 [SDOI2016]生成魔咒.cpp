#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
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
template<typename T>
inline void clear(T*a,int l,int r,T val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=2e5+5;
ll ans;
class SAM
{
	private:
		struct Point
		{
			int len,fa;
			map<int,int>ch;
		} point[N];
		int las=1,tot=1;
	public:
		inline void insert(int c)
		{
			int p=las,np=las=++tot;
			point[np].len=point[p].len+1;
			for(; p&&!point[p].ch.count(c); p=point[p].fa)
				point[p].ch[c]=np;
			if(!p)
				point[np].fa=1;
			else
			{
				int q=point[p].ch[c];
				if(point[q].len==point[p].len+1)
					point[np].fa=q;
				else
				{
					int nq=++tot;
					point[nq]=point[q];
					point[nq].len=point[p].len+1;
					point[np].fa=point[q].fa=nq;
					for(; p&&point[p].ch[c]==q; p=point[p].fa)
						point[p].ch[c]=nq;
				}
			}
			ans+=point[np].len-point[point[np].fa].len;
		}
//		inline void print()
//		{
//			for(re int i=2; i<=tot; ++i)
//				printf(" %d %d\n",point[i].fa,point[i].len);
//		}
} tree;
signed main()
{
	int n;
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		tree.insert(val);
		printf("%lld\n",ans);
	}
//	tree.print();
	return 0;
}


