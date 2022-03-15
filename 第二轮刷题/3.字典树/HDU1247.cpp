#include<cstdio>
#include<string>
#include<cstring>
#define re register
using namespace std;
const int N=50005,SIZE=30;
char str[N][SIZE],tmp1[SIZE],tmp2[SIZE];
int ch[N*SIZE][SIZE],tot=1;
bool bo[N*SIZE];
inline void insert(char *s)
{
	re int u=1;
	for(; *s; ++s)
	{
		int c=*s-'a';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	bo[u]=true;
}
inline bool find(char *s)
{
	re int u=1;
	for(; *s; ++s)
	{
		int c=*s-'a';
		if(!ch[u][c])
			return false;
		u=ch[u][c];
	}
	return bo[u];
}
int main()
{
	int size=1;
	while(scanf("%s",str[size])!=EOF)
		insert(str[size++]);
	for(re int i=1; i<size; ++i)
	{
		int len=strlen(str[i]);
		//printf("%d:\n",i);
		for(re int l=1; l<len; ++l)
		{
			strncpy(tmp1,str[i],l);
			tmp1[l]='\0';
			strncpy(tmp2,str[i]+l,len-l);
			tmp2[len-l]='\0';
			//printf("%s %s\n",tmp1,tmp2);
			if(find(tmp1)&&find(tmp2))
			{
				printf("%s\n",str[i]);
				break;
			}
		}
	}
}
