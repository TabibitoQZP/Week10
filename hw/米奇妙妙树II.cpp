#include <cstdio>
#include <vector>

using namespace std;

struct tree
{
    int val;
    int col;
    int colNum;
    tree *father;
    tree() : val(0), col(0), colNum(0), father(nullptr) {}
};

void backCol(tree *tr, int cl, int clNum)
{
    while (tr != nullptr)
    {
        if (tr->colNum > clNum)
            break;
        else
        {
            tr->col = cl;
            tr->colNum = clNum;
            tr = tr->father;
        }
    }
}

int main()
{
    int i, n, q, tmp;
    scanf("%d%d", &n, &q);
    vector<tree *> trees(n + 1);
    vector<tree> treesStore(n + 1);
    for (i = 1; i <= n; i++)
    {
        trees[i] = &treesStore[i];
        trees[i]->val = i;
    }
    for (i = 2; i <= n; i++)
    {
        scanf("%d", &tmp);
        trees[i]->father = trees[tmp];
    }
    vector<int> nodes(q + 1), cols(q + 1);
    for (i = 1; i <= q; i++)
    {
        scanf("%d%d", &nodes[i], &cols[i]);
    }
    for (i = q; i >= 1; i--)
    {
        backCol(trees[nodes[i]], cols[i], i);
    }
    for (i = 1; i <= n; i++)
    {
        printf("%d ", trees[i]->col);
    }
    return 0;
}