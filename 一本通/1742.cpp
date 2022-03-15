#include<cstdio>
#include<algorithm>
#define re register
#define lowbit(x) (x&(-x))
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=1e5+5,mod=123456789;
struct node
{
	int v,sum;
	inline void init()
	{
		v=0;
		sum=1;
		return;
	}
} tree[N],x,ans,res;
inline void update(int x,const node &y)
{
	while(x<=N)
	{
		if(y.v>tree[x].v)
			tree[x]=y;
		else if(y.v==tree[x].v)
			tree[x].sum=(tree[x].sum+y.sum)%mod;
		x+=lowbit(x);
	}
	return;
}
inline node query(int x)
{
	res.init();
	while(x)
	{
		if(tree[x].v>res.v)
			res=tree[x];
		else if(tree[x].v==res.v)
			res.sum=(res.sum+tree[x].sum)%mod;
		x-=lowbit(x);
	}
	return res;
}
int n,type;
int main()
{
	read(n);
	read(type);
	for(re int i=1,a; i<=n; i++)
	{
		read(a);
		x=query(a-1);
		x.v++;
		if(ans.v<x.v)
			ans=x;
		else if(ans.v==x.v)
			ans.sum=(ans.sum+x.sum)%mod;
		update(a,x);
	}
	printf("%d\n",ans.v);
	if(type==1)
		printf("%d\n",ans.sum);
	return 0;
}

