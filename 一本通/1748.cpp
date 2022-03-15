#include<cstdio>
#define re register
#define update(x,y) (father[find(x)]=find(y))
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
	return;
}
const int N=1e5+10,mod=1e9+7;
int n,m,id[N][20],f[N][20],log[N],time,left[N*20],right[N*20],l1,l2,r1,r2,father[N*20];
inline int find(int x)
{
	return x==father[x]?x:father[x]=find(father[x]);
}
int main()
{
	read(n);
	read(m);
	int x=n;
	re long long ans=9ll;
	re int tot=0;
	for(re int i=1; i<=n; i++)
		id[i][0]=++time;
	for(re int i=2; i<=n; i++)
		log[i]=log[i>>1]+1;
	for(re int j=1; j<=log[n]; j++)
		for(re int i=1; i+(1<<j)-1<=n; i++)
		{
			id[i][j]=++time;
			left[time]=id[i][j-1];
			right[time]=id[i+(1<<j-1)][j-1];
		}
	for(re int i=1; i<=log[n]*n; i++)
		father[i]=i;
	while(m--)
	{
		read(l1);
		read(r1);
		read(l2);
		read(r2);
		int p=log[r1-l1];
		update(id[l1][p],id[l2][p]);
		update(id[r1-(1<<p)+1][p],id[r2-(1<<p)+1][p]);
	}
	for(re int i=time; i>0; i--)
	{
		int x=find(i);
		if(x!=i)
		{
			update(left[x],left[i]);
			update(right[x],right[i]);
		}
	}
	for(re int i=1; i<=n; i++)
		if(i==find(i))
			tot++;
	for(re int i=1; i<tot; i++)
		ans=(ans*10ll)%mod;
	printf("%lld\n",ans);
	return 0;
}
