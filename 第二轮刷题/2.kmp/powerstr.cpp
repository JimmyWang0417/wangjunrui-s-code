#include<cstdio>
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
const int N=1e6+1;
char a[N],b[N];
int p[N],n,m;
inline void pre()
{
	p[1]=0;
	for(r int i=1,j=0; i<m; i++)
	{
		while(j>0&&b[j+1]!=b[i+1])
			j=p[j];
		if(b[j+1]==b[i+1])
			j++;
		p[i+1]=j;
	}
}
inline int kmp()
{
	r int i=0,ans=0,j=0;
	for(i=0; i<n; i++)
	{
		while(j>0&&b[j+1]!=a[i+1])
			j=p[j];
		if(b[j+1]==a[i+1])
			j++;
		if(j==m)
		{
			ans++;
			j=0;
		}
	}
	return ans;
}
int main()
{
	int T;
	scanf("%d",&T); 
	while(T--)
	{
		scanf("%s",b+1);
		m=strlen(b+1);
		pre();
		if(m%(m-p[m])==0)
			printf("%d\n",m/(m-p[m]));
		else
			printf("1\n");
	}
}
