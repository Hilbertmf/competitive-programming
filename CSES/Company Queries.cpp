// https://cses.fi/problemset/task/1687/
// O(q * log(n) + n*log(n))
// Solution using Binary Lifting
#include <bits/stdc++.h>
using namespace std;
 
int dfs(int root, vector<vector<int>>& tree, int d,
vector<int>& depth) {
    depth[root] = d;
    int curr = d;
    for(auto &adj : tree[root]) {
        curr = max(curr, dfs(adj, tree, d + 1, depth));
    }
    return curr;
}
 
int getDepth(int root, vector<int>& par, vector<int>& depth) {
    int n = par.size();
    vector<vector<int>> tree(n);
    for(int i = 1; i < n; ++i) {
        tree[par[i]].push_back(i);
    }
    return dfs(root, tree, 0, depth);
}
 
int getLOG(int depth) {
    int LOG = 0;
    while ((1 << LOG) < depth) {
        LOG++;
    }
    return LOG;
}
 
int goUp(int x, int k, vector<vector<int>>& anc, int LOG) {
    for(int i = LOG - 1; i >= 0; --i) {
        if ((1 << i) <= k) {
            k -= (1 << i);
            x = anc[x][i];
        }
    }
    return x;
}
 
int main()  {
 
    int n, q;
    cin >> n >> q;
    vector<int> par(n);
    par[0] = 0;
    for(int i = 1; i < n; ++i) {
        int boss;
        cin >> boss;
        boss--;
        par[i] = boss;
    }
 
    vector<int> depth(n);
    int d = getDepth(0, par, depth);
    int LOG = getLOG(d) + 1;
    vector<vector<int>> anc(n, vector<int>(LOG));
 
    for(int i = 0; i < n; ++i) {
        anc[i][0] = par[i];
    }
 
    for(int j = 1; j < LOG; ++j) {
        for(int i = 1; i < n; ++i) {
            anc[i][j] = anc[ anc[i][j - 1] ][j - 1];
        }
    }
 
    while (q--) {
        int x, k;
        cin >> x >> k;
        x--;
        
        if(k > depth[x]) {
            cout << "-1\n";
        }
        else {
            cout << goUp(x, k, anc, LOG) + 1 << "\n";
        }
    }
 
    return 0;
}
