#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
#define re register
using namespace std;
int n,maxlen;
string s[1010];
inline void print(const string &s,int len,char e)
{
	printf("%s",s.data());
	for(re int i=0; i<len-s.length(); i++)
		putchar(e);
}
int main()
{
	re int col,row;
	while(cin>>n)
	{
		maxlen=0;
		for(re int i=0; i<n; i++)
		{
			cin>>s[i];
			maxlen=max(maxlen,(int)s[i].length());
		}
		col=(60-maxlen)/(maxlen+2)+1;
		row=(n-1)/col+1;
		print("",60,'-');
		putchar('\n');
		sort(s,s+n);
		for(re int r=0; r<row; r++)
		{
			for(re int c=0; c<col; c++)
			{
				int id=c*row+r;
				if(id<n)
					print(s[id],c==col-1?maxlen:maxlen+2,' ');
			}
			putchar('\n');
		}
	}
	return 0;
}
