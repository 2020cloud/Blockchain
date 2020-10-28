#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <memory>
#include <cctype>
using namespace std;


struct TreeNode
{
    static int n;
    static int n0;

    int left, right, endpoint, power, weight, index;
    char candidate;
    vector<shared_ptr<TreeNode>> child;
    TreeNode(const int w) : weight(w),candidate('0')
    {
    }
    void insert(shared_ptr<TreeNode> node)
    {
        child.push_back(node);
    }
};

int TreeNode::n = 0;
int TreeNode::n0 = 0;

shared_ptr<TreeNode> constructDelegateGraph()
{
    int w = 1;
    auto root1 = make_shared<TreeNode>(w++);
    auto root2 = make_shared<TreeNode>(w++);
    auto root3 = make_shared<TreeNode>(w++);
    auto root4 = make_shared<TreeNode>(w++);
    auto root5 = make_shared<TreeNode>(w++);
    auto root6 = make_shared<TreeNode>(w++);
    auto root7 = make_shared<TreeNode>(w++);
    auto root8 = make_shared<TreeNode>(w++);
    auto root9 = make_shared<TreeNode>(w++);
    auto root10 = make_shared<TreeNode>(w++);
    auto root11 = make_shared<TreeNode>(w++);
    auto root12 = make_shared<TreeNode>(w++);
    root1->insert(root2);
    root1->insert(root9);
    root2->insert(root3);
    root3->insert(root4);
    root3->insert(root7);
    root4->insert(root5);
    root5->insert(root6);
    root7->insert(root8);
    root9->insert(root10);
    root9->insert(root11);
    root9->insert(root12);
    return root1;
}
// index left, right, endpoint, power, weight,
void printDetail(shared_ptr<TreeNode> root)
{
    static int n = 0;
    if (n == 0)
    {
        printf("index left right edpot power weght\n");
        n++;
    }
    printf("%d   %d   %d   %d   %d   %d\n", root->index, root->left, root->right, root->endpoint, root->power, root->weight);
    for (auto &node : root->child)
        printDetail(node);
}

unordered_map<int, int> lazy_1, lazy_2, s, nearestparent;
// 候选人的得票数
unordered_map<char, int> C;
// index对应的节点
map<int, shared_ptr<TreeNode>> b;

/*
Algorithm 1: Procedure of Preorder(root)
*/
void preorder(shared_ptr<TreeNode> root)
{
    root->left = ++root->n0;
    root->index = ++root->n;
    root->power = root->weight;
    for (auto &node : root->child)
    {
        preorder(node);
        root->power += node->power;
    }
    root->endpoint = root->n;
    root->right = ++root->n0;
    b[root->index] = root;
}

/* 
    Algorithm4: Procedure of FAULVP(L, R, l,r, k, v),
    which is to find and update the note’s lost voting power
Input: [L, R], which is the interval to be updated
Input: [l, r], which is the current interval of the interval tree node
Input: k, which is the index of interval tree node
Input: v, which is the value for updating.
*/
void FAULVP(int L, int R, int l, int r, int k, int v)
{
    if (L == l && R == r)
    {
        lazy_2[k] += v;
        if (L == R)
            s[L] = lazy_2[k];
    }
    else
    {
        const int m = (l + r) / 2;
        lazy_2[2 * k] += lazy_2[k];
        lazy_2[2 * k + 1] += lazy_2[k];
        lazy_2[k] = 0;
        if (L <= m)
            FAULVP(L, min(m, R), l, m, 2 * k, v);
        if (R > m)
            FAULVP(max(m + 1, L), R, m + 1, r, 2 * k + 1, v);
    }
}

/*
    Algorithm 3: Procedure of FAUNVP(L, R,l,r, k, v),
    which is to find and update the node’s nearest
    voted parent
*/
void FAUNVP(int L, int R, int l, int r, int k, int v)
{
    if (L == l && R == r)
    {
        if (v > lazy_1[k])
            lazy_1[k] = v;
        if (L == R)
            nearestparent[L] = lazy_1[k];
    }
    else
    {
        const int m = (l + r) / 2;
        if (lazy_1[2 * k] < lazy_1[k])
            lazy_1[2 * k] = lazy_1[k];
        if (lazy_1[2 * k + 1] < lazy_1[k])
            lazy_1[2 * k + 1] = lazy_1[k];
        if (L <= m)
            FAUNVP(L, min(m, R), l, m, 2 * k, v);
        if (R > m)
            FAUNVP(max(m + 1, L), R, m + 1, r, 2 * k + 1, v);
    }
}

/*
Algorithm 2: Procedure of Vote, upon receiving a voting message
*/
void vote(shared_ptr<TreeNode> node)
{
    b[node->index] = node;
    FAULVP(node->left, node->left, 1, 2 * node->n, 1, 0);
    FAULVP(node->right, node->right, 1, 2 * node->n,1, 0);
    const int t = node->power - s[node->left] + s[node->right];
    C[node->candidate] += t;
    printf("candidate: %c, get voting ticktes: %d \n", node->candidate, C[node->candidate]);
    FAUNVP(node->index, node->index, 1, node->n, 1, 0);
    const shared_ptr<TreeNode> parent = b[nearestparent[node->index]];
    if( parent!= nullptr){
        const char ca = parent->candidate;
        C[ca] -= t;
        printf("candidate: %c reduces %d tickets, now: %d \n",ca, t, C[ca]);
        FAULVP(parent->left, node->left, 1, node->n0, 1, t);
    }
    FAUNVP(node->index + 1, node->endpoint, 1, node->n, 1, node->index);
}

int main()
{
    auto root = constructDelegateGraph();
    preorder(root);
    printDetail(root);
    b[5]->candidate = 'B';  // 5号向B投票
    vote(b[5]);
    b[3]->candidate = 'C';
    vote(b[3]);
    b[1]->candidate = 'A';
    vote(b[1]);
    return 0;
}