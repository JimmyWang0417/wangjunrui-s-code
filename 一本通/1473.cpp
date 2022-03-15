#include<cstdio>
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
inline int max(int a,int b)
{
	return a>b?a:b;
}
int n,a[400001],ch[1531080<<3][2],tot=1,maxx,now,l[400001],r[400001];
inline void insert(int x)
{
	for(register int i=1<<30,u=1,c; i; i>>=1)
	{
		c=(x&i)?1:0;
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
}
inline int find(int x)
{
	register int u=1,ans=0,i,c;
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
	insert(now=0);
	for(register int i=1; i<=n; i++)
	{
		a[i]=read();
		now^=a[i];
		insert(now);
		l[i]=max(l[i-1],find(now));
	}
	for(register int i=1; i<=tot; i++)
		ch[i][1]=ch[i][0]=0;
	insert(now=0);
	for(register int i=n; i>=1; i--)
	{
		now^=a[i];
		insert(now);
		r[i]=max(r[i+1],find(now));
	}
	for(register int i=1; i<n; i++)
		maxx=max(maxx,l[i]+r[i+1]);
	printf("%d\n",maxx);
}
