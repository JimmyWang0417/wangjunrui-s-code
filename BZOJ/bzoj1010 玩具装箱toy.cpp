#include<cstdio>
#include<cstring>
#define re register
#define ll long long
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
int n,L,c[N],l[N],sta[N],r;
ll sum[N],f[N];
inline ll calc(int j,int i)
{
	ll x=i-j-1+sum[i]-sum[j];
	return f[j]+(x-L)*(x-L);
}
inline int find_val(int x)
{
	int left=1,right=r,mid;
	while(left<=right)
	{
		mid=(left+right)>>1;
		if(l[sta[mid]]==x)
			return mid;
		else if(l[sta[mid]]<x)
			left=mid+1;
		else
			right=mid-1;
	}
	return right;
}
int main()
{
	read(n);
	read(L);
	for(re int i=1; i<=n; ++i)
	{
		read(c[i]);
		sum[i]=sum[i-1]+c[i];
		l[i]=n+1;
	}
	memset(sta,0x3f3f3f3f,sizeof(sta));
	sta[1]=0;
	r=1;
	for(re int i=1; i<=n; ++i)
	{
		f[i]=calc(sta[find_val(i)],i);
		while(r&&l[sta[r]]>i&&calc(i,l[sta[r]])<calc(sta[r],l[sta[r]]))
			--r;
		if(!r)
		{
			sta[++r]=i;
			l[i]=i;
			continue;
		}
		int left=l[sta[r]],right=n,mid;
		while(left<=right)
		{
			mid=(left+right)>>1;
			if(calc(i,mid)<=calc(sta[r],mid))
				right=mid-1;
			else
				left=mid+1;
		}
		if(calc(i,left)<=calc(sta[r],left))
		{
			sta[++r]=i;
			l[i]=left;
		}
	}
	printf("%lld\n",f[n]);
	return 0;
}
