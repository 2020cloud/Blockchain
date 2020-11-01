#include <cstdio>
const int N = 100005;
// reference: https://oi-wiki.org/ds/splay/
// rt 代表根节点编号
// nodeCnt 表示节点数量
// fa表示父亲数组
// ch表示孩子数组
// val 表示值
// cnt 表示权值出现次数
// sz 子树大小
int rt, nodeCnt, fa[N], ch[N][2], val[N], cnt[N], sz[N];
struct SplayTree
{
    // 更新x的size
    void maintain(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; }
    // 判断x是左孩子还是右孩子
    bool get(int x) { return x == ch[fa[x]][1]; }
    // 销毁x
    void clear(int x)
    {
        ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = cnt[x] = 0;
    }
    // 对x进行旋转,本质是将某个节点上移一个位置
    void rotate(int x)
    {
        int y = fa[x], z = fa[y], chk = get(x);
        // chk == 0 是左孩子， chk == 1 是右孩子
        // // 左孩子右旋
        // if(chk == 0){
        //     // x的右孩子成为y的左孩子
        //     ch[y][chk] = ch[x][chk^1];
        //     // x的右孩子成为y
        //     ch[x][chk ^ 1] = y;
        //     // x右孩子的父节点为y
        //     fa[ch[x][chk ^ 1]] = y;
        //     // y的父节点为x
        //     fa[y] = x;
        //     // x的父节点变为z
        //     fa[x] = z;
        //     // 更新z的孩子节点
        //     if(z)
        //         ch[z][y == ch[z][1]] == x;
        // }
        // // 右孩子左旋
        // else{
        //     // x的左孩子成为y的右孩子
        //     ch[y][chk] = ch[x][chk^1];
        //     // x的左孩子成为y
        //     ch[x][chk ^ 1] = y;
        //     // x左孩子的父节点为y
        //     fa[ch[x][chk ^ 1]] = y;
        //     // y的父节点为x
        //     fa[y] = x;
        //     // x的父节点变为z
        //     fa[x] = z;
        //     // 更新z的孩子节点
        //     if(z)
        //         ch[z][y == ch[z][1]] == x;
        // }
        ch[y][chk] = ch[x][chk ^ 1];
        fa[ch[x][chk ^ 1]] = y;
        ch[x][chk ^ 1] = y;
        fa[y] = x;
        fa[x] = z;
        if (z)
            ch[z][y == ch[z][1]] = x;
        maintain(x);
        maintain(y);
    }
    // 进行伸展
    void splay(int x)
    {
        // for循环最后rotate(x),
        for (int f = fa[x]; f = fa[x], f; rotate(x)){
            if (fa[f]){
                // 如果x和y同方向，则先旋转y
                // 如果x和y不同方向，则先旋转x，
                rotate(get(x) == get(f) ? f : x);
            }
        }
        // 随后设定根节点为x
        rt = x;
    }

    // 插入值k
    void insert(int k)
    {
        // 如果是空树，则直接插入并退出
        if (!rt)
        {
            val[++nodeCnt] = k;
            cnt[nodeCnt]++;
            rt = nodeCnt;
            maintain(rt);
            return;
        }
        int cnr = rt, f = 0;
        while (1)
        {
            // 如果当前根节点权值为k, 增加当前节点的大小并更新节点和父亲的信息，并对其进行Splay操作。
            if (val[cnr] == k)
            {
                cnt[cnr]++;
                maintain(cnr);
                maintain(f);
                splay(cnr);
                break;
            }
            f = cnr;
            // 进入左子树或者右子树
            cnr = ch[cnr][val[cnr] < k];
            // 如果cnr为空，表明找到空位置，进行插入
            if (!cnr)
            {
                val[++nodeCnt] = k;
                cnt[nodeCnt]++;
                fa[nodeCnt] = f;
                ch[f][val[f] < k] = nodeCnt;
                // 维护当前节点
                maintain(nodeCnt);
                // 维护其父节点信息
                maintain(f);
                // 将当前节点放于头节点
                splay(nodeCnt);
                break;
            }
        }
    }
    // 查询k的排名
    int rank(int k)
    {
        int res = 0, cnr = rt;
        while (1)
        {
            if (k < val[cnr])
            {
                cnr = ch[cnr][0];
            }
            else
            {
                res += sz[ch[cnr][0]];
                if (k == val[cnr])
                {
                    splay(cnr);
                    return res + 1;
                }
                res += cnt[cnr];
                cnr = ch[cnr][1];
            }
        }
    }
    int kth(int k)
    {
        int cnr = rt;
        while (1)
        {
            if (ch[cnr][0] && k <= sz[ch[cnr][0]])
            {
                cnr = ch[cnr][0];
            }
            else
            {
                k -= cnt[cnr] + sz[ch[cnr][0]];
                if (k <= 0)
                {
                    splay(cnr);
                    return val[cnr];
                }
                cnr = ch[cnr][1];
            }
        }
    }
    // 查询当前树根的前驱
    int pre()
    {
        // 先找左子树，在往右子树转
        int cnr = ch[rt][0];
        while (ch[cnr][1])
            cnr = ch[cnr][1];
        splay(cnr);
        return cnr;
    }
    // 查询当前树根的后继
    int nxt()
    {
        int cnr = ch[rt][1];
        while (ch[cnr][0])
            cnr = ch[cnr][0];
        splay(cnr);
        return cnr;
    }
    void del(int k)
    {
        rank(k);
        if (cnt[rt] > 1)
        {
            cnt[rt]--;
            maintain(rt);
            return;
        }
        if (!ch[rt][0] && !ch[rt][1])
        {
            clear(rt);
            rt = 0;
            return;
        }
        if (!ch[rt][0])
        {
            int cnr = rt;
            rt = ch[rt][1];
            fa[rt] = 0;
            clear(cnr);
            return;
        }
        if (!ch[rt][1])
        {
            int cnr = rt;
            rt = ch[rt][0];
            fa[rt] = 0;
            clear(cnr);
            return;
        }
        int cnr = rt;
        int x = pre();
        fa[ch[cnr][1]] = x;
        ch[x][1] = ch[cnr][1];
        clear(cnr);
        maintain(rt);
    }
} tree;

int main()
{
    int n, m;
    scanf("%d %d", n, m);
    for (int i = 1; i <= n; ++i)
        tree.insert(i);
    while (m--)
    {
        int b, e;
        scanf("%d %d", b, e);
        for (int i = b; i <= e; ++i)
    }
    // int n, opt, x;
    // for (scanf("%d", &n); n; --n)
    // {
    //     scanf("%d%d", &opt, &x);
    //     if (opt == 1)
    //         tree.insert(x);
    //     else if (opt == 2)
    //         tree.del(x);
    //     else if (opt == 3)
    //         printf("%d\n", tree.rank(x));
    //     else if (opt == 4)
    //         printf("%d\n", tree.kth(x));
    //     else if (opt == 5)
    //         tree.insert(x), printf("%d\n", val[tree.pre()]), tree.del(x);
    //     else
    //         tree.insert(x), printf("%d\n", val[tree.nxt()]), tree.del(x);
    // }
    return 0;
}