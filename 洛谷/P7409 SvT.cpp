#include <bits/stdc++.h>
#define int ll
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
const int N=1e6+5;
#define ws wdnmd
int wa[N],wb[N],ws[N],sa[N],rk[N],height[N];
inline bool cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
inline void suffix_array(char *str,int n,int m)
{
	int *x=wa,*y=wb;

	fill(ws+1,ws+1+m,0);
	for(int i=1; i<=n; ++i)
		++ws[x[i]=str[i]-'a'+1];
	for(int i=2; i<=m; ++i)
		ws[i]+=ws[i-1];
	for(int i=n; i>=1; --i)
		sa[ws[x[i]]--]=i;

	for(int p=0,j=1; j<n&&p<=n; j<<=1,m=p)
	{
		p=0;
		for(int i=n; i>=n-j+1; --i)
			y[++p]=i;
		for(int i=1; i<=n; ++i)
			if(sa[i]>j)
				y[++p]=sa[i]-j;

		fill(ws+1,ws+1+m,0);
		for(int i=1; i<=n; ++i)
			++ws[x[i]];
		for(int i=2; i<=m; ++i)
			ws[i]+=ws[i-1];
		for(int i=n; i>=1; --i)
			sa[ws[x[y[i]]]--]=y[i];

		swap(x,y);
		p=0;
		for(int i=1; i<=n; ++i)
			x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?p:++p;
	}

	for(int i=1; i<=n; ++i)
		rk[sa[i]]=i;

	for(int j=0,i=1; i<=n; ++i)
	{
		if(j)
			--j;
		while(str[i+j]==str[sa[rk[i]-1]+j])
			++j;
		height[rk[i]]=j;
	}
}
char str[N];
int f[N][25],Log[N];
int n,m,q,a[N];
inline int query(int l,int r)
{
	int k=Log[r-l+1];
	return min(f[l][k],f[r-(1<<k)+1][k]);
}
int st[N],cnt[N],top;
inline void work()
{
	read(m);
	for(int i=1; i<=m; ++i)
	{
		int x;
		read(x);
		a[i]=rk[x];
	}
	sort(a+1,a+1+m);
	m=(int)(unique(a+1,a+1+m)-a-1);
//	for(int i=1; i<=m; ++i)
//		printf("%d ",a[i]);
//	putchar('\n');
	ll ans=0,now=0;
	top=0;
	for(int i=2; i<=m; ++i)
	{
		int val=query(a[i-1]+1,a[i]);
//		printf(" %d\n",val);
		int sum=1;
		while(top&&st[top]>val)
		{
			now-=(ll)st[top]*cnt[top];
			sum+=cnt[top];
			--top;
		}
		st[++top]=val;
		cnt[top]=sum;
		now+=(ll)val*sum;
		ans+=now;
	}
	printf("%lld\n",ans);
}
signed main()
{
	read(n,q);
	scanf("%s",str+1);
	suffix_array(str,n,26);
	Log[0]=-1;
	for(int i=1; i<=n; ++i)
		Log[i]=Log[i>>1]+1;
	for(int i=1; i<=n; ++i)
		f[i][0]=height[i];
	for(int j=0; j<20; ++j)
		for(int i=1; i+(1<<(j+1))-1<=n; ++i)
			f[i][j+1]=min(f[i][j],f[i+(1<<j)][j]);
	while(q--)
		work();
	return 0;
}


