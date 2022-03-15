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
const int N=5e5+10;
int c[N],a[N],n,k,m,p;
inline int lowbit(int x)
{
	return x&(-x);
}
inline void update(int x,int y)
{
	for(; x<=n; x+=lowbit(x))
		c[x]+=y;
}
inline int sum(int x)
{
	int ans=0;
	for(; x; x-=lowbit(x))
		ans+=c[x];
	return ans;
}
int main()
{
	n=read();
	k=read();
	for(re int i=1; i<=k; i++)
	{
		char s=getchar();
		while(!(s>='A'&&s<='C'))
			s=getchar();
		if(s=='A')
		{
			m=read();
			printf("%d\n",sum(m));
		}
		else if(s=='B')
		{
			m=read();
			p=read();
			update(m,p);
		}
		else
		{
			m=read();
			p=read();
			update(m,~p+1);
		}
	}
}

