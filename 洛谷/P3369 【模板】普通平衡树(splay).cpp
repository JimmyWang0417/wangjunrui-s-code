#include <cstdio>
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
struct Tree
{
    int size, cnt;
    int val, ch[2];
    int fa;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
int root, cnt;
inline bool check(int x) // 查询改节点在左子树还是右子树
{
    return rc(fa(x)) == x;
}
inline void pushup(int now)
{
    tree[now].size = tree[lc(now)].size + tree[rc(now)].size + tree[now].cnt;
}
inline void rotate(int x)
{ // y为x的父结点，z为x的祖父结点并选取不以y->x同侧的x的儿子w，以维持BST性质
    int y = fa(x), z = fa(y), k = check(x), w = tree[x].ch[k ^ 1];
    tree[z].ch[check(y)] = x, fa(x) = z; //将x的父结点接到z上，y的父结点接到x
    tree[y].ch[k] = w, fa(w) = y;        //将w接在y上
    tree[x].ch[k ^ 1] = y, fa(y) = x;    //将y接在x上
    pushup(y), pushup(x);
}
inline void splay(int x, int target = 0)
{ //通过一系列旋转，将结点x调整为结点target的子结点(target=0则x调整后为根结点)
    while (fa(x) != target)
    {
        int y = fa(x), z = fa(y);
        if (z != target)
        { //若x有祖父结点且与父结点在同一侧，应先调整父结点，提高时间效率
            if (check(x) == check(y))
                rotate(y);
            else
                rotate(x);
        }
        rotate(x);
    }
    if (!target)
        root = x;
}
inline void find(int val)
{ //判断元素v是否在树中
    int now = root;
    while (tree[now].ch[val > tree[now].val] && tree[now].val != val)
        now = tree[now].ch[val > tree[now].val];
    splay(now); //调整伸展树形态
}
inline void insert(int val)
{
    int now = root, las = 0;
    while (now && tree[now].val != val)
    {
        las = now;
        now = tree[now].ch[val > tree[now].val];
    }
    if (now)
        ++tree[now].cnt;
    else
    {
        now = ++cnt;
        if (las)
            tree[las].ch[val > tree[las].val] = now;
        lc(now) = rc(now) = 0;
        tree[now].val = val;
        fa(now) = las;
        tree[now].size = tree[now].cnt = 1;
    }
    splay(now);
}
inline int lower(int val)
{
    find(val);
    if (tree[root].val < val)
        return root;
    int now = lc(root);
    while (rc(now))
        now = rc(now);
    splay(now);
    return now;
}
inline int upper(int val)
{
    find(val);
    if (tree[root].val > val)
        return root;
    int now = rc(root);
    while (lc(now))
        now = lc(now);
    splay(now);
    return now;
}
inline void del(int val)
{
    int pre = lower(val), nxt = upper(val);
    splay(pre), splay(nxt, pre);
    int now = lc(nxt);
    if (tree[now].cnt > 1)
    {
        --tree[now].cnt;
        splay(now);
    }
    else
        lc(nxt) = 0;
    pushup(nxt), pushup(root);
}
inline int k_th(int rk)
{
    int now = root;
    while (1)
    {
        if (lc(now) && rk <= tree[lc(now)].size)
            now = lc(now);
        else if (rk > tree[lc(now)].size + tree[now].cnt)
        {
            rk -= tree[lc(now)].size + tree[now].cnt;
            now = rc(now);
        }
        else
        {
            splay(now);
            return now;
        }
    }
}
inline int getrank(int val)
{
    find(val);
    if (tree[root].val < val)
        return tree[lc(root)].size + tree[root].size;
    else
        return tree[lc(root)].size;
}
const int INF = 0x3f3f3f3f;
int n;
int main()
{
    insert(INF);
    insert(~INF);
    read(n);
    while (n--)
    {
        int opt, val;
        read(opt), read(val);
        if (opt == 1)
            insert(val);
        else if (opt == 2)
            del(val);
        else if (opt == 3)
            printf("%d\n", getrank(val));
        else if (opt == 4)
            printf("%d\n", tree[k_th(val + 1)].val);
        else if (opt == 5)
            printf("%d\n", tree[lower(val)].val);
        else if (opt == 6)
            printf("%d\n", tree[upper(val)].val);
    }
    return 0;
}
