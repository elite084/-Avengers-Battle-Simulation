/*
 * Quantum Nanotech Suit (QNS) Management System
 * ---------------------------------------------
 * Simulation of a battle scenario between Avengers and enemies using object-oriented principles.
 * Demonstrates concepts such as:
 * - Classes and encapsulation
 * - Operator overloading
 * - Function overloading
 * - Inheritance-like behavior via composition
 * - Real-time suit upgrade, attack, defense, and battle state management
 */

#include <iostream>
#include <vector>
using namespace std;

// Quantum Nanotech Suit class
class QNS {
private:
    int P, D, E, H;  // Power, Durability, Energy, Heat

public:
    // Constructors
    QNS(int P, int D, int E, int H) {
        this->P = min(P, 5000);     // Cap power at 5000
        this->D = D;
        this->E = E;
        this->H = max(H, 0);        // Ensure non-negative heat
    }

    // Copy constructor
    QNS(const QNS& qns) {
        P = min(qns.P, 5000);
        D = qns.D;
        E = qns.E;
        H = max(qns.H, 0);
    }

    // Default constructor
    QNS() {
        P = 1000;
        D = 500;
        E = 300;
        H = 0;
    }

    // Operator Overloading for Suit Merging and Operations

    // Merge two suits: energy and power exchange
    QNS operator+(const QNS& qns) {
        QNS temp = *this;
        temp.P += qns.E;
        temp.D += qns.D;
        temp.E += qns.P;
        temp.P = min(temp.P, 5000);  // Cap power
        return temp;
    }

    // Attack reduces durability, increases energy and heat
    QNS operator-(int X) {
        QNS temp = *this;
        temp.D -= X;
        temp.E += X;
        temp.H += X;
        return temp;
    }

    // Boost power based on percentage, increases energy and heat
    QNS operator*(int X) {
        QNS temp = *this;
        temp.P = temp.P + ((temp.P * X) / 100);
        temp.E = temp.E + (5 * X);
        temp.H = temp.H + X;
        temp.P = min(temp.P, 5000);
        return temp;
    }

    // Repair suit: restore durability and reduce heat
    QNS operator/(int X) {
        QNS temp = *this;
        temp.D += X;
        temp.E = E;
        temp.H -= X;
        temp.H = max(temp.H, 0);  // Avoid negative heat
        return temp;
    }

    // Function Overloading

    // Boost power by a factor (uses * operator internally)
    QNS& boostPower(int factor) {
        *this = *this * factor;
        return *this;
    }

    // Boost power by merging with another suit
    QNS& boostPower(QNS& otherSuit) {
        *this = *this + otherSuit;
        if (P > 5000) setP(5000);
        return *this;
    }

    // Comparison Operators

    // Equality check (based on power and durability)
    bool operator==(QNS& qns) {
        return (P == qns.P && D == qns.D);
    }

    // Comparison based on total score
    bool operator<(QNS& qns) {
        return (P + D) < (qns.P + qns.D);
    }

    // Utility Checks
    bool isOverheated() { return H > 500; }
    bool isDestroyed() { return D <= 0; }

    // Getters and Setters
    int getP() { return P; }
    int getD() { return D; }
    int getE() { return E; }
    int getH() { return H; }

    void setP(int X) { P = X; }
    void setD(int X) { D = X; }
    void setE(int X) { E = X; }
    void setH(int X) { H = X; }
};

// Avenger class
class Avenger {
private:
    string name;
    QNS suit;
    int AS;  // Attack strength

public:
    Avenger(string avName, QNS& avSuit, int strength)
        : name(avName), suit(avSuit), AS(strength) {}

    // Attack another Avenger
    QNS& attack(Avenger& enemy) {
        if (!suit.isOverheated() && !suit.isDestroyed()) {
            if (!enemy.suit.isDestroyed())
                enemy.suit = enemy.suit - AS;
        }
        return enemy.suit;
    }

    // Upgrade suit by merging with another
    QNS& upgradeSuit(QNS& qns) {
        suit = suit + qns;
        return suit;
    }

    // Repair the suit
    QNS& repair(int x) {
        suit = suit / x;
        return suit;
    }

    // Display suit status
    void printStatus() {
        cout << name << " " << suit.getP() << " " << suit.getD() << " "
             << suit.getE() << " " << suit.getH() << endl;
    }

    // Accessors and Mutators
    QNS& getSuit() { return suit; }
    string getName() { return name; }

    // Boost power operations
    QNS& boostPower(int X) { return suit.boostPower(X); }
    QNS& boostPower(QNS& otherSuit) { return suit.boostPower(otherSuit); }

    // Return the score of the Avenger (for battle result)
    int score() {
        return suit.getP() + suit.getD();
    }
};

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
