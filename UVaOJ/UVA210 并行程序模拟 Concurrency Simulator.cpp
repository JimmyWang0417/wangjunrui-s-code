#include<cstdio>
#include<iostream>
#include<deque>
#include<vector>
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
	return;
}
int var[256];
int Lock;
int n,t1,t2,t3,t4,t5,Q;
struct node
{
	int id, spare, len, where;
	vector<string> name, val;
	node()
	{
		name.push_back("");
		val = name;
		len = 0;
	}
	inline void push(const string& s1 = "", const string& s2 = "")
	{
		name.push_back(s1);
		val.push_back(s2);
	}
};
deque<node>wait,stop;
inline int to_int(const string& s)
{
	int ret;
	sscanf(s.c_str(), "%d", &ret);
	return ret;
}
inline void work(node x)
{
	for(re int i=x.where; i<=x.len&&x.spare>0; ++i)
	{
		string mark=x.name[i];
		if(mark=="print")
		{
			printf("%d: %d\n",x.id,var[x.val[i][0]]);
			x.spare-=t2;
			++x.where;
		}
		else if(mark=="lock")
		{
			if(!Lock||Lock == x.id)
			{
				Lock=x.id;
				x.spare-=t3;
				++x.where;
			}
			else
			{
				stop.push_back(x);
				return;
			}
		}
		else if(mark == "unlock")
		{
			Lock=0;
			x.spare-=t4;
			++x.where;
			if(!stop.empty())
			{
				wait.push_front(stop.front());
				stop.pop_front();
			}
		}
		else if(mark == "end")
		{
			return;
		}
		else
		{
			var[mark[0]]=to_int(x.val[i]);
			x.spare-=t1;
			++x.where;
		}
	}
	wait.push_back(x);
}
int main()
{
	re int T;
	read(T);
	while(T--)
	{
		memset(var, 0, sizeof(var));
		wait.clear();
		stop.clear();
		Lock = 0;
		read(n),read(t1),read(t2);
		read(t3),read(t4),read(t5),read(Q);
		for(re int i=1; i<=n; ++i)
		{
			node pro;
			pro.where=1;
			pro.id=i;
			while(1)
			{
				string tmp1, tmp;
				cin>>tmp1;
				if(tmp1=="print")
				{
					cin>>tmp;
					pro.push(tmp1,tmp);
					++pro.len;
				}
				else if(tmp1=="lock"||tmp1=="unlock")
				{
					pro.push(tmp1);
					++pro.len;
				}
				else if(tmp1=="end")
				{
					pro.push(tmp1);
					++pro.len;
					break;
				}
				else
				{
					string temp;
					cin>>temp;
					cin>>tmp;
					pro.push(tmp1, tmp);
					++pro.len;
				}
			}
			wait.push_back(pro);
		}
		while(!wait.empty())
		{
			node forces=wait.front();
			wait.pop_front();
			forces.spare=Q;
			work(forces);
		}
		if(T)
			putchar('\n');
	}
	return 0;
}
