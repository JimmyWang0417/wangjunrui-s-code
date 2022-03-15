#include<iostream>
#define re register
using namespace std;
string a,b,c;
inline void work()
{
	cin>>a>>b>>c;
	for(re int i=0; i<a.length(); ++i)
		if(c[i]!=a[i]&&c[i]!=b[i])
		{
			printf("NO\n");
			return;
		}
	printf("YES\n");
}
int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--)
		work();
}
