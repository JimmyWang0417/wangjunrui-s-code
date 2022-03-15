#include<cstdio>
using namespace std;
#define ri register int
inline int read()
{
	char s=getchar();
	bool f=false;
	int x=0;
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
	return f?-x:x;
}
int n,k,ans;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
	for(ri i=1; i<=n; i++)
		ans^=read();
	if(ans==0)
		printf("lose\n");
	else
		printf("win\n");
}

