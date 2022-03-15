#include<cstdio>
#define re register
#define ll long long
#define max(x,y)((x)>(y)?(x):(y))
#define solve(x) (f[x][0]-sum[x])
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
const int N=1e5+5;
int q[N],n,k;
ll sum[N],f[N][2];
int main()
{
	read(n),read(k);
	re int head=0,tail=0;
	for(re int i=1,tmp; i<=n; ++i)
	{
		read(tmp);
		f[i][0]=max(f[i-1][1],f[i-1][0]);
		sum[i]=sum[i-1]+tmp;
		while(head<=tail&&q[head]<i-k)
			++head;
		f[i][1]=f[q[head]][0]-sum[q[head]]+sum[i];
		while(head<=tail&&solve(q[tail])<=solve(i))
			--tail;
		q[++tail]=i;
	}
	printf("%lld\n",max(f[n][0],f[n][1]));
	return 0;
}
