#include "QNS.cpp"

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