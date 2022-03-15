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
const int N=1e6+5;
int n;
int a[N];
signed main()
{
	int T;
	read(T);
	for(int kase=1; kase<=T; ++kase)
	{
		if(kase==1)
		{
			read(n);
			for(int i=1; i<=n; ++i)
				read(a[i]);
		}
		else
		{
			int cnt;
			read(cnt);
			while(cnt--)
			{
				int p,v;
				read(p,v);
				a[p]=v;
			}
		}
		vector<pair<int,int> >s;
		for(int i=1; i<=n; ++i)
			s.push_back(make_pair(a[i],i));
		int ans,flag=0;
		while(1)
		{
			if(s.size()==2)
			{
				s.erase(s.begin());
				if(flag)
				{
					if((flag-s.size())&1)
						ans=flag+1;
					else
						ans=flag;
				}
				else
					ans=1;
				break;
			}
			auto it=s.end();
			--it;
			int x=s.begin()->first,y=it->first,id=it->second;
			s.erase(s.begin());
			s.erase(it);
			s.insert(lower_bound(s.begin(),s.end(),make_pair(y-x,id)),make_pair(y-x,id));
			if(s.begin()->second!=id)
			{
				if(flag)
				{
					if((flag-s.size())&1)
						ans=flag+1;
					else
						ans=flag;
					break;
				}
			}
			else
			{
				if(!flag)
					flag=s.size();
//				printf("+");
			}
//			printf("%d\n",flag);
		}
		printf("%d\n",ans);
	}
	return 0;
}


