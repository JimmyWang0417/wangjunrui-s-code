#include<cstdio>
#define re register
#define ll long long
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
const int N=1e6+5;
int fmin[N],fmax[N],a[N],n,q[N],k;
int main()
{
	read(n),read(k);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	re int head=1,tail=0;
	for(re int i=1; i<=n; ++i)
	{
		while(head<=tail&&q[head]<i-k+1)
			++head;
		while(head<=tail&&a[q[tail]]>=a[i])
			--tail;
		q[++tail]=i;
		fmin[i]=q[head];
		/*for(re int j=head; j<=tail; ++j)
			printf("%d ",a[q[j]]);
		putchar('\n');*/
	}
	for(re int i=k; i<=n; ++i)
		printf("%d ",a[fmin[i]]);
	putchar('\n');
	head=1,tail=0;
	for(re int i=1; i<=n; ++i)
	{
		while(head<=tail&&q[head]<i-k+1)
			++head;
		while(head<=tail&&a[q[tail]]<=a[i])
			--tail;
		q[++tail]=i;
		fmax[i]=q[head];
		/*for(re int j=head; j<=tail; ++j)
			printf("%d ",a[q[j]]);
		putchar('\n');*/
	}
	for(re int i=k; i<=n; ++i)
		printf("%d ",a[fmax[i]]);
	putchar('\n');
	return 0;
}
