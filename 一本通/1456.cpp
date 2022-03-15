#include<cstdio>
#include<iostream>
#include<cstring>
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
const int mod1=1e6+3,mod2=1e6+9,p1=47,p2=79,N=30000;
int tot=0,first[mod1+1];
char a1[2][5]={"no","yes"};
struct node
{
	int next,end;
} a[N+1];
inline void insert(int x,int y)
{
	a[++tot].next=first[x];
	first[x]=tot;
	a[tot].end=y;
}
inline bool query(int x,int y)
{
	for(r int i=first[x]; i; i=a[i].next)
		if(a[i].end==y)
			return true;
	return false;
}
int main()
{
	r int n=read(),len,sum1,sum2;
	r char op[10],s[205];
	while(n--)
	{
		cin>>op;
		gets(s);
		len=strlen(s);
		sum1=0;
		sum2=0;
		for(r int i=0;i<len;i++)
		{
			sum1=(sum1*p1+s[i])%mod1;
			sum2=(sum2*p2+s[i])%mod2;
		}
		if(op[0]=='a')insert(sum1,sum2);
		else printf("%s\n",a1[query(sum1,sum2)]);
	}
}
