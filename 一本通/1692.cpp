#include<cstdio>
#include<cstring>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
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
	if(f)
		x=(~x)+1;
}
#define solve(x,len) (x<len?x:0)
const int LEN=1e6+10;
int p[LEN],t[LEN],s[LEN],n,m,last[LEN],T,C,ans[LEN],top;
char a[LEN],b[LEN];
inline void pre()
{
	p[1]=0;
	for(re int i=1,j=0; i<m; i++)
	{
		while(j&&solve(t[i+1],j+1)!=solve(t[j+1],j+1))
			j=p[j];
		if(solve(t[i+1],j+1)==solve(t[j+1],j+1))
			j++;
		p[i+1]=j;
	}
}
inline void kmp()
{
	for(re int i=0,j=0; i<n; i++)
	{
		while(j&&solve(s[i+1],j+1)!=solve(t[j+1],j+1))
			j=p[j];
		if(solve(s[i+1],j+1)==solve(t[j+1],j+1))
			j++;
		if(j==m)
		{
			ans[++top]=i+1-m+1;
			j=p[j];
		}
	}
	printf("%d\n",top);
	for(re int i=1; i<=top; i++)
		printf("%d ",ans[i]);
	putchar('\n');
	top=0;
}
int main()
{
	read(n);
	read(m);
	scanf("%s%s",a+1,b+1);
	for(re int i=1; i<=n; i++)
	{
		s[i]=i-last[a[i]];
		last[a[i]]=i;
	}
	memset(last,0,sizeof(last));
	for(re int i=1; i<=m; i++)
	{
		t[i]=i-last[b[i]];
		last[b[i]]=i;
	}
	memset(last,0,sizeof(last));
	/*for(re int i=1; i<=n; i++)
		printf("%d %d\n",s[i],t[i]);*/
	pre();
	kmp();
	/*for(re int i=1; i<=m; i++)
		printf("%d ",p[i]);
	putchar('\n');*/
	return 0;
}
