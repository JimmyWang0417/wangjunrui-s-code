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
const int N=5e4+5;
int n;
int p[N],tot;
struct node
{
	int ans;
	long double cnt;
	node(int _ans=0,long double _cnt=0):ans(_ans),cnt(_cnt) {}
	inline node operator + (const node &rhs)const
	{
		node res=(*this);
		if(res.ans<rhs.ans)
			res=ans;
		else if(res.ans==rhs.ans)
			res.cnt+=rhs.cnt;
		return res;
	}
	inline void operator +=(const node &rhs)
	{
		if(ans<rhs.ans)
			(*this)=rhs;
		else if(ans==rhs.ans)
			cnt+=rhs.cnt;
	}
};
struct Tree_array
{
	node sum[N];
	inline void update(int pos,node val)
	{
//		printf("%d\n",pos);
		for(int i=pos; i<=tot; i+=lowbit(i))
			sum[i]+=val;
	}
	inline node query(int pos)
	{
		node res=0;
		for(int i=pos; i; i-=lowbit(i))
			res+=sum[i];
		return node(res.ans+1,res.cnt);
	}
	inline void clear(int pos)
	{
		for(int i=pos; i<=tot; i+=lowbit(i))
			sum[i]=node();
	}
	inline void clear()
	{
		memset(sum,0,sizeof(sum));
	}
} tree;
struct Point
{
	int tim,h,v;
	node pre,suf;
	inline bool operator <(const Point &rhs)const
	{
		return tim<rhs.tim;
	}
} a[N];
inline void cdq1(int l,int r)
{
	if(l==r)
	{
		a[l].pre+=node(1,1);
		return;
	}
	int mid=(l+r)>>1;
	cdq1(l,mid);
	sort(a+mid+1,a+r+1,[](const Point&rhsa,const Point&rhsb)
	{
		return rhsa.h==rhsb.h?rhsa.v>rhsb.v:rhsa.h>rhsb.h;
	});
	int i=l,j=mid+1;
	while(i<=mid&&j<=r)
	{
		if(a[i].h==a[j].h?(a[i].v>=a[j].v):a[i].h>=a[j].h)
		{
			tree.update(tot-a[i].v+1,a[i].pre);
			++i;
		}
		else
		{
			a[j].pre+=tree.query(tot-a[j].v+1);
			++j;
		}
	}
	while(i<=mid)
	{
		tree.update(tot-a[i].v+1,a[i].pre);
		++i;
	}
	while(j<=r)
	{
		a[j].pre+=tree.query(tot-a[j].v+1);
		++j;
	}
	for(i=l; i<=r; ++i)
		tree.clear(tot-a[i].v+1);
	sort(a+mid+1,a+r+1,[](const Point&rhsa,const Point&rhsb)
	{
		return rhsa.tim<rhsb.tim;
	});
	cdq1(mid+1,r);
	sort(a+l,a+r+1,[](const Point&rhsa,const Point&rhsb)
	{
		return rhsa.h==rhsb.h?rhsa.v>rhsb.v:rhsa.h>rhsb.h;
	});
//	printf("%d %d\n",l,r);
}
inline void cdq2(int l,int r)
{
	if(l==r)
	{
		a[l].suf+=node(1,1);
//		printf(" %d %lld\n",a[l].suf.ans,a[l].suf.cnt);
		return;
	}
	int mid=(l+r)>>1;
	cdq2(l,mid);
	sort(a+mid+1,a+r+1,[](const Point&rhsa,const Point&rhsb)
	{
		return rhsa.h==rhsb.h?rhsa.v<rhsb.v:rhsa.h<rhsb.h;
	});
	int i=l,j=mid+1;
//	printf("%d %d\n",l,r);
	while(i<=mid&&j<=r)
	{
		if(a[i].h==a[j].h?(a[i].v<=a[j].v):a[i].h<=a[j].h)
		{
			tree.update(a[i].v,a[i].suf);
			++i;
		}
		else
		{
			a[j].suf+=tree.query(a[j].v);
			++j;
		}
//		printf(" %d %d\n",i,j);
	}
	while(i<=mid)
	{
		tree.update(a[i].v,a[i].suf);
		++i;
	}
	while(j<=r)
	{
		a[j].suf+=tree.query(a[j].v);
		++j;
	}
	for(i=l; i<=r; ++i)
		tree.clear(a[i].v);
	sort(a+mid+1,a+r+1,[](const Point&rhsa,const Point&rhsb)
	{
		return rhsa.tim>rhsb.tim;
	});
	cdq2(mid+1,r);
	sort(a+l,a+r+1,[](const Point&rhsa,const Point&rhsb)
	{
		return rhsa.h==rhsb.h?rhsa.v<rhsb.v:rhsa.h<rhsb.h;
	});
}
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
	{
		a[i].tim=i;
		read(a[i].h,a[i].v);
		p[i]=a[i].v;
	}

	sort(p+1,p+1+n);
	tot=(int)(unique(p+1,p+1+n)-p-1);
	for(int i=1; i<=n; ++i)
		a[i].v=(int)(lower_bound(p+1,p+1+tot,a[i].v)-p);

	cdq1(1,n);
	node ans;
	for(int i=1; i<=n; ++i)
		ans+=a[i].pre;
	sort(a+1,a+n+1,[](const Point&rhsa,const Point&rhsb)
	{
		return rhsa.tim>rhsb.tim;
	});
	cdq2(1,n);
	sort(a+1,a+n+1,[](const Point&rhsa,const Point&rhsb)
	{
		return rhsa.tim<rhsb.tim;
	});
	printf("%d\n",ans.ans);
	for(int i=1; i<=n; ++i)
		if(ans.ans+1==a[i].pre.ans+a[i].suf.ans)
			printf("%.5LF ",a[i].pre.cnt*a[i].suf.cnt/ans.cnt);
		else
			printf("0.00000 ");
//	for(int i=1; i<=n; ++i)
//		printf("%d %lld %d %lld\n",a[i].pre.ans,a[i].pre.cnt,a[i].suf.ans,a[i].suf.cnt);
	return 0;
}

