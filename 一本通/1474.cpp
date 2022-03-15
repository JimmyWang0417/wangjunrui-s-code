#include<cstdio>
#include<cstring>
using namespace std;
#define r register
int ch[100][2],tot,t;
bool bo[100];
char s[11];
inline bool insert(char *s)
{
    int len=strlen(s),u=1;
    bool flag=false;
    for(r int i=0,c; i<len; i++)
    {
        c=s[i]-'0';
        if(!ch[u][c])
            ch[u][c]=++tot;
        else if(i==len-1)
            flag=true;
        u=ch[u][c];
        if(bo[u])
            flag=true;
    }
    bo[u]=true;
    return flag;
}
int main()
{
	while(1)
	{
		++t;
		tot=1;
		bool ans=false;
		while(1)
		{
			scanf("%s",s);
			//printf("%s\n",s);
			if(s[0]=='9'&&strlen(s)==1)break;
			ans=ans||insert(s);
		}
		if(ans)
			printf("Set %d is not immediately decodable\n",t);
		else
			printf("Set %d is immediately decodable\n",t);
		memset(ch,0,sizeof(ch));
		memset(bo,false,sizeof(bo));
	}
}

