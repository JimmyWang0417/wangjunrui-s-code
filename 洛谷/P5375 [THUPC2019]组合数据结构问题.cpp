#include <bits/stdc++.h>
using namespace std;
queue <int> a;
stack <int> b;
priority_queue <int> c;
priority_queue <int, vector<int>, greater<int> > d;
int n, flag[5];

inline int read()
{
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int main()
{
	n = read();
	while (n--)
	{
		int opt = read(), k = read();
		if (opt == 1)
		{
			if (!flag[1]) a.push(k);
			if (!flag[2]) b.push(k);
			if (!flag[3]) c.push(k) ;
			if (!flag[4]) d.push(k);
		}
		else
		{
			if (a.empty()) flag[1] = 1;
			if (b.empty()) flag[2] = 1;
			if (c.empty()) flag[3] = 1;
			if (d.empty()) flag[4] = 1;
			if (!flag[1]) if (a.front() == k) a.pop();
				else flag[1] = 1;
			if (!flag[2]) if (b.top() == k) b.pop();
				else flag[2] = 1;
			if (!flag[3]) if (c.top() == k) c.pop();
				else flag[3] = 1;
			if (!flag[4]) if (d.top() == k) d.pop();
				else flag[4] = 1;
		}
	}
	for (int i = 1; i <= 4; ++i)
		if (flag[i]) puts("No");
		else puts("Yes");
	return 0;
}
