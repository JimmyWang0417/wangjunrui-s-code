#include<cstdio>
#include<algorithm>
#define int ll
using namespace std;
#define re register
#define ll long long
template<typename T>
inline void read(T&x)
{
	x=0;
	char wjr=(char)getchar();
	bool flag=false;
	while(!(wjr>='0'&&wjr<='9'))
	{
		if(wjr=='-')
			flag=true;
		wjr=(char)getchar();
	}
	while(wjr>='0'&&wjr<='9')
	{
		x=(x<<1)+(x<<3)+wjr-'0';
		wjr=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
}
int n,m;
const int N=2e5+5;
int p[N],val[N];
ll sum[N];
#define lowbit(x) (x&(-x))
inline void add(int x,int val)
{
	for(; x<=n; x+=lowbit(x))
		sum[x]+=val;
	return;
}
inline long long query(int x)
{
	long long res=0;
	for(; x; x-=lowbit(x))
		res+=sum[x];
	return res;
}
struct Tree
{
	ll sum,num;
	Tree(int n=0,int s=0):num(n),sum(s) {}
	inline Tree operator +(const Tree&rhs)const
	{
		return Tree(num+rhs.num,sum+rhs.sum);
	}
} tree[N<<2];
#define lson (k<<1)
#define rson (k<<1|1)
inline Tree query(int l,int r,int k,int x,int y)
{
	Tree w=Tree();
	if(l>y||r<x)return w;
	if(l>=x&&r<=y)return tree[k];
	int mid=l+r>>1;
	return query(l,mid,lson,x,y)+query(mid+1,r,rson,x,y);
}
inline void change(int l,int r,int k,int x,int val)
{
	if(l>x||r<x)return;
	if(l==r&&l==x)
	{
		tree[k].num+=val;
		tree[k].sum+=l*val;
		return;
	}
	int mid=l+r>>1;
	change(l,mid,lson,x,val);
	change(mid+1,r,rson,x,val);
	tree[k].num=tree[lson].num+tree[rson].num;
	tree[k].sum=tree[lson].sum+tree[rson].sum;
	return;
}
signed main()
{
	read(n),read(m);
	for(re int i=1; i<=n; i++)
	{
		read(p[i]);
		val[i]=query(n)-query(p[i]);
		change(1,n,1,val[i],1);
		add(p[i],1);
	}
	while(m--)
	{
		int opt,x;
		read(opt),read(x);
		if(opt==1)
		{
			int x1=val[x],x2=val[x+1];
			swap(p[x],p[x+1]);
			swap(val[x],val[x+1]);
			if(p[x+1]>p[x])
			{
				val[x]--;
				change(1,n,1,val[x],1);
				change(1,n,1,x2,-1);
			}
			else
			{
				val[x+1]++;
				change(1,n,1,val[x+1],1);
				change(1,n,1,x1,-1);
			}
		}
		if(opt==2)
		{
			if(x>=n)printf("0\n");
			else
			{
				Tree p=query(1,n,1,x+1,n);
				printf("%lld\n",p.sum-p.num*(ll)x);
			}
		}
	}
	return 0;
}
