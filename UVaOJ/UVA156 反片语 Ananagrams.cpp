#include<cstdio>
#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
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
map<string,int>cnt;
vector<string>words,ans;
string s,r;
int n;
inline string change(string s)
{
	for(re int i=0; i<s.length(); i++)
		s[i]=tolower(s[i]);
	sort(s.begin(),s.end());
	return s;
}
int main()
{
	while(cin>>s)
	{
		if(s[0]=='#')
			break;
		words.push_back(s);
		r=change(s);
		cnt[r]++;
	}
	for(re int i=0; i<words.size(); i++)
		if(cnt[change(words[i])]==1)
			ans.push_back(words[i]);
	sort(ans.begin(),ans.end());
	for(re int i=0; i<ans.size(); i++)
		printf("%s\n",ans[i].data());
	return 0;
}
