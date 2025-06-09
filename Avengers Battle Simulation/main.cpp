#include "Battle.cpp"

// Main driver function
int main() {
    int k, n, m;
    cin >> k >> n >> m;
    vector<QNS> suits;

    // Input all suits
    for (int i = 0; i < k; i++) {
        int P, D, E, H;
        cin >> P >> D >> E >> H;
        P = min(5000, P);
        suits.emplace_back(P, D, E, H);
    }

    Battle battle;

    // Input Avengers (n heroes and m enemies)
    for (int i = 0; i < n + m; i++) {
        string name; int as;
        cin >> name >> as;
        if (i < n) {
            Avenger a(name, suits[i], as);
            battle.add_hero(a);
        } else if (i < k) {
            Avenger a(name, suits[i], as);
            battle.add_enemy(a);
        } else {
            cout << name << " is out of fight" << endl;
        }
    }

    // Start battle if input is correct
    string start;
    cin >> start;
    if (start == "BattleBegin") {
        battle.startBattle(suits, k, n, m);
    }

    return 0;
}
