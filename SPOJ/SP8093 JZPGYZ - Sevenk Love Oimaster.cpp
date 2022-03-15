#include <cstdio>
#include <cassert>
#define re register
using namespace std;
template <typename T>
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

const int N=100000*2+5;
struct Edge
{
	int ch[200];
	int fa,len;
	int id,size;
} point[N];
int las,tot=1;
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
			point[np].fa=point[q].fa=nq;
			point[nq].len=point[p].len+1;
			for(; p&&q==point[p].ch[c]; p=point[p].fa)
				point[p].ch[c]=nq;
		}
	}
//	assert(point[np].id!=id);
//	printf("%d\n",id);
	for(; np&&point[np].id!=id; np=point[np].fa)
	{
		++point[np].size;
		point[np].id=id;
	}
}
int n,m;
char str[N];
int main()
{
	read(n),read(m);
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str);
		las=1;
		for(re int j=0; str[j]; ++j)
			insert(str[j],i);
	}
//	printf("%d\n",tot);
	while(m--)
	{
		scanf("%s",str);
		int now=1;
		for(re int j=0; str[j]; ++j)
			now=point[now].ch[str[j]];
		printf("%d\n",point[now].size);
	}
	return 0;
}
