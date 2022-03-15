#include<cstdio>
#define re register
#define ll long long
using namespace std;
const int N=1005,SIZE=30;
int n,ch[N*SIZE][SIZE],tot=1,sum[N*SIZE];
char s[N][SIZE];
inline void insert(char *s)
{
	re int u=1;
	for(; *s; ++s)
	{
		int c=*s-'a';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
		++sum[u];
	}
}
inline void find(char *s)
{
	re int u=1;
	for(; *s; ++s)
	{
		int c=*s-'a';
		u=ch[u][c];
		putchar(*s);
		if(sum[u]==1)
			break;
	}
}
int main()
{
	int n=1;
	while(scanf("%s",s[n])!=EOF)
	{
		insert(s[n]);
		++n;
	}
	for(re int i=1; i<n; ++i)
	{
		printf("%s ",s[i]);
		find(s[i]);
		putchar('\n');
	}
	return 0;
}
