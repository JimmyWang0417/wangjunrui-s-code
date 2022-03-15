#include<cstdio>
#include<cstring>
#define re register
#define ll long long
using namespace std;
const int N=1e6+5;
struct node
{
	int len,fa,ch[26];
} point[N];
int las,tot,f[N],w[N];
inline void insert(int c)
{
	int p=las,np=las=++tot;
	point[np].len=point[p].len+1;
	f[np]=w[np]=1;
	for(; p&&!point[p].ch[c]; p=point[p].fa)
		point[p].ch[c]=np;
	if(!p)
		point[np].fa=1;
	else
	{
		int q=point[p].ch[c];
		if(point[q].len==point[p].len+1)
			point[np].fa=q;
		else
		{
			int nq=++tot;
			point[nq]=point[q];
			point[np].fa=point[q].fa=nq;
			point[nq].len=point[p].len+1;
			for(; p&&q==point[p].ch[c]; p=point[p].fa)
				point[p].ch[c]=nq;
		}
	}
}
int ws[N],idx[N],n;
inline void getsort()
{
	for(re int i=1; i<=tot; ++i)
		++ws[point[i].len];
	for(re int i=1; i<=n; ++i)
		ws[i]+=ws[i-1];
	for(re int i=1; i<=tot; ++i)
		idx[ws[point[i].len]--]=i;
}
inline ll solve()
{
	ll ans=0;
	for(re int i=tot; i>=1; --i)
		f[point[idx[i]].fa]+=f[idx[i]];
	for(re int i=tot; i>=1; --i)
	{
		int &x=idx[i];
		ans+=1ll*f[x]*w[point[x].fa]*point[point[x].fa].len;
		w[point[x].fa]+=f[x];
	}
	return ans;
}
char str[N];
int main()
{
	las=tot=1;
	scanf("%s",str);
	n=strlen(str);
	for(re int i=n-1; i>=0; --i)
		insert(str[i]-'a');
	ll ans=1ll*(n+1)*n*(n-1)>>1;
	getsort();
//	printf("%lld %lld\n",ans,extra);
	printf("%lld\n",ans-(solve()<<1));
}
