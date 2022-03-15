#include<iostream>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#define ALL(x) x.begin(),x.end()
#define INS(x) inserter(x,x.begin())//插入迭代器，用于后面的取并集、交集以及合并后返回一个set<int>，详见第43至49行的详细使用。
using namespace std;
map<set<int>,int> IDdata;//将集合映射成数，具体为什么用set<int>相信每一位了解stl的C党都明白。
vector< set<int> > setdata;//可以理解为集合的检索表，用于对集合ID的分配与对已知ID的集合的查询。
int ID(set<int> x)   //查找给定集合x的ID。若找不到，分配一个新ID。
{
	if(IDdata.count(x))return IDdata[x];
	setdata.push_back(x);
	return IDdata[x]=setdata.size()-1;
}
int main()
{
	int T;
	cin>>T;
	while(T)
	{
		T--;
		stack<int>s;
		int n;
		cin>>n;
		for(int i=1; i<=n; i++)
		{
			string point;
			cin>>point;
			if(point=="PUSH")
				s.push(ID(set<int>()));
			else if(point=="DUP")
				s.push(s.top());
			else
			{
				set<int> x1=setdata[s.top()];
				s.pop();
				set<int> x2=setdata[s.top()];
				s.pop();
				set<int> x;
				if(point=="UNION")set_union(ALL(x1),ALL(x2),INS(x));
				else if(point=="INTERSECT")set_intersection(ALL(x1),ALL(x2),INS(x));
				else if(point=="ADD")
				{
					x=x2;
					x.insert(ID(x1));
				}
				s.push(ID(x));
			}
			cout<<setdata[s.top()].size()<<endl;
		}
		cout<<"***"<<endl;
	}
	return 0;
}
