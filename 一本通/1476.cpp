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
int n,m,ch[1000010][2],s[10010],sum[1000010],bo[1000010],tot=1;
inline void insert(int s[])
{
	int u=1;
	for(r int i=1,c; i<=s[0]; i++)
	{
		c=s[i];
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
		sum[u]++;
	}
	bo[u]++;
}
inline void find(int s[])
{
	int u=1,ans=0;
	for(r int i=1,c; i<=s[0]; i++)
	{
		c=s[i];
		ans+=bo[u];
		u=ch[u][c];
	}
	printf("%d\n",ans+sum[u]);
}
int main()
{
	n=read();
	m=read();
	for(r int j=1; j<=n; j++)
	{
		s[0]=read();
		for(r int i=1; i<=s[0]; i++)
			s[i]=read();
		insert(s);
	}
	for(r int j=1; j<=m; j++)
	{
		s[0]=read();
		for(r int i=1; i<=s[0]; i++)
			s[i]=read();
		find(s);
	}
}

