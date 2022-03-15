#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
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
const int N=100007;
int father[N],l,r,mid1,mid2,m,n,op,q;
double k1,k2,ans;
struct edge
{
	int x,y;
	double u,v;
} a[N];
struct node
{
	double k1,k2,a,b;
} head,tail,b[N];
inline bool cmp(edge x,edge y)
{
	return x.u*k1+x.v*k2<y.u*k1+y.v*k2;
}
inline int find(int x)
{
	if(!father[x])
		return x;
	return father[x]=find(father[x]);
}
inline void kruskal(node &x)
{
	k1=x.k1;
	k2=x.k2;
	int i,k=0;
	x.a=x.b=0;
	sort(a+1,a+1+m,cmp);
	/*for(re int i=1; i<=m; i++)
		printf("%d %d %lf %lf\n",a[i].x,a[i].y,a[i].u,a[i].v);*/
	memset(father,0,sizeof(father));
	for(re int i=1,fx,fy; i<=m; i++)
	{
		fx=find(a[i].x);
		fy=find(a[i].y);
		if(fx!=fy)
		{
			father[fx]=fy;
			k++;
			x.a+=a[i].u;
			x.b+=a[i].v;
		}
		if(k==n-1)
			break;
	}
	return;
}
inline void dfs(node l,node r)
{
	node mid;
	mid.k1=fabs(l.b-r.b);
	mid.k2=fabs(l.a-r.a);
	kruskal(mid);
	if(l.b==r.b||l.b==mid.b||(l.a-r.a)/(l.b-r.b)==(l.a-mid.a)/(l.b-mid.b))
		return;
	dfs(l,mid);
	b[++op]=mid;
	dfs(mid,r);
}
int main()
{
	read(n);
	read(m);
	read(q);
	for(re int i=1; i<=m; i++)
	{
		read(a[i].x);
		read(a[i].y);
		scanf("%lf%lf",&a[i].u,&a[i].v);
		if(a[i].x>a[i].y)
			swap(a[i].x,a[i].y);
	}
	/*for(re int i=1; i<=m; i++)
		printf("%d %d %lf %lf\n",a[i].x,a[i].y,a[i].u,a[i].v);*/
	head.k1=1;
	head.k2=0;
	tail.k1=0;
	tail.k2=1;
	kruskal(head);
	kruskal(tail);
	b[op=1]=head;
	dfs(head,tail);
	b[++op]=tail;
	/*for(re int i=1; i<=op; i++)
		printf("%lf %lf %lf %lf\n",b[i].a,b[i].b,b[i].k1,b[i].k2);*/
	while(q--)
	{
		scanf("%lf%lf",&k1,&k2);
		ans=1e15;
		l=1;
		r=op;
		while(l<r)
		{
			if(r-l<=2)
				break;
			mid1=l+(r-l+1)/3;
			mid2=l+(r-l+1)/3*2;
			if(b[mid1].a*k1+b[mid1].b*k2<b[mid2].a*k1+b[mid2].b*k2)
				r=mid2;
			else
				l=mid1;
		}
		for(re int i=l; i<=r; i++)
			ans=min(ans,b[i].a*k1+b[i].b*k2);
		printf("%.3lf\n",ans);
	}
	return 0;
}

