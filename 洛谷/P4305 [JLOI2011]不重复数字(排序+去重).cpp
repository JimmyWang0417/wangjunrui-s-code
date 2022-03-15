#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}
const int N=5e4+5;
int n;
struct node
{
	int val,id;
	inline bool operator <(const node &rhs)const
	{
		return val<rhs.val||val==rhs.val&&id<rhs.id;
	}
	inline bool operator ==(const node &rhs)const
	{
		return val==rhs.val;
	}
} a[N];
inline bool cmp(const node &x,const node &y)
{
	return x.id<y.id;
}
int main()
{
	int T;
	read(T);
	while(T--)
	{
		read(n);
		for(re int i=1; i<=n; ++i)
		{
			read(a[i].val);
			a[i].id=i;
		}
		sort(a+1,a+1+n);
		n=unique(a+1,a+1+n)-1-a;
//		printf("%d\n",n);
		sort(a+1,a+1+n,cmp);
		for(re int i=1; i<=n; ++i)
			printf("%d ",a[i].val);
		putchar('\n');
	}
	return 0;
}
