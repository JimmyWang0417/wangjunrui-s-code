#include<iostream>
#define re register
using namespace std;
const int N=155;
int n,height[N];
int ans;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(re int i=1; i<=n; ++i)
	{
		for(re int j=1; j<=n; ++j)
		{
			static char ch;
			cin>>ch;
			if(ch=='W')
				++height[j];
			else
				height[j]=0;
		}
		for(re int j=1; j<=n; ++j)
		{
			int now=height[j];
			ans+=now;
			for(re int k=j+1; k<=n&&now; ++k)
			{
				now=min(now,height[k]);
				ans+=now;
			}
		}
	}
	cout<<ans<<endl; 
	return 0;
}
