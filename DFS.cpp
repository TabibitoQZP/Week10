#include <cstdio>
#include <vector>

using namespace std;

void dfs(vector<int> *tr, vector<int> &dfsN, vector<int> &deepest, int &c, int rt)
{
    dfsN[rt] = c;
    int i, len = tr[rt].size();
    for (i = 0; i < len; i++)
    {
        c++;
        dfs(tr, dfsN, deepest, c, tr[rt][i]);
    }
    deepest[rt] = c;
}

int main()
{
    int i, n, q, tmp, u, k, c = 1;
    scanf("%d%d", &n, &q);
    vector<int> *trees = new vector<int>[n + 1];
    vector<int> dfsNum(n + 1, 0), numNode(n + 1, 0), deepest(n + 1, 0);
    for (i = 2; i <= n; i++)
    {
        scanf("%d", &tmp);
        trees[tmp].push_back(i);
    }
    dfs(trees, dfsNum, deepest, c, 1);
    for (i = 1; i <= n; i++)
    {
        numNode[dfsNum[i]] = i;
    }
    for (i = 0; i < q; i++)
    {
        scanf("%d%d", &u, &k);
        tmp = dfsNum[u];
        tmp += k - 1;
        if (tmp > deepest[u])
        {
            printf("-1\n");
        }
        else
        {
            if (numNode[tmp] < u)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n", numNode[tmp]);
            }
        }
    }
    return 0;
}