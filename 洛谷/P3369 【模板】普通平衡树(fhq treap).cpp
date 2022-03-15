#include <cstdio>
#include <ctime>
#include <random>
using namespace std;

template <typename T>
inline void read(T &x)
{
    x = 0;
    char s = (char)getchar();
    bool f = false;
    while (!(s >= '0' && s <= '9'))
    {
        if (s == '-')
            f = true;
        s = (char)getchar();
    }
    while (s >= '0' && s <= '9')
    {
        x = (x << 1) + (x << 3) + s - '0';
        s = (char)getchar();
    }
    if (f)
        x = (~x) + 1;
}

const int N = 1e5 + 5;
mt19937 rnd((unsigned int)time(0));
class fhq_treap
{
private:
    struct Tree
    {
        int val, key, size;
        int l, r;
    } tree[N];
    int cnt, root;
    inline int newnode(int val)
    {
        tree[++cnt].val = val;
        tree[cnt].key = rnd();
        tree[cnt].size = 1;
        return cnt;
    }
    inline void pushup(int now)
    {
        tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size + 1;
        return;
    }
    inline void split(int now, int val, int &x, int &y)
    {
        if (!now)
            x = y = 0;
        else
        {
            if (tree[now].val <= val)
            {// now的权值小于等于val，说明now以及now的左子树都属于x，所以递归划分now的右子树
                x = now;
                split(tree[now].r, val, tree[now].r, y);
            }
            else
            {// now的权值大于v，说明now以及now的右子树都属于y，所以递归划分now的左子树
                y = now;
                split(tree[now].l, val, x, tree[now].l);
            }
            pushup(now);
        }
        return;
    }
    inline int merge(int x, int y)
    {
        if (!x)
            return y;
        if (!y)
            return x;
        if (tree[x].key > tree[y].key)// 若x优先级小，则它应该为新树的根
        {// 由于x中元素都比y中元素权值小，所以合并x的右子树与y
            tree[x].r = merge(tree[x].r, y);
            pushup(x);
            return x;
        }
        else
        {//若y优先级小，则y应该为新树的根
            tree[y].l = merge(x, tree[y].l);
            pushup(y);
            return y;
        }
    }

public:
    inline void insert(int val)
    {
        int x, y;
        split(root, val, x, y);
        root = merge(merge(x, newnode(val)), y);
        return;
    }
    inline void del(int val)
    {
        int x, y, z;
        split(root, val, x, z);
        split(x, val - 1, x, y);
        y = merge(tree[y].l, tree[y].r); //只删除一个数
        root = merge(merge(x, y), z);
        return;
    }
    inline void getrank(int val)
    {
        int x, y;
        split(root, val - 1, x, y);
        printf("%d\n", tree[x].size + 1);
        root = merge(x, y);
        return;
    }
    inline void getnum(int rank)
    {
        int now = root;
        while (now)
        {
            if (rank == tree[tree[now].l].size + 1)
                break;
            else if (tree[tree[now].l].size >= rank)
                now = tree[now].l;
            else
            {
                rank -= tree[tree[now].l].size + 1;
                now = tree[now].r;
            }
        }
        printf("%d\n", tree[now].val);
        return;
    }
    inline void pre(int val)
    {
        int x, y;
        split(root, val - 1, x, y);
        int now = x;
        while (tree[now].r)
            now = tree[now].r;
        printf("%d\n", tree[now].val);
        root = merge(x, y);
        return;
    }
    inline void next(int val)
    {
        int x, y;
        split(root, val, x, y);
        int now = y;
        while (tree[now].l)
            now = tree[now].l;
        printf("%d\n", tree[now].val);
        root = merge(x, y);
        return;
    }
    inline void getans()
    {
        int opt, val;
        read(opt), read(val);
        switch (opt)
        {
        case 1:
            insert(val);
            break;
        case 2:
            del(val);
            break;
        case 3:
            getrank(val);
            break;
        case 4:
            getnum(val);
            break;
        case 5:
            pre(val);
            break;
        case 6:
            next(val);
            break;
        }
    }
} fhq;
int n;
int main()
{
    read(n);
    while (n--)
        fhq.getans();
}
