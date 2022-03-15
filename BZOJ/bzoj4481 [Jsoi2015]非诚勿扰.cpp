#include<cstdio>
#include<algorithm>
#define re register
#define lowbit(x) ((x)&(-x))
#define ld long double
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
const int N=500000+5;
int n,m;
ld p,c[N],prime[N],ans;
inline void update(int x,ld y)
{
	for(; x<=n; x+=lowbit(x))
		c[x]+=y;
}
inline ld query(int x)
{
	ld res=0.0;
	for(; x; x-=lowbit(x))
		res+=c[x];
	return res;
}
int outedge[N];
struct node
{
	int x,y;
	inline bool operator < (const node &rhs)const
	{
		return (x==rhs.x&&y<rhs.y)||x<rhs.x;
	}
} a[N];
#define get(x,y) (p*prime[y-1]/(1-prime[outedge[x]]))
int main()
{
	read(n);
	read(m);
	scanf("%Lf",&p);
	prime[0]=1.0;
	for(re int i=1; i<=m; ++i)
		prime[i]=prime[i-1]*(1-p);
	for(re int i=1; i<=m; ++i)
	{
		read(a[i].x);
		read(a[i].y);
		++outedge[a[i].x];
	}
	std::stable_sort(a+1,a+1+m);
	int head=1;
	for(re int i=1; i<=n; ++i)
	{
		int cnt=0;
		ld tmp;
		while(a[head].x==i)
		{
			++cnt;
			tmp=get(i,cnt);
			update(a[head].y,tmp);
			ans+=(query(n)-query(a[head].y))*tmp;
			++head;
		}
	}
	printf("%.2lf\n",(double)ans);
	return 0;
}
