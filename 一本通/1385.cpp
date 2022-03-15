#include<cstdio>
using namespace std;
int father[1001],enemy[1001],n,m,x,y,sum;
int p;
inline int find(int x)
{
	if(father[x]!=x)return father[x]=find(father[x]);
	return x;
}
inline void unionn(int x,int y)
{
	int fx=find(x),fy=find(y);
	father[fx]=fy;
}
inline int read()
{
	int x=0;
	char s=getchar();
	while(s<'0'||s>'9')
	{
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<3)+(x<<1)+s-'0';
		s=getchar();
	}
	return x;
}
inline void write(int x)
{
	int y=0xa,len=1;
	while(y<=x)
	{
		y*=0xa;
		len++;
	}
	while(len--)
	{
		y/=0xa;
		putchar(x/y+0x30);
		x%=y;
	}
}
int main()
{
	n=read();
	m=read();
	for(register int i=1; i<=n; i++)
		father[i]=i;
	for(register int i=1; i<=m; i++)
	{
		p=read();
		x=read();
		y=read();
		int fy=find(y);
		if(p==0)
			unionn(x,y);
		else
		{
			if(!enemy[x])
				enemy[x]=y;
			else
				unionn(enemy[x],y);
			if(!enemy[y])
				enemy[y]=x;
			else
				unionn(enemy[y],x);
		}
	}
	for(register int i=1; i<=n; i++)
		if(father[i]==i)
			sum++;
	write(sum);
}
