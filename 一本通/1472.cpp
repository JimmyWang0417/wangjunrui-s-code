#include<cstdio>
using namespace std;
#define r register
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
inline int max(int a,int b)
{
	return a>b?a:b;
}
int n,a[100001],ch[1531080<<1][2],tot=1,maxx;
inline void insert(int x)
{
	for(r int i=1<<30,u=1,c; i; i>>=1)
	{
		c=(x&i)?1:0;
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
}
inline int find(int x)
{
	r int u=1,ans=0,i,c;
	for(i=1<<30; i; i>>=1)
	{
		c=(x&i)?0:1;
		if(ch[u][c])
		{
			ans+=i;
			u=ch[u][c];
		}
		else u=ch[u][!c];
	}
	return ans;
}
int main()
{
	n=read();
	for(r int i=1; i<=n; i++)
	{
		a[i]=read();
		insert(a[i]);
	}
	for(r int i=1; i<=n; i++)
		maxx=max(maxx,find(a[i]));
	//printf("%d\n",find(a[i]));
	printf("%d\n",maxx);
}
