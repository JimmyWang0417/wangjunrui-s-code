#include <bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
using std::swap;
const int N=1e5+5;
int ws[N],wa[N],wb[N],id[N];
inline bool cmp(int *r,int a,int b,int len)
{
	return r[a]==r[b]&&r[a+len]==r[b+len];
}
inline void da(int *r,int *sa,int n,int m)
{
	int p,*x=wa,*y=wb;
	for(re int i=0; i<m; ++i)
		ws[i]=0;
	for(re int i=0; i<n; ++i)
		++ws[x[i]=r[i]];
	for(re int i=1; i<m; ++i)
		ws[i]+=ws[i-1];
	for(re int i=n-1; i>=0; --i)
		sa[--ws[x[i]]]=i;
	for(re int j=1; j<=n; j<<=1)
	{
		p=0;
		for(re int i=n-j; i<n; ++i)
			y[p++]=i;
		for(re int i=0; i<n; ++i)
			if(sa[i]>=j)
				y[p++]=sa[i]-j;
		for(re int i=0; i<m; ++i)
			ws[i]=0;
		for(re int i=0; i<n; ++i)
			++ws[x[y[i]]];
		for(re int i=1; i<m; ++i)
			ws[i]+=ws[i-1];
		for(re int i=n-1; i>=0; --i)
			sa[--ws[x[y[i]]]]=y[i];
		swap(x,y),m=1,x[sa[0]]=0;
		for(re int i=1; i<n; ++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?m-1:m++;
		if(m>=n)
			break;
	}
}
int rk[N],height[N];
inline void calheight(int *r,int *sa,int n)
{
	int h=0;
	for(re int i=1; i<=n; ++i)
		rk[sa[i]]=i;
	for(re int i=0; i<n; height[rk[i++]]=h)
	{
		if(h)
			--h;
		for(re int j=sa[rk[i]-1]; r[i+h]==r[j+h]; ++h);
	}
}
int sa[N],r[N];
char str1[N],str2[N];
inline void work()
{
	memset(wa,0,sizeof(wa));
	memset(wb,0,sizeof(wb));
	memset(id,0,sizeof(id));
	memset(sa,0,sizeof(sa));
	memset(rk,0,sizeof(rk));
	memset(height,0,sizeof(height));
	memset(r,0,sizeof(r));
	int len=0;
	for(re int i=0; str1[i]; ++i)
	{
		id[len]=1;
		r[len++]=str1[i];
	}
	id[len]=0;
	r[len++]=1;
	for(re int i=0; str2[i]; ++i)
	{
		id[len]=2;
		r[len++]=str2[i];
	}
	r[len]=0;
	id[len]=0;
	da(r,sa,len,200);
	calheight(r,sa,len-1);
//	for(re int i=0; i<len; ++i)
//		printf("%d ",sa[i]);
//	putchar('\n');
	int maxlen=0;
	for(re int i=1; i<len; ++i)
		if(id[sa[i-1]]+id[sa[i]]==3)
		{
			if(height[i]>maxlen)
				maxlen=height[i];
		}
	if(!maxlen)
	{
		printf("No common sequence.\n");
		return;
	}
	std::set<int>se;
	std::vector<int>ans;
	height[len]=0;
	for(re int i=1; i<=len; ++i)
	{
		if(height[i]>=maxlen)
		{
			se.insert(id[sa[i]]);
			se.insert(id[sa[i-1]]);
		}
		else
		{
			if(se.size()==2)
				ans.push_back(sa[i-1]);
			se.clear();
		}
//		printf("%d %d %d %d %d\n",sa[i-1],sa[i],id[sa[i-1]],id[sa[i]],height[i]);
	}
	for(auto now:ans)
	{
//		printf("%d\n",now);
		for(re int i=now; i<now+maxlen; ++i)
			putchar(r[i]);
		putchar('\n');
	}
}
signed main()
{
	int kase=0;
	while(scanf("%s%s",str1,str2)!=EOF)
	{
		if(kase++)
			putchar('\n');
		work();
	}
	return 0;
}


