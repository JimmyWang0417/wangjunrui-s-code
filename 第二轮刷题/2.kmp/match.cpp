#include<stack>
#include<cstdio>
#include<cstring>
#define re register
using namespace std;
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
const int N=500005,S=10005;
int idx1[N],idx2[N],idx3[N],nxt[N],pre[S],n,m,s,str[N],a[N],ans[N];
stack<int>st[S];
int main()
{
//	freopen("test.in","r",stdin);
	read(n),read(m),read(s);
	for(re int i=0; i<n; ++i)
		read(str[i]);
	for(re int i=0; i<m; ++i)
		read(a[i]);
	for(re int i=0; i<m; ++i)
	{
		idx1[i]=st[a[i]].empty()?-1:i-st[a[i]].top();
		st[a[i]].push((int)i);
	}
	for(re int i=1,now=-1; i<=s; ++i)
		if(!st[i].empty())
		{
			pre[i]=now;
			nxt[i]=-1;
			if(now!=-1)
				nxt[now]=i;
			now=i;
		}
	for(re int i=m-1; i>=0; --i)
	{
		idx2[i]=pre[a[i]]==-1?-1:i-st[pre[a[i]]].top();
		idx3[i]=nxt[a[i]]==-1?-1:i-st[nxt[a[i]]].top();
		st[a[i]].pop();
		if(st[a[i]].empty())
		{
			if(pre[a[i]]!=-1)
				nxt[pre[a[i]]]=nxt[a[i]];
			if(nxt[a[i]]!=-1)
				pre[nxt[a[i]]]=pre[a[i]];
		}
	}
	memset(nxt,0,sizeof(nxt));
//	for(re int i=0; i<=m-1; ++i)
//		printf("%d %d %d\n",idx1[i],idx2[i],idx3[i]);
	nxt[0]=-1;
	
	for(re int i=0,j=-1;i<m;)
	{
		if(j==-1||((idx1[j]==-1||a[i-idx1[j]]==a[i])&&(idx2[j]==-1||a[i-idx2[j]]<a[i])&&(idx3[j]==-1||a[i-idx3[j]]>a[i])))
			nxt[++i]=++j;
		else
			j=nxt[j];
	}
//	for(re int i=0; i<m; ++i)
//		printf("%d ",nxt[i]);
//	printf("\n");
	for(re int i=0,j=0;i<n;)
	{
		if(j==-1||((idx1[j]==-1||str[i-idx1[j]]==str[i])&&(idx2[j]==-1||str[i-idx2[j]]<str[i])&&(idx3[j]==-1||str[i-idx3[j]]>str[i])))
		{
			++i;
			++j;
		}
		else
			j=nxt[j];
		if(j==m)
		{
			ans[++ans[0]]=i-m+1;
			j=nxt[j];
		}
	}
	printf("%d\n",ans[0]);
	for(re int i=1; i<=ans[0]; ++i)
		printf("%d\n",ans[i]);;
	return 0;
}
