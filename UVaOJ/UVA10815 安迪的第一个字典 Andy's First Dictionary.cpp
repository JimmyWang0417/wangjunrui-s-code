#include<iostream>
#include<set>
#include<string>
#include<sstream>
#define re register
using namespace std;
set<string>dict;
string s,buf;
int main()
{
	while(cin>>s)
	{
		for(re int i=0; i<s.length(); i++)
			if(isalpha(s[i]))
				s[i]=tolower(s[i]);
			else
				s[i]=' ';
		stringstream ss(s);
		while(ss>>buf)
			dict.insert(buf);
	}
	for(set<string>::iterator it=dict.begin(); it!=dict.end(); it++)
		cout<<*it<<endl;
	return 0;
}