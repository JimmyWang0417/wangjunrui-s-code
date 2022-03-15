#include<cstdio>
using namespace std;
int n,tot,m,val,w[10001],c[10001],f[10001],father[10001];
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
inline int find(int x)
{
	if(father[x]!=x)return father[x]=find(father[x]);
	return x;
}
int main()
{
	n=read();
	m=read();
	val=read();
	for(int i=1; i<=n; i++)
		father[i]=i;
	for(register int i=1; i<=n; i++)
	{
		w[i]=read();
		c[i]=read();
	}
	for(register int i=1; i<=m; i++)
	{
		int x=read(),y=read();
		int fx=find(x),fy=find(y);
		if(fx!=fy)
		{
			father[fy]=fx;
			w[fx]+=w[fy];
			c[fx]+=c[fy];
		}
	}
	for(register int i=1; i<=n; i++)
		if(father[i]==i)
		{
			w[++tot]=w[i];
			c[tot]=c[i];
		}
	for(int i=1; i<=tot; i++)
		for(int j=val; j>=w[i]; j--)
			if(f[j-w[i]]+c[i]>f[j])
				f[j]=f[j-w[i]]+c[i];
	write(f[val]);
}
