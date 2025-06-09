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