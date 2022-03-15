/*https://www.luogu.org/problemnew/show/P1563*/
#include<cstdio>
using namespace std;
int n,m,x,y,t;
struct node
{
	char s[11];
	int i;
} a[100001];
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=0; i<n; i++)
		scanf("%d%s",&a[i].i,a[i].s);
	for(register int m1=1;m1<=m;m1++)
	{
		scanf("%d%d",&x,&y);
		if((a[t].i+x)%2)
		  t=(t+y)%n;
		else
		  t=(t-y%n+n)%n;
	}
	printf("%s\n",a[t].s);
}
