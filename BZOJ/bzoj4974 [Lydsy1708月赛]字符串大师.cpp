#include<cstdio>
#include<cstring>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
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
	if(f)
		x=(~x)+1;
}
const int N=1e5+10,S=30;
int n;
int p[N];
bool vis[S];
char str[N];
int main()
{
	read(n);
	p[0]=-1;
	for(re int i=1; i<=n; ++i)
	{
		read(p[i]);
		p[i]=i-p[i];
		if(p[i])
			str[i]=str[p[i]];
		else
		{
			for(re int j=p[i-1]; ~j; j=p[j])
				vis[str[j+1]-'a']=true;
//			for(re int j=0; j<=26; ++j)
//				printf("%d ",vis[j]);
			for(re int j=0; j<=26; ++j)
				if(!vis[j])
				{
					str[i]=j+'a';
					//printf("%d %c\n",i,j+'a');
					break;
				}
			memset(vis,false,sizeof(vis));
		}
		//printf("%d ",i);
	}
	printf("%s\n",str+1);
}
