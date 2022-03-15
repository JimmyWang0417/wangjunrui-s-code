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
inline void clear(T*a,int l,int r,int val)
{
    memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1e6+5,M=1e6+5;
struct Edge
{
    int next,to;
} edge[M];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
    edge[++num_edge].next=head[from];
    edge[num_edge].to=to;
    head[from]=num_edge;
}
using std::min;
int dfn[N],low[N],belong[N],dfstime;
int color;
int st[N],top;
inline void tarjan(int u)
{
    dfn[u]=low[u]=++dfstime;
    st[++top]=u;
    for(re int i=head[u]; i; i=edge[i].next)
    {
        int &v=edge[i].to;
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!belong[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u])
    {
        belong[u]=++color;
        while(st[top]!=u)
            belong[st[top--]]=color;
        --top;
    }
}
int n,m;
inline void work()
{
	memset(dfn,0,sizeof(dfn));
    memset(belong,0,sizeof(belong));
    memset(head,dfstime=color=top=num_edge=0,sizeof(head));
    for(re int i=1; i<=m; ++i)
    {
        int x,y,a,b;
        read(x,y,a,b);
        ++x,++y;
        add_edge(x+a*n,y+(b^1)*n);
        add_edge(y+b*n,x+(a^1)*n);
    }
    for(re int i=1; i<=2*n; ++i)
        if(!dfn[i])
            tarjan(i);
    for(re int i=1; i<=n; ++i)
        if(belong[i]==belong[i+n])
        {
            printf("NO\n");
            return;
        }
    printf("YES\n");
}
signed main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
        work();
    return 0;
}

