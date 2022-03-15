/*https://www.luogu.org/problemnew/show/P1056*/
#include<cstdio>
#include<algorithm>
using namespace std;
int m,n,k,l,d,
    x,y,p,q;
int min(int a,int b)
{
	return a<b?a:b;
}
struct node
{
	int date,i;
} lsort[1001],ksort[1001];
bool lt[1001],kt[1001];
bool comp1(node a,node b)
{
	return a.date>b.date;
}
bool comp2(node a,node b)
{
	return a.i<b.i;
}
int lnum,knum;
int main()
{
	scanf("%d%d%d%d%d",&m,&n,&k,&l,&d);
	for(register int i=1; i<=m; i++)
		ksort[i].i=i;
	for(register int i=1; i<=n; i++)
		lsort[i].i=i;
	for(register int i=1; i<=d; i++)
	{
		scanf("%d%d%d%d",&x,&y,&p,&q);
		if(y!=q)
			lsort[min(y,q)].date++;
		else
			ksort[min(x,p)].date++;
	}
	sort(lsort+1,lsort+n,comp1);
	sort(ksort+1,ksort+m,comp1);
	for(register int i=1; i<=l; i++)
		lt[lsort[i].i]=true;
	for(register int i=1; i<=k; i++)
		kt[ksort[i].i]=true;
	for(register int i=1; i<=m; i++)
		if(kt[i])
			printf("%d ",i);
	putchar('\n');
	for(register int i=1; i<=n; i++)
		if(lt[i])
			printf("%d ",i);
	putchar('\n');
}
