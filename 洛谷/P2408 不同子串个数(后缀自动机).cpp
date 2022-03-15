#include<cstdio>
#define re register
#define ll long long
using namespace std;
const int N=2e5+10;
struct tree
{
	int ch[26],fa,len;
} point[N];
int las=1,tot=1;
inline void insert(int c)
{
	int p=las,np=las=++tot;
	point[np].len=point[p].len+1;
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
			point[q].fa=point[np].fa=nq;
			point[nq].len=point[p].len+1;
			for(; p&&point[p].ch[c]==q; p=point[p].fa)
				point[p].ch[c]=nq;
		}
	}
}
int n;
char str[N];
ll ans;
int main()
{
	scanf("%d%s",&n,str);
	for(re int i=0; i<n; ++i)
		insert(str[i]-'a');
	for(re int i=2; i<=tot; ++i)
		ans+=point[i].len-point[point[i].fa].len;
	printf("%lld\n",ans);
	return 0;
}
