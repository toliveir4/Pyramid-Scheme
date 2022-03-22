#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <valarray>

using namespace std;

map<int, vector<int>> links;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;

        vector<int> nums;

        string num;
        for (int i = 0; i < (int) line.size(); i++) {
            if (line[i] == ' ' || i == (int) line.size() - 1) {
                nums.push_back(stoi(num));
                num = "";
                continue;
            }
            num += line[i];
        }

        if (nums[0] == -1) {
            //chama a funcao e reseta o dicionario


            links.clear();
            continue;
        }

        for (int i = 1; i < (int) nums.size(); ++i) {
            if (links.find(nums[0]) == links.end())
                links[nums[0]] = {nums[i]}; // cria uma key com o no e define as suas ligacoes como values
            else links[nums[0]].push_back(nums[i]);
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