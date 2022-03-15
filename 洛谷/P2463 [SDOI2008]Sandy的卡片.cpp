#include <bits/stdc++.h>
#define lowbit(x) (x&(-x))
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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1000*100*2+5;
using std::map;
using std::max;
int n;
class SAM
{
	private:
		struct Point
		{
			int fa,len,size,vis;
			map<int,int>ch;
		} point[N];
	public:
		int las=1,tot=1;
		inline void insert(int c,int id)
		{
			int p=las,np=las=++tot;
			point[np].len=point[p].len+1;
			for(; p&&!point[p].ch.count(c); p=point[p].fa)
				point[p].ch[c]=np;
			if(!p)
				point[np].fa=1;
			else
			{
				int q=point[p].ch[c];
				if(point[q].len==point[p].len+1)
					point[np].fa=q;
				else
				{
					int nq=++tot;
					point[nq]=point[q];
					point[nq].len=point[p].len+1;
					point[q].fa=point[np].fa=nq;
					for(; p&&point[p].ch[c]==q; p=point[p].fa)
						point[p].ch[c]=nq;
				}
			}
			for(; np&&point[np].vis!=id; np=point[np].fa)
			{
				point[np].vis=id;
				++point[np].size;
			}
		}
		inline int solve()
		{
			int ans=0;
			for(re int i=1; i<=tot; ++i)
				if(point[i].size==n)
					ans=max(point[i].len,ans);
			return ans+1;
		}
} tree;
signed main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		int m,las,val;
		read(m,las);
		for(re int j=2; j<=m; ++j)
		{
			read(val);
			tree.insert(val-las,i);
			las=val;
		}
		tree.las=1;
	}
	printf("%d\n",tree.solve());
	return 0;
}

