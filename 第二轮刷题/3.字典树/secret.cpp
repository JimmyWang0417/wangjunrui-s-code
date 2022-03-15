#include<cstdio>
#include<vector>
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
const int N=1e6+5;
int n,a[N],val[N],ch[N][2],tot;
inline int get()
{
	++tot;
	ch[tot][0]=ch[tot][1]=0;
	return tot;
}
inline void insert(int id)
{
	for(re int i=30,u=1; i>=0; --i)
	{
		bool c=val[id]&(1<<i);
		if(!ch[u][c])
			ch[u][c]=get();
		u=ch[u][c];
	}
}
inline int find(int id)
{
	int ans=0;
	for(re int i=30,u=1; i>=0; --i)
	{
		bool c=val[id]&(1<<i);
		if(ch[u][c])
			u=ch[u][c];
		else
		{
			u=ch[u][!c];
			ans|=(1<<i);
		}
	}
	return ans;
}
ll ans=0;
inline void solve(vector<int>tree,int dep)
{
	if(tree.size()<=1)
		return;
	if(dep==-1)
		return;
	vector<int>son[2];
	for(re int i=0; i<tree.size(); ++i)
		son[(bool)(val[tree[i]]&(1<<dep))].push_back(tree[i]);
	if(son[0].size()&&son[1].size())
	{
		tot=1;
		ch[tot][0]=ch[tot][1]=0;
		int minn=0x7fffffff;
		for(re int i=0; i<son[0].size(); ++i)
			insert(son[0][i]);
		for(re int i=0; i<son[1].size(); ++i)
			minn=min(minn,find(son[1][i]));
		ans+=minn;
	}
	if(son[0].size())
		solve(son[0],dep-1);
	if(son[1].size())
		solve(son[1],dep-1);
}
int main()
{
	vector<int>tree;
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=1; i<=n; ++i)
		val[i]=val[i-1]^a[i];
	for(re int i=0; i<=n; ++i)
		tree.push_back(i);
	solve(tree,30);
	printf("%lld\n",ans);
}
