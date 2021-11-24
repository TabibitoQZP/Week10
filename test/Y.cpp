#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

#define M 2000050

using namespace std;

vector<int> trees[M];
int ans[M];
int head;
int deepest = 0;

void dfsForHead(int h, int pre, int depth)
{
    if (deepest < depth)
    {
        head = h;
        deepest = depth;
    }
    for (int i = 0; i < trees[h].size(); i++)
    {
        if (trees[h][i] == pre)
        {
            continue;
        }
        dfsForHead(trees[h][i], h, depth + 1);
    }
}

void dfs(int h, int pre, int depth)
{
    if (deepest == depth)
    {
        ans[h] = 1;
        head = h;
    }
    for (int i = 0; i < trees[h].size(); i++)
    {
        if (trees[h][i] == pre)
        {
            continue;
        }
        dfs(trees[h][i], h, depth + 1);
    }
}

int main()
{
    int i, n, tmp;
    scanf("%d", &n);
    for (i = 2; i <= n; i++)
    {
        scanf("%d", &tmp);
        trees[tmp].push_back(i);
        trees[i].push_back(tmp);
    }
    head = 1;
    int pre = 0;
    while (trees[head].size() > 1)
    {
        for (i = 0; i < trees[head].size(); i++)
        {
            if (trees[head][i] != pre)
            {
                pre = head;
                head = trees[head][i];
                break;
            }
        }
    }
    dfsForHead(head, 0, 0);
    ans[head] = 1;
    dfsForHead(head, 0, 0);
    ans[head] = 1;
    dfs(head, 0, 0);
    dfs(head, 0, 0);
    int ret = 0;
    for (i = 1; i <= n; i++)
    {
        if (ans[i] == 1)
        {
            ret++;
        }
    }
    printf("%d", ret);
    return 0;
}