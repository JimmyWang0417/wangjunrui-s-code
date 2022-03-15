#include<cstdio>
#define re register
const int wei=30;
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
const int N=1e5+10;
int n,m,suml[N],sumr[N],a[N],ch[N*31][2],tot=1;
inline int opp(int x)
{
	return (((x>>m-1)&1)|((x<<1)&((1<<m)-1)));
}
inline void insert(int x)
{
	int u=1;
	for(re int i=m-1; i>=0; i--)
	{
		bool c=x>>i&1;
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
}
int ans,sum;
inline void find(int dep,int u,int res)
{
	if(dep==-1)
	{
		if(res>ans)
		{
			ans=res;
			sum=1;
		}
		else if(res==ans)
			sum++;
		return;
	}
	if(!ch[u][0])
		find(dep-1,ch[u][1],res|(1<<dep));
	else if(!ch[u][1])
		find(dep-1,ch[u][0],res|(1<<dep));
	else
	{
		find(dep-1,ch[u][0],res);
		find(dep-1,ch[u][1],res);
	}
	return;
}
int main()
{
	read(m);
	read(n);
	//printf("%d\n",opp(0b101));
	for(re int i=1; i<=n; i++)
		read(a[i]);
	for(re int i=1; i<=n; i++)
		suml[i]=suml[i-1]^opp(a[i]);
	for(re int i=n; i>=1; i--)
		sumr[i]=sumr[i+1]^a[i];
	for(re int i=0; i<=n; i++)
		insert(suml[i]^sumr[i+1]);
	find(m-1,1,0);
	printf("%d\n%d\n",ans,sum);
	return 0;
}
