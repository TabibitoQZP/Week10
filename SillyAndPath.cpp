#include <cstdio>
#include <vector>

using namespace std;

struct tree
{
    int crossTime;
    vector<int> next;
    tree() : crossTime(0) {}
};

void dfs(vector<tree>& trees,int a,int b)
{
    
}

int main()
{
    int i, n, tmp0, tmp1, k; // number of cities, k sillies.
    scanf("%d", &n);
    vector<tree> trees(n+1);
    for(i=1;i<n;i++)
    {
        scanf("%d%d",&tmp0,&tmp1);
        trees[tmp0].next.push_back(tmp1);
        trees[tmp1].next.push_back(tmp0);
    }
    scanf("%d", &k);
    for (i = 0; i < k; i++)
    {
        scanf("%d%d",&tmp0,&tmp1);
    }
}