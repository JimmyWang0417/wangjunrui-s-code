#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring> 
#define re register
#define ll long long
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int maxn=1005,base=2333;
int head[maxn],num_edge,n,m;
struct Edge
{
	int next,to;
} edge[maxn<<1];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
ll ans[maxn][maxn];
inline ll HASH(int u,int f)
{
	int top=0;
	ll ans=maxn;
	vector<ll>q;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==f)
			continue;
		q.push_back(HASH(v,u));
	}
	sort(q.begin(),q.end());
	for(re int i=0; i<q.size(); ++i)
		ans=ans*base+q[i];
	return ans*base+maxn+1;
}
int main()
{
	read(m);
	for(int i=1; i<=m; ++i)
	{
		num_edge=0;
		memset(head,0,sizeof(head));
		static int n;
		read(n);
		for (int j=1; j<=n; ++j)
		{
			static int x;
			read(x);
			if (x)
				add_edge(x,j),add_edge(j,x);
		}
		for (int j=1; j<=n; ++j)
			ans[i][j]=HASH(j,0);//树哈希
		sort(ans[i]+1,ans[i]+n+1);
		for (int j=1,k=0; j<=i; ++j)
		{
			while (k<=n)
				if (ans[i][++k]!=ans[j][k]) break;//找同构
			if (k>n)
			{
				printf("%d\n",j);
				break;
			}//找到同构就输出
		}
	}
}
