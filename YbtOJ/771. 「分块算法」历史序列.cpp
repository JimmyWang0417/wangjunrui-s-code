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
int n,m;
int pos[N];
int num,block,belong[N],L[N],R[N];
int cnt[N],cntblock[N];
ll a[N],addblock[N];
vector<int>op[N];
inline bool cmp(int x,int y)
{
	return a[x]<a[y];
}
inline void pushdown(int x)
{
	int l=L[x],r=R[x],len=(int)op[x].size(),cs=cntblock[x]+len,j=0;
	if(!len)
	{
		for(int i=l; i<=r; ++i)
		{
			a[i]+=addblock[x];
			cnt[i]+=cntblock[x];
		}
		addblock[x]=cntblock[x]=0;
	}
	else
	{
		for(int i=l; i<=r; ++i)
		{
			int k=pos[i];
			while(j<len&&a[k]>=op[x][j])
			{
				++j;
				--cs;
			}
			cnt[k]+=cs;
			if(j!=len)
				a[k]=op[x].back();
		}
		op[x].clear();
		cntblock[x]=0;
		for(int i=l; i<=r; ++i)
			a[i]+=addblock[x];
		addblock[x]=0;
	}
}
int q1[N],q2[N];
inline void addsort(int l,int r,int val)
{
	int bel=belong[l];
	pushdown(bel);
	int qm1=0,qm2=0;
	for(int i=L[bel]; i<=R[bel]; ++i)
	{
		if(l<=pos[i]&&pos[i]<=r)
			q1[++qm1]=pos[i];
		else
			q2[++qm2]=pos[i];
	}
	for(int i=1; i<=qm1; ++i)
	{
		a[q1[i]]+=val;
		++cnt[q1[i]];
	}
	int now=L[bel]-1;
	int i=1,j=1;
	while(i<=qm1&&j<=qm2)
	{
		if(a[q1[i]]<a[q2[j]])
			pos[++now]=q1[i++];
		else
			pos[++now]=q2[j++];
	}
	while(i<=qm1)
		pos[++now]=q1[i++];
	while(j<=qm2)
		pos[++now]=q2[j++];
}
inline void change(int l,int r,int val)
{
	if(belong[l]==belong[r])
		addsort(l,r,val);
	else
	{
		addsort(l,R[belong[l]],val);
		addsort(L[belong[r]],r,val);
		for(int i=belong[l]+1; i<belong[r]; ++i)
		{
			addblock[i]+=val;
			++cntblock[i];
		}
	}
}
inline void coversort(int l,int r,int val)
{
	int bel=belong[l];
	pushdown(bel);
	int qm1=0,qm2=0;
	for(int i=L[bel]; i<=R[bel]; ++i)
	{
		if(l<=pos[i]&&pos[i]<=r&&a[pos[i]]<val)
			q1[++qm1]=pos[i];
		else
			q2[++qm2]=pos[i];
	}
	for(int i=1; i<=qm1; ++i)
	{
		a[q1[i]]=val;
		++cnt[q1[i]];
	}
	int now=L[bel]-1;
	int i=1,j=1;
	while(i<=qm1&&j<=qm2)
	{
		if(a[q1[i]]<a[q2[j]])
			pos[++now]=q1[i++];
		else
			pos[++now]=q2[j++];
	}
	while(i<=qm1)
		pos[++now]=q1[i++];
	while(j<=qm2)
		pos[++now]=q2[j++];
}
inline void update(int l,int r,int val)
{
	if(belong[l]==belong[r])
		coversort(l,r,val);
	else
	{
		coversort(l,R[belong[l]],val);
		coversort(L[belong[r]],r,val);
		for(int i=belong[l]+1; i<belong[r]; ++i)
		{
			if(op[i].empty()||val-addblock[i]>op[i].back())
				op[i].push_back(val-addblock[i]);
		}
	}
}
signed main()
{
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		pos[i]=i;
	}
	block=(int)sqrt(n);
	num=n/block+(n%block!=0);
	for(int i=1; i<=num; ++i)
	{
		L[i]=R[i-1]+1;
		R[i]=min(R[i-1]+block,n);
		for(int j=L[i]; j<=R[i]; ++j)
			belong[j]=i;
		sort(pos+L[i],pos+R[i]+1,cmp);
	}
	read(m);
	for(int i=1; i<=m; ++i)
	{
		char opt[2];
		scanf("%s",opt);
		if(opt[0]=='A')
		{
			int l,r,c;
			read(l,r,c);
			if(c==0)
				continue;
			change(l,r,c);
		}
		else if(opt[0]=='M')
		{
			int l,r,c;
			read(l,r,c);
			update(l,r,c);
		}
		else
		{
			int k;
			read(k);
			pushdown(belong[k]);
			printf("%lld %d\n",a[k],cnt[k]);
		}
	}
	return 0;
}

