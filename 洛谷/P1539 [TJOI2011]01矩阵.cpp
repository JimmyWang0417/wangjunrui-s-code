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
const int N=230;
const int mod=10007;
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
char str[N][N];
char solvestr[N][N];
int n,m;
unordered_map<int,int>heapmap[2];
signed main()
{
	read(n,m);
	for(int i=0; i<n; ++i)
		scanf("%s",str[i]);
	if(n<m)
	{
		for(int i=0; i<n; ++i)
			for(int j=0; j<m; ++j)
				solvestr[j][i]=str[i][j];
		swap(n,m);
	}
	else
	{
		for(int i=0; i<n; ++i)
			for(int j=0; j<m; ++j)
				solvestr[i][j]=str[i][j];
	}
	int now=0,las=1;
#define f0 heapmap[now]
#define f1 heapmap[las]
	f1[0]=1;
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<m; ++j)
		{
			swap(las,now);
			f1.clear();
			for(auto v:f0)
			{
				const int bit=v.first,val=v.second;
				if(solvestr[i][j]=='0')
					add(f1[bit&(~(1<<j))],val);
				else if(solvestr[i][j]=='1')
				{
					if(!((bit>>j)&1)&&!(j&&((bit>>(j-1))&1)))
						add(f1[bit|(1<<j)],val);
				}
				else
				{
					add(f1[bit&(~(1<<j))],val);
					if(!((bit>>j)&1)&&!(j&&((bit>>(j-1))&1)))
						add(f1[bit|(1<<j)],val);
				}
			}
		}
	}
	swap(las,now);
	int ans=0;
	for(auto v:f0)
		add(ans,v.second);
	printf("%d\n",ans);
	return 0;
}

