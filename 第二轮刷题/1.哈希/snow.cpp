#include<cstdio>
#define ull unsigned long long
#define re register
#define max(x,y) ((x)>(y)?(x):(y))
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
const int mod=2e7+7,N=1000010;
int head[mod+10],num_edge;
struct Edge
{
	int next;
	int val;
	bool vis;
} edge[2000010];
inline void pop(int val)
{
	for(re int i=head[val%mod]; i; i=edge[i].next)
		if(!edge[i].vis&&edge[i].val==val)
			edge[i].vis=true;
	return;
}
inline void insert(int val)
{
	int tmp=val%mod;
	edge[++num_edge].next=head[tmp];
	head[tmp]=num_edge;
	edge[num_edge].val=val;
}
inline int find(int val)
{
	for(re int i=head[val%mod]; i; i=edge[i].next)
		if(edge[i].val==val)
			return edge[i].vis?i:-(edge[i].vis=true);
	return false;
}
int n,x[N],ans;
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(x[i]);
		insert(x[i]);
	}
	for(re int l=1,r=1; r<=n; ++r)
	{
		if(ans>n-l)
			break;
		if(r-l>ans)
			ans=r-l;
		if(find(x[r])!=-1)
		{
			if(r-l>ans)
				ans=r-l;
			while(x[l]!=x[r])
				edge[find(x[l++])].vis=false;
			l++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
