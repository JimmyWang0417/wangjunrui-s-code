#include <bits/stdc++.h>
#define int ll
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
const int N=1e6+5;
const int mod=1e9+7;
const int dx[]= {0,0,1,-1,1,-1,-1,1};
const int dy[]= {1,-1,0,0,1,1,-1,-1};
int power[N];
int n;
struct node
{
	int x,y;
} a[N];
int have[N],use[N];
int limit[8];
int can[N];
inline bool check(int pos,int id)
{
	return dx[id]*a[pos].x+dy[id]*a[pos].y==limit[id];
}
vector<int>corner;
ll ans=0;
inline void dfs(int pos)
{
	if(pos==corner.size())
	{
		ll res=1;
		for(int i=0; i<8; ++i)
			if(use[i])
				(res*=power[have[i]])%=mod;
			else
				(res*=power[have[i]]-1)%=mod;
		(ans+=res)%=mod;
		return;
	}
	dfs(pos+1);
	for(int i=0; i<8; ++i)
		if(check(corner[pos],i))
			++use[i];
	dfs(pos+1);
	for(int i=0; i<8; ++i)
		if(check(corner[pos],i))
			--use[i];
}
int useless;
signed main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	read(n);
	power[0]=1;
	for(int i=1; i<=n; ++i)
		power[i]=power[i-1]*2%mod;
	for(int i=1; i<=n; ++i)
		read(a[i].x,a[i].y);
	memset(limit,~0x3f,sizeof(limit));
	for(int i=0; i<8; ++i)
		for(int j=1; j<=n; ++j)
			limit[i]=max(limit[i],dx[i]*a[j].x+dy[i]*a[j].y);
//	for(int i=0; i<8; ++i)
//		printf("%d ",limit[i]);
//	putchar('\n');
	for(int i=0; i<8; ++i)
		for(int j=1; j<=n; ++j)
			if(check(j,i))
				++can[j];
	for(int i=0; i<8; ++i)
		for(int j=1; j<=n; ++j)
			if(check(j,i)&&can[j]==1)
				++have[i];
	for(int i=1; i<=n; ++i)
		if(can[i]>1)
			corner.push_back(i);
		else if(can[i]==0)
			++useless;
	dfs(0);
	printf("%lld\n",ans*power[useless]%mod);
	return 0;
}

