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
int n;
struct node
{
	int price,tim;
	bool vis;
} q[1000010];
long long ans=0;
int main()
{
	re int head=1,tail=0;
	scanf("%d",&n);
	int opt,p,t;
	for(re int i=1; i<=n; ++i)
	{
		read(opt);
		read(p);
		read(t);
		if(opt==0)
		{
			++tail;
			q[tail].price=p;
			q[tail].tim=t;
			q[tail].vis=false;
			ans+=p;
		}
		else if(opt==1)
		{
			while((q[head].tim+45<t||q[head].vis)&&head<=tail)
				++head;
			bool flag=true;
			for(re int j=head; j<=tail; ++j)
				if(q[j].price>=p&&!q[j].vis)
				{
					flag=false;
					q[j].vis=true;
					break;
				}
			if(flag)
			{
				ans+=p;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
