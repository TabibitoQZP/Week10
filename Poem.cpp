/*
参考 https://blog.csdn.net/Meulsama/article/details/108588265
*/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct tree
{
    long long w;
    long long d;
    vector<tree *> next;
    tree(long long v) : w(v), d(0) {}
};

struct cmp
{
    bool operator()(tree *a, tree *b)
    {
        if (a->w > b->w)
            return true;
        else if (a->w == b->w)
            return a->d > b->d;
        return false;
    }
};

long long len = 0;
long long maxDeep = 0;

void dfs(tree *rt, long long depth)
{
    if (rt->w == 0)
        return;
    int vecLen = rt->next.size();
    if (vecLen == 0)
    {
        maxDeep = max(maxDeep, depth);
        len += depth * rt->w;
        return;
    }
    for (int i = 0; i < vecLen; i++)
    {
        dfs(rt->next[i], depth + 1);
    }
}

int main()
{
    int i, n, k;
    scanf("%d%d", &n, &k);
    int remain = (n - 1) % (k - 1);
    long long tmp;
    priority_queue<tree *, vector<tree *>, cmp> nums;
    tree *tmpTree;
    for (i = 0; i < n; i++)
    {
        scanf("%lld", &tmp);
        tmpTree = new tree(tmp);
        nums.push(tmpTree);
    }
    if (remain != 0)
    {
        tmp = k - 1 - remain;
        for (i = 0; i < tmp; i++)
        {
            tmpTree = new tree(0);
            nums.push(tmpTree);
        }
    }
    long long depth;
    while (nums.size() > 1)
    {
        tmp = 0;
        depth = 0;
        tmpTree = new tree(0);
        for (i = 0; i < k; i++)
        {
            tmp += nums.top()->w;
            depth = max(nums.top()->d, depth);
            tmpTree->next.push_back(nums.top());
            nums.pop();
        }
        tmpTree->w = tmp;
        tmpTree->d = depth + 1;
        nums.push(tmpTree);
    }
    dfs(tmpTree, 0);
    printf("%lld\n%lld", len, maxDeep);
    return 0;
}