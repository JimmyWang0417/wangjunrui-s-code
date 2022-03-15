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
const int N=15;
int h[N][N],l[N][N],g[N][N];
char str[N][N];
int ans[N][N];
inline void print()
{
	
	for(int i=0; i<9; ++i)
	{
		for(int j=0; j<9; ++j)
			printf("%d",ans[i][j]);
		putchar('\n');
	}
	exit(0);
}
inline void dfs(int x,int y)
{
	if(x>9)
	{
		print();
		return;
	}
	if(str[x][y]=='.')
	{
		int fx=x,fy=y;
		++fy;
		if(fy>=9)
		{
			++fx;
			fy=0;
		}
		for(int i=1; i<=9; ++i)
		{
			if(h[x][i]||l[y][i]||g[x/3*3+y/3][i])
				continue;
			ans[x][y]=i;
			h[x][ans[x][y]]=l[y][ans[x][y]]=g[x/3*3+y/3][ans[x][y]]=true;
			dfs(fx,fy);
			h[x][ans[x][y]]=l[y][ans[x][y]]=g[x/3*3+y/3][ans[x][y]]=false;

		}
	}
	else
	{
		++y;
		if(y>=9)
		{
			++x;
			y=0;
		}
		dfs(x,y);
	}

}
signed main()
{
	for(int i=0; i<9; ++i)
		scanf("%s",str[i]);
	for(int x=0; x<9; ++x)
	{
		for(int y=0; y<9; ++y)
			if(str[x][y]!='.')
			{
				ans[x][y]=str[x][y]-'0';
				h[x][ans[x][y]]=l[y][ans[x][y]]=g[x/3*3+y/3][ans[x][y]]=true;
			}
	}
	dfs(0,0);
	return 0;
}


