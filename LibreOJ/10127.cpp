#include<cstdio>
#define re register
using namespace std;
int n,m,p;
long long maxx[200010<<2],a;
inline int max(int a,int b)
{
	return a>b?a:b;
}
inline int read()
{
	char s=getchar();
	bool f=false;
	int x=0;
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
	return f?-x:x;
}
inline void update(int root,int l,int r,int x,long long v)
{
	if(l>x||r<x)
		return;
	if(l==r&&r==x)
	{
		maxx[root]=v;
		return;
	}
	int mid=l+r>>1;
	update(root<<1,l,mid,x,v);
	update(root<<1|1,mid+1,r,x,v);
	maxx[root]=max(maxx[root<<1],maxx[root<<1|1]);
}
inline int query(int root,int l,int r,int x,int y)
{
	if(l>y||r<x)
		return 0;
	if(l>=x&&r<=y)
		return maxx[root];
	int mid=l+r>>1;
	return max(query(root<<1,l,mid,x,y),query(root<<1|1,mid+1,r,x,y));
}
int main()
{
	m=read();
	p=read();
	for(re int i=1,x; i<=m; i++)
	{
		char s=getchar();
		while(s!='A'&&s!='Q')
			s=getchar();
		if(s=='A')
		{
			x=read();
			++n;
			update(1,1,m,n,((long long)x+a)%(long long)p);
		}
		else
		{
			x=read();
			printf("%lld\n",a=query(1,1,m,n-x+1,n));
		}
	}
	return 0;
}

