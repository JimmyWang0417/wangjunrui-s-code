#include<cstdio>
using namespace std;
#define r register
inline int read()
{
	char s=getchar();
	bool f=false;
	int x=0;
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
	return f?-x:x;
}
const int p1=1e6+9,p2=1<<22-1,N=2000001;
int first[(int)1e6+10];
int tot=0,A,B,C;
struct node
{
	int next;
	int end;
} a[N+1];
inline void insert(int x,int y)
{
	a[++tot].next=first[x];
	first[x]=tot;
	a[tot].end=y;
}
inline bool query(int x,int y)
{
	for(r int i=first[x]; i; i=a[i].next)
		if(a[i].end==y)
			return true;
	return false;
}
unsigned long long sum1=1,sum2=1;
int main()
{
	A=read();
	B=read();
	C=read();
	insert(sum1,sum2);
	for(register int i=1; i<=2000000; i++)
	{
		sum2=((sum2*A+sum2%B)%C);
		sum1=sum2%p1;
		if(query(sum1,sum2))
		{
			printf("%d\n",i);
			return 0;
		}
		insert(sum1,sum2);
	}
	printf("-1\n");
	return 0;
}
