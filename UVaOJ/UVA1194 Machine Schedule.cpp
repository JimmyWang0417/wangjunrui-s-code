#include<cstdio>
#include<vector>
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
const int N=110;
int n,m,k,f[N],ans;
bool v[N];
vector<int>e[N];
inline bool dfs(int x)
{
	for(re int i=0; i<e[x].size(); i++)
	{
		int y=e[x][i];
		if(v[y])
			continue;
		v[y]=true;
		if(!f[y]||dfs(f[y]))
		{
			f[y]=x;
			return true;
		}
	}
	return false;
}
inline void machine_schedule()
{
	read(m);
	read(k);
	for(re int i=0,x,y; i<k; i++)
	{
		read(i);
		read(x);
		read(y);
		e[x].push_back(y);
	}
	for(re int i=1; i<=n; i++)
	{
		fill(v,v+1+n,false);
		ans+=dfs(i);
	}
	printf("%d\n",ans);
	fill(f,f+1+n,0);
	ans=0;
	for(re int i=1; i<=n; i++)
		e[i].clear();
}
int main()
{
	while(read(n),n)
		machine_schedule();
}

