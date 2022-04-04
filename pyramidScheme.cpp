#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_map<int, vector<int>> links;

// An utility function to add an edge in the tree
void addEdge(vector<int> adj[], int x, int y)
{
    adj[x].push_back(y);
    adj[y].push_back(x);
}

void dfs(vector<int> adj[], vector<int> dp[], int src, int par)
{
    for (auto child : adj[src])
    {
        if (child != par)
            dfs(adj, dp, child, src);
    }

    for (auto child : adj[src])
    {
        if (child != par)
        {
            // not including source in the vertex cover
            dp[src][0] += dp[child][1];

            // including source in the vertex cover
            dp[src][1] += min(dp[child][1], dp[child][0]);
        }
    }
}

// function to find minimum size of vertex cover
void minSizeVertexCover(vector<int> adj[], int N)
{
    vector<int> dp[N + 1];

    for (int i = 1; i <= N; i++)
    {
        // 0 denotes not included in vertex cover
        dp[i].push_back(0);

        // 1 denotes included in vertex cover
        dp[i].push_back(1);
    }

    dfs(adj, dp, 1, -1);

    // printing minimum size vertex cover
    cout << min(dp[1][0], dp[1][1]) << endl;
}

/*
// Driver Code
int main()
{
    // number of nodes in the tree
    int N = 8;

    // adjacency list representation of the tree
    vector<int> adj[N + 1];

    addEdge(adj, 1, 2);
    addEdge(adj, 1, 7);
    addEdge(adj, 2, 3);
    addEdge(adj, 2, 6);
    addEdge(adj, 3, 4);
    addEdge(adj, 3, 8);
    addEdge(adj, 3, 5);

    minSizeVertexCover(adj, N);

    return 0;
}
*/

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line))
    {
        if (line.empty())
            break;

        vector<int> nums;

        string num;
        for (int i = 0; i < (int)line.size(); i++)
        {
            if (line[i] == ' ' || (i + 1 == (int)line.size() - 1 && line[i + 1] == ' '))
            {
                nums.push_back(stoi(num));
                num = "";
                continue;
            }
            num += line[i];
        }

        if (nums[0] == -1)
        {
            // chama a funcao e reseta o dicionario
            // minSizeVertexCover(, links.size());
            for (auto &i : links)
            {
                cout << "(" << i.first << ")" << " ";
                for (auto &j : i.second)
                    cout << j << " ";
                cout << endl;
            }
            cout << endl;
            links.clear();
            continue;
        }

        for (int i = 1; i < (int)nums.size(); ++i)
        {
            if (links.find(nums[0]) == links.end())
                links[nums[0]] = {nums[i]}; // cria uma key com o no e define as suas ligacoes como values
            else
                links[nums[0]].push_back(nums[i]);
        }

        /*// print do dicionario
        for (auto &i: links)
        {
            cout << "(" << i.first << ")" << " ";
            for (auto &j : i.second)
                cout << j << " ";
            cout << endl;
        }*/
    }

    return 0;
}