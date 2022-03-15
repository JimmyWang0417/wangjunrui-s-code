#include<cstdio>
#include<bitset>
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
const int N=2010;
vector<int> e[N];
bitset<N> v;
int n,m,q,x,y,ans,f[N];
inline bool dfs(int x)
{
	for(re int i=0; i<e[x].size(); i++)
	{
		int y=e[x][i];
		if(v[y]);
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
int main()
{
	read(n);
	read(m);
	read(q);
	while(q--)
	{
		read(x);
		read(y);
		if(x>n||y>m)
			continue;
		e[x].push_back(y+n);
		e[y+n].push_back(x);
	}
	for(re int i=1; i<=n; i++)
	{
		v.reset();
		ans+=dfs(i);
	}
	printf("%d\n",ans);
	return 0;
}

