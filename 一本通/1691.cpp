#include<cstdio>
#include<map>
#define re register
using namespace std;
#define ull long long
const int N=200010;
const ull p1=1e6+3,p2=1e9+7;
int n,m,ans,head[p1+10],num_edge;
ull power1[N],sum1[N],x;
char s[N];
ull power2[N],sum2[N],y;
map<ull,bool>b1,b2;
struct node
{
	int next;
	ull date;
} edge[N];
inline void insert(ull sum1,ull sum2)
{
	edge[++num_edge].next=head[sum1];
	edge[num_edge].date=sum2;
	head[sum1]=num_edge;
}
inline bool find(ull sum1,ull sum2)
{
	for(re int i=head[sum1]; i; i=edge[i].next)
		if(edge[i].date==sum2)
			return true;
	return false;
}
int main()
{
	scanf("%d%d%s",&n,&m,s+1);
	power1[0]=power2[0]=1;
	for(re int i=1; i<=n; i++)
	{
		power1[i]=power1[i-1]*27%p1;
		power2[i]=power2[i-1]*27%p2;
	}
	for(re int i=1; i<=n; i++)
	{
		sum1[i]=(sum1[i-1]*27%p1+s[i]-'a'+1)%p1;
		sum2[i]=(sum2[i-1]*27%p2+s[i]-'a'+1)%p2;
	}
	for(re int i=0; i+m<=n; i++)
	{
		x=((sum1[i+m]-sum1[i]*power1[m]%p1)%p1+p1)%p1;
		y=((sum2[i+m]-sum2[i]*power2[m]%p2)%p2+p2)%p2;
		if(find(x,y))
			continue;
		insert(x,y);
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}

