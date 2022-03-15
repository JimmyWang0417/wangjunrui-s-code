#include<cstdio>
#define ull unsigned long long
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
const int mod=1e6+7;
int head[mod+10],num_edge;
struct node
{
	int next;
	ull val;
} edge[2000010];
inline void insert(int val)
{
	int tmp=val%mod;
	edge[++num_edge].next=head[tmp];
	head[tmp]=num_edge;
	edge[num_edge].val=val;
}
inline bool find(int val)
{
	for(re int i=head[val%mod]; i; i=edge[i].next)
		if(edge[i].val==val)
			return 1;
	return 0;
}
int A,B,C;
int a[2000010]= {1};
int main()
{
	read(A),read(B),read(C);
	insert(a[0]);
	for(re int i=1; i<=2000000; ++i)
	{
		a[i]=(1ull*A*a[i-1]+a[i-1]%B)%C;
		if(find(a[i]))
		{
			printf("%d\n",i);
			return 0;
		}
		insert(a[i]);
	}
	printf("-1\n");
	return 0;
}
