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
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=1e5+5;
int n;
int a[N];
int ch[N*31][2],tot,bo[N*31];
inline void insert(int id,int val)
{
	int u=0;
	for(int i=30; i>=0; --i)
	{
		int c=(val>>i)&1;
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	bo[u]=id;
}
inline pair<int,int> find(int val)
{
	int u=0;
	int ans=0;
	for(int i=30; i>=0; --i)
	{
		int c=(val>>i)&1;
		if(ch[u][!c])
		{
			u=ch[u][!c];
			ans|=(1<<i);
		}
		else
			u=ch[u][c];
	}
	return make_pair(ans,bo[u]);
}
signed main()
{
	read(n);
	insert(0,0);
	pair<pair<int,int>,int>ans(make_pair(make_pair(-1,0),0));
	for(int i=1; i<=n; ++i)
	{
		read(a[i]);
		a[i]^=a[i-1];
		pair<int,int>now(find(a[i]));
//		printf("%d %d %d\n",now.first,now.second,i);
		if(now.first>ans.first.first)
			ans=make_pair(now,i);
		insert(i,a[i]);
	}
	printf("%d %d %d\n",ans.first.first,ans.first.second+1,ans.second);
	return 0;
}


