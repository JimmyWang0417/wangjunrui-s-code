#include<cstdio>
#include<cstring>
#include<algorithm>
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
}
const int N=5e4+5;
int n;
int sta[N],l[N],top;
struct node
{
	int l,w;
	inline bool operator < (const node &rhs)const
	{
		return l>rhs.l||l==rhs.l&&w>rhs.w;
	}
} a[N];
ll f[N];
inline ll calc(int i,int j)
{
	return f[i]+1ll*a[i+1].l*a[j].w;
}
inline int find(int x)
{
	int left=1,right=top,mid;
	while(left<=right)
	{
		mid=(left+right)>>1;
		if(l[sta[mid]]==x)
			return mid;
		if(l[sta[mid]]<x)
			left=mid+1;
		else
			right=mid-1;
	}
	return right;
}
signed main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i].l);
		read(a[i].w);
	}
	stable_sort(a+1,a+1+n);
	int maxv=0,size=0;
	for(re int i=1; i<=n; ++i)
		if(a[i].w>maxv)
		{
			maxv=a[i].w;
			a[++size]=a[i];
		}
	for(re int i=1; i<=n; ++i)
		l[i]=n+1;
	memset(sta,0x3f,sizeof(sta));
	sta[top=1]=0;
	l[0]=1;
	for(re int i=1; i<=size; ++i)
	{
		f[i]=calc(sta[find(i)],i);
		while(top&&l[sta[top]]&&calc(i,l[sta[top]])<calc(sta[top],l[sta[top]]))
			--top;
		if(!top)
		{
			sta[++top]=i;
			l[i]=i;
			continue;
		}
		int left=l[sta[top]],right=size,mid;
		while(left<=right)
		{
			int mid=(left+right)>>1;
			if(calc(i,mid)>calc(sta[top],mid))
				left=mid+1;
			else
				right=mid-1;
		}
		if(calc(i,left)>calc(sta[top],left))
			continue;
		sta[++top]=i;
		l[i]=left;
	}
	printf("%lld\n",f[size]);
	return 0;
}
