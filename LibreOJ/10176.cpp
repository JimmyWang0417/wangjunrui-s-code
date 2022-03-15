#include<cstdio>
#define re register
#define ll long long
#define cmax(x,y)if(y>x)x=y
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
int n,m,s[N],q[N],ans=-0x3f3f3f3f;
int main()
{
	read(n),read(m);
	re int head=0,tail=0;
	for(re int i=1,tmp; i<=n; ++i)
	{
		read(tmp);
		s[i]=s[i-1]+tmp;
		while(head<=tail&&q[head]<i-m)
			++head;
		cmax(ans,s[i]-s[q[head]]);
		while(head<=tail&&s[q[tail]]>=s[i])
		--tail;
		q[++tail]=i;
	}
	printf("%d\n",ans);
	return 0;
}
