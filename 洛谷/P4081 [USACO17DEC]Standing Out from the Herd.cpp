#include <cstdio>
#include <cstring>
#define re register
#define ll long long
using namespace std;
const int N=2e5+5;
struct Tree
{
	int size,id;
	int fa,len;
	int ch[26];
} point[N];
int tot=1,las;
inline void insert(int c,int id)
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
	for(; np&&point[np].id!=id; np=point[np].fa)
	{
		point[np].id=id;
		++point[np].size;
	}
}
char str[N>>1];
int ans[N],n;
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str);
		las=1;
		for(re int j=0; str[j]; ++j)
			insert(str[j]-'a',i);
	}
	for(re int i=2; i<=tot; ++i)
	{
		if(point[i].size>=2)
			continue;
		ans[point[i].id]+=point[i].len-point[point[i].fa].len;
	}
	for(re int i=1; i<=n; ++i)
		printf("%d\n",ans[i]);
	return 0;
}
