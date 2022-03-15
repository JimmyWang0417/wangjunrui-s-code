#include <cstdio>
#include <algorithm>
#include <vector>
#define ll long long
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
#define int ll
const int N = 2e5 + 10;
vector<pair<int,int> >mat[N];
int ans[N];
#define pb push_back
signed main()
{
	int n;
	read(n);
	for(re int i=1; i<n; ++i)
	{
		int x , y;
		read(x),read(y);
		mat[x].pb(make_pair(y , i));
		mat[y].pb(make_pair(x , i));
	}
	int cnt = 1;
	for(re int i=1; i<=n; ++i)
	{
		if(mat[i].size() > 2)
		{
			for(auto j : mat[i])
				ans[j.second] = cnt ++;
			break;
		}
	}
	for(re int i=1; i<n; ++i)
	{
		if(ans[i] == 0)
			ans[i] = cnt ++;
		printf("%lld\n",ans[i]-1);
	}
	return 0;
}
