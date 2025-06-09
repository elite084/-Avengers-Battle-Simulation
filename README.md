# Avengers: Quantum Suit Battle Simulation

This project is a **C++ OOP-based battle simulation** featuring Avengers equipped with **Quantum Nanotech Suits (QNS)**. It models dynamic suit upgrades, overheating mechanics, and battle interactions using **polymorphism, operator overloading, and function overloading**.

---

## Objective

* Design a **Quantum Suit Management System** for Avengers using OOP.
* Implement **polymorphism**, **operator overloading**, and **function overloading**.
* Simulate real-time combat with suit upgrades and strategic actions.

---

## Background Story

    Tony Stark has created Quantum Nanotech Suits to prepare the Avengers for an intergalactic war. These suits adapt dynamically:
    
    - Absorb energy to upgrade power.
    - Reinforce armor to increase durability.
    - Overclock systems for high-damage output.
    - But excessive upgrades cause overheating and can disable the suit.


## Problem Description

    You will:
    
    1. Create and manage a list of Quantum Suits.
    2. Assign suits to Avengers.
    3. Simulate turn-based battle events.
    4. Maintain a battle log and handle all constraints.


## Class Definitions

### 1. `QNS` - Quantum Nanotech Suit

Represents an adaptive battle suit. Format: (P, D, E, H)

**Attributes:**

* `powerLevel (P)`: Default 1000
* `durability (D)`: Default 500
* `energyStorage (E)`: Default 300
* `heatLevel (H)`: Default 0

**Constructors:**

* Default, Parameterized, and Copy Constructor

**Operator Overloading:**

* `+` : Upgrades suit → (P1 + E2, D1 + D2, E1 + P2, H1)
* `-` : Damage → (P, D - X, E + X, H + X)
* `*` : Boost → (P + P\*X/100, D, E + 5X, H + X)
* `/` : Cool down → (P, D + X, E, max(H - X, 0))

**Function Overloading:**

* `boostPower(int factor)` → Increases power, increases heat
* `boostPower(QNS otherSuit)` → Transfers energy from other suit to boost durability

**Comparison Operators:**

* `==` → Same powerLevel & durability
* `<` → Based on (power + durability)

**Constraints:**

* `heatLevel > 500` → Overheated
* `durability <= 0` → Destroyed
* `powerLevel > 5000` → Cap at 5000

---

### 2. `Avenger`

Represents a hero with a QNS suit.

**Attributes:**

* `name`
* `QNS suit` (assigned in FCFS manner)
* `attackStrength`

**Methods:**

* `attack(enemy)` → Reduces enemy's durability by attackStrength
* `upgradeSuit()` → Uses extra suit to upgrade current one
* `repair(x)` → Cools down heat by x and increases durability
* `printStatus()` → Prints: `AvengerName P D E H`

**Constraints:**

* Overheated → cannot fight
* Destroyed → out of battle
* No suit → print: `X is out of fight`

---

### 3. `Battle`

Handles simulation logic.

**Attributes:**

* `heroes`: Vector of Avenger (size n)
* `enemies`: Vector of Avenger (size m)
* `battleLog`: Vector of strings

**Logged Events:**

* `"A attacks B"`
* `"B suit destroyed"` if D <= 0
* `"B suit overheated"` if H > 500
* `"X boosted"` → `"X suit overheated"` if H > 500
* `"X upgraded"` or `"X upgrade Fail"`
* `"X repaired"`

**Methods:**

* `startBattle()` → Initializes battle
* `printBattleLog()` → One log per line
* `Result()` → Compares total P + D of heroes vs enemies:

  * Returns 1 → Heroes win
  * Returns -1 → Enemies win
  * Returns 0 → Tie

---

