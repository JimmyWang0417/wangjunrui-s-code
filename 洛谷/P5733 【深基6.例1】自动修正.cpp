#include<cstdio>
char s[105];
int main()
{
	scanf("%s",s+1);
	for(int i=1; s[i]; ++i)
		printf("%c",s[i]>='a'&&s[i]<='z'?s[i]+'A'-'a':s[i]);
	return 0;
}
