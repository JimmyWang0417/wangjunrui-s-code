#include<cstdio>
#include<vector>
#include<algorithm>
#define re register
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
const int N=20010,M=200010;
struct node
{
	int x,y,z;
} a[M];
int n,m,l,r,mid,ans;
int vis[N];
vector<int>e[N];
inline bool dfs(int x,int color)
{
	vis[x]=color;
	for(re int i=0,y; i<e[x].size(); i++)
	{
		y=e[x][i];
		if(vis[y]==color)
			return false;
		if(!vis[y]&&!dfs(y,3-color))
			return false;
	}
	return true;
}
inline bool check(int now)
{
	for(re int i=1; i<=n; i++)
		e[i].clear();
	for(re int i=1; i<=m; i++)
	{
		if(a[i].z<=now)
			break;
		e[a[i].x].push_back(a[i].y);
		e[a[i].y].push_back(a[i].x);
	}
	fill(vis+1,vis+1+n,0);
	for(re int i=1; i<=n; i++)
		if(!vis[i]&&!dfs(i,1))
			return false;
	return true;
}
inline bool cmp(node a,node b)
{
	return a.z>b.z;
}
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=m; i++)
	{
		read(a[i].x);
		read(a[i].y);
		read(a[i].z);
	}
	sort(a+1,a+1+m,cmp);
	l=0;
	r=a[1].z;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else
			l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
