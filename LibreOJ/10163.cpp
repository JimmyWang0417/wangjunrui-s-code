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
int f[32][32],x,y,k,b,a[32],top,res;
inline void init()
{
	f[0][0]=1;
	for(re int i=1; i<=31; i++)
	{
		f[i][0]=1;
		for(re int j=1; j<=i; j++)
			f[i][j]=f[i-1][j]+f[i-1][j-1];
	}
}
inline int calc(int x,int k)
{
	int tot=0,ans=0;
	for(re int i=31; i>0; i--)
	{
		if(x&(1<<i))
		{
			tot++;
			if(tot>k)
				break;
			x^=(1<<i);
		}
		if(1<<(i-1)<=x)
			ans+=f[i-1][k-tot];
	}
	if(tot+x==k)ans++;
	return ans;
}
inline int change(int x)
{
	res=top=0;
	while(x>0)
	{
		a[++top]=x%b;
		x/=b;
	}
	for(re int i=top; i>=1; i--)
	{
		if(a[i]==1||a[i]==0)
			res=(res<<1)+a[i];
		else
		{
			res=(res<<1)+1;
			a[i-1]=b-1;
		}
	}
	return res;
}
int main()
{
	x=read();
	y=read();
	k=read();
	b=read();
	init();
	printf("%d\n",calc(change(y),k)-calc(change(x-1),k));
	return 0;
}

