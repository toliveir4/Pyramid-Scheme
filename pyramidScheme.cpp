#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Member {
public:
    int cost;   // custo do no
    int totalCost;  // custo acumulado ate ao no
    int vertexCover;
    vector<int> recruits; // lista de recrutados

    explicit Member(int cost) {
        this->cost = cost;
        totalCost = 0;
        vertexCover = 0;
    }
};

// dicionario em que a key e o id do no e o value um ponteiro para o no
unordered_map<int, Member*> members;

// escolhe a melhor opcao consoante o valor minimo de vertices e, no caso de empate, o custo maximo
void checkBestOption(Member* m, int sizeWith, int totalCostWith, int sizeWithout, int totalCostWithout) {
    if (sizeWithout < sizeWith) {
        m->vertexCover = sizeWithout;
        m->totalCost = totalCostWithout;
    }
    else if (sizeWith < sizeWithout) {
        m->vertexCover = sizeWith;
        m->totalCost = totalCostWith;
    }
    else {
        m->vertexCover = sizeWithout;
        m->totalCost = max(totalCostWith, totalCostWithout);
    }
}


pair<int, int> minSizeCover(Member* m) {
    // verifica se o no tem filhos
    if (m->recruits.empty())
        return { 0, 0 };

    // verifica se o no ja foi analizado, caso ja tenha sido
    // e retornado os valores atuais de modo a poupar tempo
    if (m->vertexCover != 0)
        return { m->vertexCover, m->totalCost };

    // caso em que a raiz e contada
    int sizeWith = 1;
    int totalCostWith = m->cost;

    for (auto& r : m->recruits) {
        pair<int, int> aux = minSizeCover(members[r]);
        sizeWith += aux.first;
        totalCostWith += aux.second;
    }

    // caso em que a raiz nao e contada
    int sizeWithout = 0;
    int totalCostWithout = 0;

    for (auto& r : m->recruits) {
        sizeWithout += 1;
        totalCostWithout += members[r]->cost;

        for (auto& rr : members[r]->recruits) {
            pair<int, int> aux = minSizeCover(members[rr]);
            sizeWithout += aux.first;
            totalCostWithout += aux.second;
        }
    }

    checkBestOption(m, sizeWith, totalCostWith, sizeWithout, totalCostWithout);

    return { m->vertexCover, m->totalCost };
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;

    while (getline(cin, line)) {
        if (line.empty())
            break;

        vector<int> nums;

        string num;

        if (line.find("-1") != string::npos) {
            // chama a funcao com a raiz
            pair<int, int> best = minSizeCover(members[0]);
            cout << best.first << " " << best.second << endl;
            members.clear();
            continue;
        }

        int space = 0;
        int key = -1;
        for (int i = 0; i < (int)line.size(); i++) {
            if (i == (int)line.size() - 1) {
                num += line[i];
                auto* m = new Member(stoi(num));
                m->recruits = nums;
                members[key] = m;
                num = "";
                continue;
            }

            if (line[i] == ' ' && space == 0) {
                key = stoi(num);
                num = "";
                space = 1;
                continue;
            }

            if (line[i] == ' ' && space != 0) {
                nums.push_back(stoi(num));
                num = "";
                continue;
            }

            num += line[i];
        }
    }

    return 0;
}