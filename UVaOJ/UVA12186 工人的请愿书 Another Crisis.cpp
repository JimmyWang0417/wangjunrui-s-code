#include<cstdio>
#include<algorithm>
#include<vector>
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
vector<vector<int> >son;
int T;
inline int dp(int u)
{
	if(son[u].empty())
		return 1;
	vector<int>d;
	int num=son[u].size();
	for(re int i=0; i<num; ++i)
		d.push_back(dp(son[u][i]));
	stable_sort(d.begin(),d.end());
	int c=(num*T-1)/100+1;
	re int ans=0;
	for(re int i=0; i<c; ++i)
		ans+=d[i];
	return ans;
}
int n;
int main()
{
	//freopen("ans.in","r",stdin);
	//freopen("ans.out","w",stdout);
	while(read(n),read(T),n&&T)
	{
		re int b;
		for(re int i=0; i<=n; ++i)
			son.push_back(vector<int>());
		for(re int i=1; i<=n; ++i)
		{
			read(b);
			son[b].push_back(i);
		}
		printf("%d\n",dp(0));
		son.clear();
	}
	return 0;
}
