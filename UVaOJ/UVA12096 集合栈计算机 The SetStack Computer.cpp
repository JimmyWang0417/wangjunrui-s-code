#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x.begin()) //��������������ں����ȡ�����������Լ��ϲ��󷵻�һ��set<int>�������43��49�е���ϸʹ�á�
using namespace std;
map<set<int>, int> IDdata; //������ӳ�����������Ϊʲô��set<int>����ÿһλ�˽�stl��C�������ס�
vector<set<int>> setdata;  //��������Ϊ���ϵļ����������ڶԼ���ID�ķ��������֪ID�ļ��ϵĲ�ѯ��
int ID(set<int> x)         //���Ҹ�������x��ID�����Ҳ���������һ����ID��
{
    if (IDdata.count(x))
        return IDdata[x];
    setdata.push_back(x);
    return IDdata[x] = setdata.size() - 1;
}
int main()
{
    int T;
    cin >> T;
    while (T)
    {
        T--;
        stack<int> s;
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            string point;
            cin >> point;
            if (point == "PUSH")
                s.push(ID(set<int>()));
            else if (point == "DUP")
                s.push(s.top());
            else
            {
                set<int> x1 = setdata[s.top()];
                s.pop();
                set<int> x2 = setdata[s.top()];
                s.pop();
                set<int> x;
                if (point == "UNION")
                    set_union(ALL(x1), ALL(x2), INS(x));
                else if (point == "INTERSECT")
                    set_intersection(ALL(x1), ALL(x2), INS(x));
                else if (point == "ADD")
                {
                    x = x2;
                    x.insert(ID(x1));
                }
                s.push(ID(x));
            }
            cout << setdata[s.top()].size() << endl;
        }
        cout << "***" << endl;
    }
    return 0;
}
