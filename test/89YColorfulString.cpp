#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct tree
{
    int val;
    vector<tree *> next;
};

int deepest = 0, depth = 0;
tree *tail, *head;
multiset<int> ans;

void DfsForTail(tree *h, int pre)
{
    if (deepest < depth)
    {
        tail = h;
        deepest = depth;
    }
    for (int i = 0; i < h->next.size(); i++)
    {
        if (h->next[i]->val == pre)
        {
            continue;
        }
        depth++;
        DfsForTail(h->next[i], h->val);
        depth--;
    }
}

void dfs(tree *h, int pre)
{
    if (depth == deepest)
    {
        if (ans.find(h->val) == ans.end())
        {
            ans.insert(h->val);
        }
    }
    for (int i = 0; i < h->next.size(); i++)
    {
        if (h->next[i]->val == pre)
        {
            continue;
        }
        depth++;
        dfs(h->next[i], h->val);
        depth--;
    }
}

int main()
{
    int i, n, tmp;
    scanf("%d", &n);
    vector<tree *> trees(n + 1);
    vector<tree> treesStore(n);
    for (i = 1; i <= n; i++)
    {
        treesStore[i - 1].val = i;
        trees[i] = &treesStore[i - 1];
    }
    for (i = 2; i <= n; i++)
    {
        scanf("%d", &tmp);
        trees[tmp]->next.push_back(trees[i]);
        trees[i]->next.push_back(trees[tmp]);
    }
    int pre = 0;
    head = trees[1];
    while (head->next.size() > 1)
    {
        for (i = 0; i < head->next.size(); i++)
        {
            if (head->next[i]->val != pre)
            {
                pre = head->val;
                head = head->next[i];
                break;
            }
        }
    }
    tail = head;
    DfsForTail(head, 0);
    ans.insert(head->val);
    ans.insert(tail->val);
    depth = 0;
    dfs(head, 0);
    depth = 0;
    dfs(tail, 0);
    printf("%d", ans.size());
    return 0;
}