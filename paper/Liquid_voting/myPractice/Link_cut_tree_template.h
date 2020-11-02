/*
problem: https://www.luogu.com.cn/problem/P3690
*/ 

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 100010;
struct LCTree
{
    int ch[maxn][2], fa[maxn], tag[maxn], sum[maxn], val[maxn];
    void pushup(int x){sum[x] = sum[ch[x][0]] ^ sum[ch[x][1]] ^ val[x];}

    void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = tag[x] = 0; }
    int getch(int x) { return ch[fa[x]][1] == x; }
    int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

    // 从x开始下传懒标记
    void pushdown(int x)
    {
        if (tag[x])
        {
            if (ch[x][0])
                swap(ch[ch[x][0]][0], ch[ch[x][0]][1]), tag[ch[x][0]] ^= 1;
            if (ch[x][1])
                swap(ch[ch[x][1]][0], ch[ch[x][1]][1]), tag[ch[x][1]] ^= 1;
            tag[x] = 0;
        }
    }
    // 从头递归，从上倒下下传所有懒标记
    void update(int x)
    {
        if (!isroot(x))
            update(fa[x]);
        pushdown(x);
    }
    void rotate(int x)
    {
        int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y))
            ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
        // y当前是子树，修正y的异或和
        pushup(y);
        // y现在是x的孩子，修改x的异或和
        pushup(x);
    }

    // 将x旋转至整个splay树的定点
    void splay(int x)
    {
        // x所在的路径的所有懒标记下传，该交换的交换
        update(x);
        int f;
        // while 保证x一定可以旋转到根节点位置
        while (!isroot(x))
        {
            f = fa[x];
            if (!isroot(f))
                rotate(getch(x) == getch(f) ? f : x);
            rotate(x);
        }
    }
    // 访问节点x，并且将根节点到x节点之间所有的路径变为实边
    void access(int x)
    {
        // 将最后一个点的右儿子变为0，即变为虚边
        int son = 0;
        while(x){
            // 将x转换为当前树的树根
            splay(x);
            // 将x的右儿子设置为前一棵splay树的树根
            ch[x][1] = son;
            // x的孩子发生变化，上传信息
            pushup(x);
            // son 保存当前splay树树根，x是其父节点
            x = fa[son = x];
        }
        
    }
    // 将原来的树中x节点作为根节点
    void makeroot(int x)
    {
        access(x);
        // splay(x) 之后x在这个树的最右下角 
        splay(x);
        // 交换x的左孩子节点和右孩子节点
        swap(ch[x][0], ch[x][1]);
        // 进行懒人标记，不再递归的进行翻转
        tag[x] ^= 1;
    }

    // 寻找x节点在原树的根节点
    int findRoot(int x)
    {
        access(x);
        splay(x);
        // 最左边的一定是根节点
        while (ch[x][0])
        {
            // 下传懒标记
            pushdown(x);
            x = ch[x][0];
        }
        // 对根节点进行splay，保证时间复杂度
        splay(x);
        return x;
    }

    // 将x和y之间建立连接
    void link(int y, int x)
    {
        makeroot(x);
        // 如果是同一个点，或者x和y已经连通，则跳过
        if (x == y || findRoot(x) == findRoot(y))
            return;
        fa[x] = y;
    }

    // 断开x 和 y 之间的连接
    void cut(int x, int y)
    {
        // makeroot(x)之后y的深度比x高，x一定在y的右边
        makeroot(x);
        // 如果y和x不在一棵树上，或者x和y之间不邻接(y的父亲不是x 或者y有左儿子)，不进行cut
        if (findRoot(y) != x || fa[y] != x || ch[y][0])
            return;
        fa[y] = ch[x][1] = 0;
        update(x);
    }
 
    // 把x到y的路径拆成一棵方便的Splay树
    void split(int x, int y)
    {
        // 如果x和y根本不在同一条路径上，则跳过
        if (findRoot(x) != findRoot(y))
            return;
        makeroot(x);
        access(y);
        splay(y);
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    LCTree lct;
    for(int i = 1; i <=n; ++i){
        int v;
        scanf("%d", &v);
        lct.val[i] = v;
    }
    while (m--)
    {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        if(op == 0){
            lct.split(x, y);
            printf("%d\n", lct.sum[y]);
        }

        if (op == 1)
        {
            lct.link(y, x);
        }
        if (op == 2)
        {
            lct.cut(y, x);
        }
        if (op == 3)
        {
            lct.splay(x);
            lct.val[x] = y;
            lct.pushup(x);
        }
    }
    return 0;
}