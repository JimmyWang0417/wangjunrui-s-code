#include<cstdio>
#define re register
using namespace std;
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
const int N=1e5+10;
int c1[N],c2[N],n,m,k,l,r;
inline int lowbit(int x)
{
	return x&(-x);
}
inline void update1(int x,int y)
{
	for(; x<=n; x+=lowbit(x))
		c1[x]+=y;
}
inline void update2(int x,int y)
{
	for(; x<=n; x+=lowbit(x))
		c2[x]+=y;
}
inline int sum1(int x)
{
	int ans=0;
	for(; x; x-=lowbit(x))
		ans+=c1[x];
	return ans;
}
inline int sum2(int x)
{
	int ans=0;
	for(; x; x-=lowbit(x))
		ans+=c2[x];
	return ans;
}
int main()
{
	n=read();
	m=read();
	for(re int i=1; i<=m; i++)
	{
		int k=read(),l=read(),r=read();
		if(k==1)
		{
			update1(l,1);
			update2(r,1);
		}
		else
			printf("%d\n",sum1(r)-sum2(l-1));
	}
	return 0;
}
