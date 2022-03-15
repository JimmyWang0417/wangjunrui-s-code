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
const int N=1e6+5;
int belong[N],block;
int cnt[N],tag[N];
inline void add(int val)
{
	--tag[cnt[val]];
	++tag[++cnt[val]];
}
inline void del(int val)
{
	--tag[cnt[val]];
	++tag[--cnt[val]];
}
int n,m;
struct Query
{
	int l,r,t,id;
	inline bool operator < (const Query &rhs)const
	{
		return belong[l]==belong[rhs.l]?(belong[r]==belong[rhs.r]?t<rhs.t:r<rhs.r):l<rhs.l;
	}
} q[N];
struct Change
{
	int pos,val;
} c[N];
int a[N];
int p[N],tot;
int answer[N];
signed main()
{
	read(n,m);

	block=(int)pow(n,2.0/3.0);
	for(int i=1; i<=n; ++i)
		belong[i]=(i-1)/block+1;

	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[++tot]=a[i];
	}
	int ccnt=0,qcnt=0;
	for(int i=1; i<=m; ++i)
	{
		int opt;
		read(opt);
		if(opt==1)
		{
			++qcnt;
			read(q[qcnt].l,q[qcnt].r);
			q[qcnt].t=ccnt;
			q[qcnt].id=qcnt;
		}
		else
		{
			++ccnt;
			read(c[ccnt].pos,c[ccnt].val);
			p[++tot]=c[ccnt].val;
		}
	}

	sort(p+1,p+1+tot);
	tot=(int)(unique(p+1,p+1+tot)-p-1);
	for(int i=1; i<=n; ++i)
		a[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
	for(int i=1; i<=ccnt; ++i)
		c[i].val=(int)(lower_bound(p+1,p+1+tot,c[i].val)-p);


	sort(q+1,q+1+qcnt);
	int l=1,r=0,t=0;
	for(int i=1; i<=qcnt; ++i)
	{
		const int ql=q[i].l,qr=q[i].r,qt=q[i].t;

		while(ql>l)
			del(a[l++]);
		while(qr>r)
			add(a[++r]);
		while(ql<l)
			add(a[--l]);
		while(qr<r)
			del(a[r--]);

		while(qt>t)
		{
			++t;
			if(l<=c[t].pos&&c[t].pos<=r)
			{
				del(a[c[t].pos]);
				add(c[t].val);
			}
			swap(a[c[t].pos],c[t].val);
		}
		while(qt<t)
		{
			if(l<=c[t].pos&&c[t].pos<=r)
			{
				del(a[c[t].pos]);
				add(c[t].val);
			}
			swap(a[c[t].pos],c[t].val);
			--t;
		}
		for(int &ans=answer[q[i].id]=1; tag[ans]; ++ans);
	}
	for(int i=1; i<=qcnt; ++i)
		printf("%d\n",answer[i]);
	return 0;
}


