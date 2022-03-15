#include<cstdio>
using namespace std;
inline int read()//¿ì¶Á
{
	int x=0b0;
	char s=getchar();
	bool f=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')f=1;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return f==1?-x:x;
}
const int N=1e6+5;
#define ull long long
int n,m,a[N],add[N*4];
ull sum[(N)*4];
void build(int k,int l,int r)
{
	if(l==r)
	{
		sum[k]=a[l];
		return;
	}
	int mid=l+r>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	sum[k]=sum[k<<1]+sum[k<<1|1];
}
inline void Add(int k,int l,int r,int v)
{
	add[k]+=v;
	sum[k]+=(ull)v*(r-l+1);
}
inline void pushdown(int k,int l,int r,int mid)
{
	if(add[k]==0)return;
	Add(k<<1,l,mid,add[k]);
	Add(k<<1|1,mid+1,r,add[k]);
	add[k]=0;
}
inline ull query(int k,int l,int r,int x,int y)
{
	if(l>=x&&r<=y)return sum[k];
	int mid=l+r>>1;
	ull res=0;
	pushdown(k,l,r,mid);
	if(x<=mid)res+=query(k<<1,l,mid,x,y);
	if(mid<y)res+=query(k<<1|1,mid+1,r,x,y);
	return res;
}
inline void modify(int k,int l,int r,int x,int y,int v)
{
	if(l>=x&&r<=y)
	{

		return Add(k,l,r,v);
	}
	int mid=l+r>>1;
	pushdown(k,l,r,mid);
	if(x<=mid)modify(k<<1,l,mid,x,y,v);
	if(mid<y)modify(k<<1|1,mid+1,r,x,y,v);
	sum[k]=sum[k<<1]+sum[k<<1|1];
}
int main()
{
	n=read();
	m=read();
	//scanf("%d%d",&n,&m);
	for(register int i=1; i<=n; i++)a[i]=read();
	build(1,1,n);
	int op,A,B,C;
	while(m--)
	{
		op=read();
		if(op==2)
		{
			A=read();
			B=read();
			printf("%lld\n",query(1,1,n,A,B));
		}
		else
		{
			A=read();
			B=read();
			C=read();
			modify(1,1,n,A,B,C);
		}
	}
}
