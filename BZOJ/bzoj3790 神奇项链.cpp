#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define ll long long
using namespace std;
const int N=1e6+5;
int len,p[N],ans;
char str[N];
struct node
{
	int l,r;
	inline bool operator < (const node &rhs)const
	{
		return l<rhs.l||l==rhs.l&&r<rhs.r;
	}
} a[N];
inline void init()
{
	len=strlen(str+1);
	for(re int i=len; i>=1; --i)
	{
		str[i<<1]=str[i];
		str[i<<1|1]='|';
	}
	str[0]='~';
	str[1]='|';
	len=len<<1|1;
	str[len+1]='$';
}
inline void manacher()
{
	for(re int i=1,mid=0,maxx=0; i<=len; ++i)
	{
		p[i]=maxx>i?min(maxx-i,p[(mid<<1)-i]):1;
		while(str[i-p[i]]==str[i+p[i]])
			++p[i];
		if(i+p[i]>maxx)
		{
			maxx=i+p[i];
			mid=i;
		}
		a[i].l=i-p[i]+1;
		a[i].r=i+p[i]-1;
	}
}
inline void work()
{
	init();
	manacher();
//	printf("%s",str);
	sort(a+1,a+1+len);
//	for(re int i=1; i<=len; ++i)
//		printf("%d %d\n",a[i].l,a[i].r);
	ans=-1;
	for(re int i=1,j=1,maxx=0; i<=len;)
	{
		while(j<=len&&a[j].l<=i)
			maxx=max(maxx,a[j++].r);
		i=maxx+1;
		++ans;
	}
	printf("%d\n",ans);
}
int main()
{
	while(scanf("%s",str+1)!=EOF)
		work();
	return 0;
}
