#include<cstdio>
#include<cstring>
#define re register
#define min(x,y) (x<y?x:y)
using namespace std;
const int N=1000010;
int m,p[N];
char s1[N<<1],s[N];
int main()
{
	scanf("%s%s",s1,s);
	m=strlen(s);
	strcat(s,"#");
	strcat(s,s1);
	for(re int i=1,mx=0,l=0; s[i]; i++)
	{
		p[i]=i<mx?min(mx-i,p[i-l]):0;
		while(s[p[i]]==s[i+p[i]])
			p[i]++;
		if(i+p[i]>mx)
		{
			mx=i+p[i];
			l=i;
		}
	}
	for(re int i=0; i<m; i++)
		printf("%d ",i?p[i]:m);
	puts("\0");
	for(re int i=m+1; s[i]; i++)
		printf("%d ",p[i]);
	return 0;
}

