#include<cstdio>
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
const int N=1e6+5;
int n,m,c;
int a[N];
int headmax,tailmax,qmax[N],qmin[N],headmin,tailmin;
bool flag;
int main()
{
	read(n);
	read(m);
	read(c);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	headmin=headmax=1;
	for(re int i=1; i<=n; ++i)
	{
		while(headmin<=tailmin&&qmin[headmin]+m<=i)
			++headmin;
		while(headmax<=tailmax&&qmax[headmax]+m<=i)
			++headmax;
		while(headmin<=tailmin&&a[qmin[tailmin]]>a[i])
			--tailmin;
		while(headmax<=tailmax&&a[qmax[tailmax]]<a[i])
			--tailmax;
		qmin[++tailmin]=qmax[++tailmax]=i;
		if(i>=m&&a[qmax[headmax]]-a[qmin[headmin]]<=c)
		{
			printf("%d\n",i-m+1);
			flag=true;
		}
		/*printf("%d:\n",i);
		for(re int i=headmin; i<=tailmin; ++i)
			printf("%d ",a[qmin[i]]);
		printf("\n");
		for(re int i=headmax; i<=tailmax; ++i)
			printf("%d ",a[qmax[i]]);
		printf("\n\n");*/
	}
	if(!flag)
		printf("NONE\n");
	return 0;
}
