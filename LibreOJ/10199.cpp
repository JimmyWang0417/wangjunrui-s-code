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
struct node
{
	int sum,answer;
} keke[int(1e6+5)];
int n,a[int(1e6+5)];
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
	{
		read(a[i]);
		keke[a[i]].sum++;
	}
	for(re int i=1; i<=1000000; i++)
		for(re int j=2; j<=1000000/i; j++)
			keke[i*j].answer+=keke[i].sum;
	for(re int i=1; i<=n; i++)
		printf("%d\n",keke[a[i]].answer+keke[a[i]].sum-1);
}

