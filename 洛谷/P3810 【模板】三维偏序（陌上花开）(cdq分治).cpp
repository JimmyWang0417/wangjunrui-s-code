#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1e5+5;
struct node
{
	int a,b,c,cnt,sum;
	inline bool operator <(const node&rhs)const
	{
		if(a!=rhs.a)
			return a<rhs.a;
		if(b!=rhs.b)
			return b<rhs.b;
		return c<rhs.c;
	}
} a[N],b[N];
int n,k;
int c[N*2];
inline void update(int pos,int val)
{
	for(re int i=pos; i<=k; i+=lowbit(i))
		c[i]+=val;
}
inline int query(int pos)
{
	int res=0;
	for(re int i=pos; i; i-=lowbit(i))
		res+=c[i];
	return res;
}
inline void clear(int pos)
{
	for(re int i=pos; i<=k; i+=lowbit(i))
		if(c[i])
			c[i]=0;
		else
			return;
}
inline void cdq(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	re int i=l,j=mid+1;
	int top=l-1;
//	printf("%d %d:\n",l,r);
//	for(re int i=l; i<=r; ++i)
//		printf(" %d %d %d\n",a[i].a,a[i].b,a[i].c);
	while(i<=mid&&j<=r)
	{
		if(a[i].b<a[j].b||(a[i].b==a[j].b&&a[i].c<=a[j].c))
		{
			b[++top]=a[i++];
//			printf(" %d",b[top].c);
			update(b[top].c,b[top].cnt);
		}
		else
		{
			b[++top]=a[j++];
			b[top].sum+=query(b[top].c);
		}
	}
	while(i<=mid)
		b[++top]=a[i++];
	while(j<=r)
	{
		b[++top]=a[j++];
		b[top].sum+=query(b[top].c);
	}
	for(i=l; i<=r; ++i)
	{
		a[i]=b[i];
		clear(a[i].c);
	}
//	putchar('\n');
}
int ans[N];
signed main()
{
	int _n;
	read(_n,k);
	for(re int i=1; i<=_n; ++i)
		read(a[i].a,a[i].b,a[i].c);
	std::sort(a+1,a+1+_n);
	int head=1,tail=0;
	while(head<=_n)
	{
		tail=head+1;
		while(tail<=_n&&a[head].a==a[tail].a&&a[head].b==a[tail].b&&a[head].c==a[tail].c)
			++tail;
		a[++n]=a[head],a[n].cnt=tail-head;
		head=tail;
	}
	cdq(1,n);
	std::sort(a+1,a+1+n);
//	for(re int i=1; i<=n; ++i)
//		printf(" %d %d %d %d %d\n",a[i].a,a[i].b,a[i].c,a[i].cnt,a[i].sum);
	for(re int i=1; i<=n; ++i)
		ans[a[i].sum+a[i].cnt-1]+=a[i].cnt;
	for(re int i=0; i<_n; ++i)
		printf("%d\n",ans[i]);
	return 0;
}


