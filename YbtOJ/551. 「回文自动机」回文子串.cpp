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
int n,k;
char str[N];
struct Tree
{
	int fa,len,ch[26];
	int pos;
} point[N];
int las=1,cnt=1;
inline int getfa(int x)
{
	while(str[n]!=str[n-point[x].len-1])
		x=point[x].fa;
	return x;
}
inline void insert(int c,int id)
{
	int cur=getfa(las);
	int now=point[cur].ch[c];
	if(!now)
	{
		now=++cnt;
		point[now].fa=point[getfa(point[cur].fa)].ch[c];
		point[now].len=point[cur].len+2;
		point[now].pos=id-point[now].len+1;
		point[cur].ch[c]=now;
	}
	las=now;
}
#define ws nmsl
#define rank Rank
int wa[N],wb[N],ws[N],sa[N],height[N],rank[N];
inline bool cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
inline void da(int *sa,int n,int m)
{
	int *x=wa,*y=wb;
	int i,j,p;
	for(i=1; i<=m; ++i)
		ws[i]=0;
	for(i=1; i<=n; ++i)
		++ws[x[i]=str[i]-'a'+1];
	for(i=2; i<=m; ++i)
		ws[i]+=ws[i-1];
	for(i=n; i>=1; --i)
		sa[ws[x[i]]--]=i;
	for(j=1,p=1; j<n&&p<=n; j<<=1,m=p)
	{
		for(p=0,i=n-j+1; i<=n; ++i)
			y[++p]=i;
		for(i=1; i<=n; ++i)
			if(sa[i]>j)
				y[++p]=sa[i]-j;
		for(i=1; i<=m; ++i)
			ws[i]=0;
		for(i=1; i<=n; ++i)
			++ws[x[i]];
		for(i=2; i<=m; ++i)
			ws[i]+=ws[i-1];
		for(i=n; i>=1; --i)
			sa[ws[x[y[i]]]--]=y[i];
		for(swap(x,y),i=1,p=0; i<=n; ++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p:++p;
//		for(int i=1; i<=n; ++i)
//			printf("%d ",x[i]);
//		putchar('\n');
	}
	for(int i=1; i<=n; ++i)
		rank[sa[i]]=i;
}
inline bool comp(int a,int b)
{
	return point[a].len==point[b].len?rank[point[a].pos]<rank[point[b].pos]:point[a].len<point[b].len;
}
int pos[N];
signed main()
{
	freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);
	read(n,k);
	scanf("%s",str+1);
	point[0].fa=1,point[0].len=0;
	point[1].fa=0,point[1].len=-1;
	for(n=1; str[n]; ++n)
		insert(str[n]-'a',n);
	printf("%d\n",cnt-1);
	--n;
	k=k%(cnt-1)+1;
	da(sa,n,30);
	int m=0;
	for(int i=2; i<=cnt; ++i)
		pos[++m]=i;
	sort(pos+1,pos+1+m,comp);
	for(int i=point[pos[k]].pos; i<point[pos[k]].pos+point[pos[k]].len; ++i)
		putchar(str[i]);
	putchar('\n');
	return 0;
}
