#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// dicionario de nos
// as keys sao os nos e os values um array com os nos que se ligam a essa key e o custo da key
unordered_map<int, vector<int>> links;

void dfs(vector<int> dp[], int src, int par)
{
    for (int i = 0; i < (int)links[src].size() - 1; i++)
    {
        if (links[src][i] != par)
            dfs(dp, links[src][i], src);
    }

    for (int i = 0; i < (int)links[src].size() - 1; i++)
    {
        if (links[src][i] != par)
        {
            dp[src][0] += dp[links[src][i]][1];
            dp[src][1] += min(dp[links[src][i]][1], dp[links[src][i]][0]);
        }
    }
}

void minCover(int N)
{
    vector<int> dp[N];

    for (int i = 0; i < N; i++)
    {
        dp[i].push_back(0);
        dp[i].push_back(1);
    }

    dfs(dp, 1, -1);

    cout << min(dp[1][0], dp[1][1]) << endl;
}

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

        if (line.find("-1") != string::npos)
        {
            // chama a funcao com o numero de nos como argumento
            minCover(links.size());
            links.clear();
            continue;
        }

        int space = 0;
        int key = -1;
        for (int i = 0; i < (int)line.size(); i++)
        {
            if (i == (int)line.size() - 1)
            {
                num += line[i];
                links[key].insert(links[key].end(), nums.begin(), nums.end());
                links[key].push_back(stoi(num));
                num = "";
                continue;
            }

            if (line[i] == ' ' && space == 0)
            {
                key = stoi(num);
                num = "";
                space = 1;
                continue;
            }

            if (line[i] == ' ' && space != 0)
            {
                nums.push_back(stoi(num));
                links[stoi(num)] = {key};
                num = "";
                continue;
            }
            num += line[i];
        }
    }

    return 0;
}