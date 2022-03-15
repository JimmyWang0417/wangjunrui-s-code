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
const int N=50000*50+10;
int n,ch[N][27],tot=1,f[N];
char s[110];
bool bo[N];
inline void insert(char *s)
{
	int u=1,len=strlen(s+1);
	for(re int i=1,c; i<=len; i++)
	{
		c=s[i]-'a';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	bo[u]=true;
}
inline int find(int u)
{
	if(f[u])
		return f[u];
	int &res=f[u]=1;
	for(re int i=0; i<=26; i++)
		if(ch[u][i])
			res=(res*find(ch[u][i]))%9191;
	if(bo[u])
		res++;
	res%=9191;
	return res;
}
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
	{
		scanf("%s",s+1);
		insert(s);
	}
	printf("%d\n",find(1));
	return 0;
}

