#include "Avenger.cpp"

// Battle class to simulate the battle
class Battle {
private:
    vector<Avenger> heroes, enemies;
    vector<string> battleLog;

public:
    // Add heroes and enemies
    void add_hero(Avenger& h) { heroes.push_back(h); }
    void add_enemy(Avenger& e) { enemies.push_back(e); }

    // Repair a hero's suit
    void repair(string name, int X) {
        for (Avenger& hero : heroes) {
            if (hero.getName() == name) {
                hero.repair(X);
                battleLog.push_back(name + " repaired");
                return;
            }
        }
    }

    // Perform an attack between two Avengers
    void attack(string name1, string name2) {
        // Hero attacking enemy
        for (Avenger& h : heroes) {
            if (h.getName() == name1) {
                for (Avenger& e : enemies) {
                    if (e.getName() == name2) {
                        h.attack(e);
                        battleLog.push_back(name1 + " attacks " + name2);
                        if (e.getSuit().isDestroyed())
                            battleLog.push_back(name2 + " suit destroyed");
                        else if (e.getSuit().isOverheated())
                            battleLog.push_back(name2 + " suit overheated");
                        return;
                    }
                }
            }
        }

        // Enemy attacking hero
        for (Avenger& e : enemies) {
            if (e.getName() == name1) {
                for (Avenger& h : heroes) {
                    if (h.getName() == name2) {
                        e.attack(h);
                        battleLog.push_back(name1 + " attacks " + name2);
                        if (h.getSuit().isDestroyed())
                            battleLog.push_back(name2 + " suit destroyed");
                        else if (h.getSuit().isOverheated())
                            battleLog.push_back(name2 + " suit overheated");
                        return;
                    }
                }
            }
        }

        // Friendly fire (heroes attacking heroes or enemies attacking enemies)
        for (Avenger& a1 : heroes) {
            if (a1.getName() == name1) {
                for (Avenger& a2 : heroes) {
                    if (a2.getName() == name2) {
                        a1.attack(a2);
                        battleLog.push_back(name1 + " attacks " + name2);
                        if (a2.getSuit().isDestroyed())
                            battleLog.push_back(name2 + " suit destroyed");
                        else if (a2.getSuit().isOverheated())
                            battleLog.push_back(name2 + " suit overheated");
                        return;
                    }
                }
            }
        }

        for (Avenger& a1 : enemies) {
            if (a1.getName() == name1) {
                for (Avenger& a2 : enemies) {
                    if (a2.getName() == name2) {
                        a1.attack(a2);
                        battleLog.push_back(name1 + " attacks " + name2);
                        if (a2.getSuit().isDestroyed())
                            battleLog.push_back(name2 + " suit destroyed");
                        else if (a2.getSuit().isOverheated())
                            battleLog.push_back(name2 + " suit overheated");
                        return;
                    }
                }
            }
        }
    }

    // Boost power by percentage
    void boostpowerbyfactor(string name, int y) {
        for (Avenger& h : heroes) {
            if (h.getName() == name) {
                h.boostPower(y);
                battleLog.push_back(name + " boosted");
                if (h.getSuit().isOverheated())
                    battleLog.push_back(name + " suit overheated");
                return;
            }
        }
        for (Avenger& e : enemies) {
            if (e.getName() == name) {
                e.boostPower(y);
                battleLog.push_back(name + " boosted");
                if (e.getSuit().isOverheated())
                    battleLog.push_back(name + " suit overheated");
                return;
            }
        }
    }

    // Boost power using another suit
    void boostpower(string name, QNS& otherSuit) {
        for (Avenger& h : heroes) {
            if (h.getName() == name) {
                h.boostPower(otherSuit);
                battleLog.push_back(name + " boosted");
                if (h.getSuit().isOverheated())
                    battleLog.push_back(name + " suit overheated");
                return;
            }
        }
        for (Avenger& e : enemies) {
            if (e.getName() == name) {
                e.boostPower(otherSuit);
                battleLog.push_back(name + " boosted");
                if (e.getSuit().isOverheated())
                    battleLog.push_back(name + " suit overheated");
                return;
            }
        }
    }

    // Print current status of an Avenger
    void printStatus(string name) {
        for (Avenger& h : heroes)
            if (h.getName() == name) return h.printStatus();
        for (Avenger& e : enemies)
            if (e.getName() == name) return e.printStatus();
    }

    // Upgrade a suit from available pool
    void upgradeSuit(string name, QNS& q) {
        for (Avenger& h : heroes) {
            if (h.getName() == name) {
                h.upgradeSuit(q);
                battleLog.push_back(name + " upgraded");
                return;
            }
        }
        for (Avenger& e : enemies) {
            if (e.getName() == name) {
                e.upgradeSuit(q);
                battleLog.push_back(name + " upgraded");
                return;
            }
        }
    }

    // Start the full battle simulation
    void startBattle(vector<QNS>& suits, int k, int n, int m) {
        int noA = n + m;
        string command;
        while (cin >> command && command != "End") {
            if (command == "Attack") {
                string a, b; cin >> a >> b;
                attack(a, b);
            } else if (command == "Repair") {
                string name; int X; cin >> name >> X;
                repair(name, X);
            } else if (command == "BoostPowerByFactor") {
                string name; int y; cin >> name >> y;
                boostpowerbyfactor(name, y);
            } else if (command == "BoostPower") {
                string name; int P, D, E, H;
                cin >> name >> P >> D >> E >> H;
                QNS otherSuit(P, D, E, H);
                boostpower(name, otherSuit);
            } else if (command == "AvengerStatus") {
                string name; cin >> name;
                printStatus(name);
            } else if (command == "Upgrade") {
                string name; cin >> name;
                if (noA < k) {
                    upgradeSuit(name, suits[noA]);
                    noA++;
                } else {
                    battleLog.push_back(name + " upgrade Fail");
                }
            } else if (command == "PrintBattleLog") {
                printBattleLog();
            } else if (command == "BattleStatus") {
                int res = Result();
                if (res == 1) cout << "heroes are winning" << endl;
                else if (res == -1) cout << "enemies are winning" << endl;
                else cout << "tie" << endl;
            }
        }
    }

    // Print all logged battle events
    void printBattleLog() {
        for (string& s : battleLog) {
            cout << s << endl;
        }
    }

    // Compute who is winning based on scores
    int Result() {
        int hs = 0, es = 0;
        for (Avenger& h : heroes) if (!h.getSuit().isDestroyed()) hs += h.score();
        for (Avenger& e : enemies) if (!e.getSuit().isDestroyed()) es += e.score();
        return (hs > es) ? 1 : (hs < es ? -1 : 0);
    }
};
