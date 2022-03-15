#include<cstdio>
#include<cstring>
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
const int N=1e6+10;
int p[N],str[N],n,a,b,tmp[N];
inline void pre()
{
	memset(p,0,sizeof(p));
	p[1]=-1;
	for(re int i=2,j=0; i<=n; ++i)
	{
		while(j!=0&&tmp[i]!=tmp[j+1])
			j=p[j];
		if(j==0||tmp[i]==tmp[j+1])
			++j;
		p[i]=j;
	}
}
inline void solve1()
{
	for(re int i=1; i<=n; ++i)
		tmp[i]=str[i]%a;
	pre();
	if(n%(n-p[n]))
		printf("0\n");
	else
		printf("%d\n",n/(n-p[n]));
}
inline void solve2()
{
	int ans=0;
	for(re int i=1; i<=n; ++i)
		tmp[i]=str[i]%a;
	pre();
	if(n%(n-p[n]))
		ans=0;
	else
		ans=n/(n-p[n]);
	for(re int i=1; i<=n; ++i)
		tmp[i]=str[i]%b;
	if(!n%(n-p[n]))
		ans=n/(n-p[n]);
	printf("%d\n",ans);
}
int main()
{
	int T;
	read(T);
	while(T--)
	{
		read(n),read(a),read(b);
		for(re int i=1; i<=n; ++i)
			read(str[i]);
		if(a==b)
			solve1();
		else
			solve2();
	}
}
