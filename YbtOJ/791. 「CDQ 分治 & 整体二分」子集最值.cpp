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
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=1e5+5;
struct node
{
	int a,b,c;
	int sum;
} a[N],b[N];
int n;
int C[N];
inline void update(int pos,int val=1)
{
	for(int i=pos; i<=n; i+=lowbit(i))
		C[i]+=val;
}
inline int query(int pos)
{
	int res=0;
	for(int i=pos; i; i-=lowbit(i))
		res+=C[i];
	return res;
}
inline void clear(int pos)
{
	for(int i=pos; i<=n; i+=lowbit(i))
		C[i]=0;
}
ll ans;




inline bool cmp1(node rhsx,node rhsy)
{
	return rhsx.a>rhsy.a;
}
inline void cdq1(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	cdq1(l,mid),cdq1(mid+1,r);
	int i=l,j=mid+1;
	int tot=l-1;
	while(i<=mid&&j<=r)
	{
		if(a[i].b<a[j].b)
		{
			b[++tot]=a[i];
			update(a[i].c);
			++i;
		}
		else
		{
			b[++tot]=a[j];
			ans+=query(a[j].c);
			++j;
		}
	}
	while(i<=mid)
	{
		b[++tot]=a[i];
		++i;
	}
	while(j<=r)
	{
		b[++tot]=a[j];
		ans+=query(a[j].c);
		++j;
	}
	for(i=l; i<=r; ++i)
	{
		a[i]=b[i];
		clear(a[i].c);
	}
}




inline bool cmp2(node rhsx,node rhsy)
{
	return rhsx.b>rhsy.b;
}
inline void cdq2(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	cdq2(l,mid),cdq2(mid+1,r);
	int i=l,j=mid+1;
	int tot=l-1;
	while(i<=mid&&j<=r)
	{
		if(a[i].a<a[j].a)
		{
			b[++tot]=a[i];
			update(a[i].c);
			++i;
		}
		else
		{
			b[++tot]=a[j];
			ans+=query(a[j].c);
			++j;
		}
	}
	while(i<=mid)
	{
		b[++tot]=a[i];
		++i;
	}
	while(j<=r)
	{
		b[++tot]=a[j];
		ans+=query(a[j].c);
		++j;
	}
	for(i=l; i<=r; ++i)
	{
		a[i]=b[i];
		clear(a[i].c);
	}
}



inline bool cmp3(node rhsx,node rhsy)
{
	return rhsx.c>rhsy.c;
}
inline void cdq3(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	cdq3(l,mid),cdq3(mid+1,r);
	int i=l,j=mid+1;
	int tot=l-1;
	while(i<=mid&&j<=r)
	{
		if(a[i].a<a[j].a)
		{
			b[++tot]=a[i];
			update(a[i].b);
			++i;
		}
		else
		{
			b[++tot]=a[j];
			ans+=query(a[j].b);
			++j;
		}
	}
	while(i<=mid)
	{
		b[++tot]=a[i];
		++i;
	}
	while(j<=r)
	{
		b[++tot]=a[j];
		ans+=query(a[j].b);
		++j;
	}
	for(i=l; i<=r; ++i)
	{
		a[i]=b[i];
		clear(a[i].b);
	}
}

inline bool cmp4(node rhsx,node rhsy)
{
	return rhsx.b<rhsy.b;
}
inline bool cmp5(node rhsx,node rhsy)
{
	return rhsx.a<rhsy.a;
}
inline void cdq4(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	cdq4(l,mid),cdq4(mid+1,r);
	int i=l,j=mid+1;
	int tot=l-1;
	while(i<=mid&&j<=r)
	{
		if(a[i].b<a[j].b)
		{
			b[++tot]=a[i];
			update(a[i].c);
			++i;
		}
		else
		{
			b[++tot]=a[j];
			b[tot].sum+=query(a[j].c);
			++j;
		}
	}
	while(i<=mid)
	{
		b[++tot]=a[i];
		++i;
	}
	while(j<=r)
	{
		b[++tot]=a[j];
		b[tot].sum+=query(a[j].c);
		++j;
	}
	for(i=l; i<=r; ++i)
	{
		a[i]=b[i];
		clear(a[i].c);
	}
}

signed main()
{
	freopen("subset.in","r",stdin);
	freopen("subset.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i].a);
	for(int i=1; i<=n; ++i)
		read(a[i].b);
	for(int i=1; i<=n; ++i)
		read(a[i].c);
	ll sum=n;


	sort(a+1,a+1+n,cmp1);
	ans=0;
	cdq1(1,n);
	sum+=ans;

	sort(a+1,a+1+n,cmp2);
	ans=0;
	cdq2(1,n);
	sum+=ans;

	sort(a+1,a+1+n,cmp3);
	ans=0;
	cdq3(1,n);
	sum+=ans;

	sum+=((ll)n*(n-1)*(n-2)/6);
	sort(a+1,a+1+n,cmp4);
	for(int i=1; i<=n; ++i)
	{
		int cnt=query(a[i].c-1);
		sum-=(ll)cnt*(cnt-1)/2;
		update(a[i].c,1);
	}
	for(int i=1; i<=n; ++i)
		clear(i);

	sort(a+1,a+1+n,cmp5);
	for(int i=1; i<=n; ++i)
	{
		int cnt=query(a[i].b-1);
		sum-=(ll)cnt*(cnt-1)/2;
		update(a[i].b,1);
	}
	for(int i=1; i<=n; ++i)
		clear(i);
	for(int i=1; i<=n; ++i)
	{
		int cnt=query(a[i].c-1);
		sum-=(ll)cnt*(cnt-1)/2;
		update(a[i].c,1);
	}
	for(int i=1; i<=n; ++i)
		clear(i);
	cdq4(1,n);
	for(int i=1; i<=n; ++i)
		sum+=(ll)a[i].sum*(a[i].sum-1);

	printf("%lld\n",sum);
	return 0;
}


