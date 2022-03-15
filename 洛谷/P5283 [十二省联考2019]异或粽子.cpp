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
const int N=5e5+5;
struct Tree
{
	int size,ch[2];
} tree[N*60];
int tot=1;
inline void insert(unsigned val)
{
	int u=1;
	for(int i=31; i>=0; --i)
	{
		unsigned c=(val>>i)&1;
		++tree[u].size;
		if(!tree[u].ch[c])
			tree[u].ch[c]=++tot;
		u=tree[u].ch[c];
	}
	++tree[u].size;
}
inline unsigned query(int rk,unsigned val)
{
	unsigned ans=0;
	int u=1;
	for(int i=31; i>=0; --i)
	{
		unsigned c=(val>>i)&1;
		if(rk<=tree[tree[u].ch[!c]].size)
		{
			u=tree[u].ch[!c];
			ans|=1ll<<i;
		}
		else
		{
			rk-=tree[tree[u].ch[!c]].size;
			u=tree[u].ch[c];
		}
	}
//	putchar('\n');
	return ans;
}
int n,k;
unsigned a[N];
struct node
{
	int id,rk;
	unsigned val;
	node(int _id=0,int _rk=0,unsigned _val=0):id(_id),rk(_rk),val(_val) {}
	inline bool operator <(const node &rhs)const
	{
		return val<rhs.val;
	}
};
signed main()
{
	read(n,k);
	k<<=1;
	insert(0);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		a[i]^=a[i-1];
		insert(a[i]);
	}
//	for(int i=1; i<=n; ++i)
//		printf("%u ",a[i]);
//	putchar('\n');
	priority_queue<node>q;
	for(int i=0; i<=n; ++i)
	{
		q.push(node(i,1,query(1,a[i])));
//		printf("%u ",query(1,a[i]));
	}
//	putchar('\n');
	ll sum=0;
	for(int i=1; i<=k; ++i)
	{
		node u=q.top();
		q.pop();
		sum+=u.val;
		if(u.rk<n)
			q.push(node(u.id,u.rk+1,query(u.rk+1,a[u.id])));
	}
	printf("%lld\n",sum>>1);
	return 0;
}

