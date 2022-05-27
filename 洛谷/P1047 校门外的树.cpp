#include <cstdio>
#define MAXN 100007
using namespace std;
int n, m, x, y;
struct SegTree
{
    int l;       //��˵�
    int r;       //�Ҷ˵�
    long long w; //����ͣ���ʾ����������������
    int lt;      // lazytag(������)
    int add;
    int mul;
    SegTree()
    {
        lt = 1; //��lazytag��ʼ��Ϊһ
    }
} tree[MAXN << 2]; //ע��tree����ĳ�������Ϊmaxn*4
inline int read()
{
    register char s = getchar();
    int x = 0;
    while (s < '0' || s > '9')
        s = getchar();
    while (s >= '0' && s <= '9')
    {
        x = (x << 1) + (x << 3) + s - '0';
        s = getchar();
    }
    return x;
}
inline void build(int l, int r, int u) //����
{
    tree[u].l = l, tree[u].r = r;
    if (l == r)
    {
        tree[u].w = 1; //һ���ҵ�Ҷ�ڵ㣬ֱ�ӽ�ֵ��Ϊ1(��Ϊû������ֻ��һ����)
        return;
    }
    int m = (l + r) / 2; //����
    build(l, m, u + u);
    build(m + 1, r, u + u + 1);
    tree[u].w = tree[u + u].w + tree[u + u + 1].w; //����ͼ�Ϊ�������������֮�ͣ��ƿڵ��������⣩
}
inline void down(int u) //����lazytag
{
    tree[u + u].lt = tree[u].lt; //ֱ�ӽ�lazytag�����ӽڵ�
    tree[u + u + 1].lt = tree[u].lt;
    tree[u + u].w = tree[u].lt; //����lazytag����Ǻ�ֵΪ0���޸������ڵ���ҲҪ��Ϊ0������ֱ�ӽ�lazytag�����ӽڵ��w
    tree[u + u + 1].w = tree[u].lt;
    tree[u].lt = 1; //�����ȥ��
}
inline void change(int u) //�����޸�
{
    if (tree[u].l >= x && tree[u].r <= y) //�������䱻���޸����串�ǣ�ֱ�ӽ��������0����Ҫȫ��ȥ�����������ϱ��
    {
        tree[u].w = 0;
        tree[u].lt = 0;
        return;
    }
    if (tree[u].lt != 1)
        down(u); //���б��������
    int m = (tree[u].l + tree[u].r) / 2;
    if (x <= m)
        change(u + u); //�ж��е������Ƿ��д��޸ĵĵ�
    if (y > m)
        change(u + u + 1);
    tree[u].w = tree[u + u + 1].w + tree[u + u].w; //���µ�ǰ��������
}
int main()
{
    n = read();
    m = read();
    ++n; //����λ����0~n->1~n+1
    build(1, n, 1);
    while (m--)
    {
        x = read();
        y = read();
        ++x, ++y;
        change(1);
    }
    printf("%lld", tree[1].w); //ֱ������޸ĺ���������֮��
    return 0;
}
