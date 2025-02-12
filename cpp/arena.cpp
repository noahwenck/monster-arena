#include <iostream>
#include <typeinfo>
#include <vector>
// #include <cxxabi.h> todo: add to demangle type names


using namespace std;

enum Team {
    RED,
    BLUE
};

string getTeamName(Team team) {
    switch(team) {
        case RED: return "Red";
        case BLUE: return "Blue";
        default: return "Unknown";
    }
}

class Monster {
    public:
        const Team team;
        int health;
        const int damage;
        bool dead = false;

    public:
        Monster(Team team, int health, int damage) : team(team), health(health), damage(damage) {}

        virtual ~Monster() {}

        virtual void attack(Monster* target) {
            target->health -= damage;
            
            cout << printName() << " attacks " << getTeamName(target->team) << " "
            << typeid(target).name() << " for " << this->damage << endl;
            
            // Check for deaths for both monsters
            target->checkDeath();
            this->checkDeath();
        }

        void attackOrc(Monster* target, int damageBlocked, int damageReflected) {
            int dealedDamage = this->damage - damageBlocked;

            cout << printName() << " attacks " << getTeamName(target->team) << " " << typeid(target).name() << " for "
            << this->damage << " damage, dealing " << dealedDamage << " damage, and receiving "
            << damageReflected << " damage." << endl;

            target->health -= dealedDamage;
            this->health -= damageReflected;

            // Check for deaths for both monsters
            target->checkDeath();
            this->checkDeath();
        }

        void checkDeath() {
            if (health <= 0) {
                dead = true;
                cout << printName() << " has died." << endl;
            }
        }

        string printName() {
            return getTeamName(this->team) + " " + typeid(*this).name();
        }
};

class Orc : public Monster {
    public:
        const int damageBlocked = 2;
        const int damageReflected = 2;
    
    public:
        Orc(Team team) : Monster(team, 40, 4) {};

        ~Orc() override = default;
};

class Goblin : public Monster {
    private:
        const int numAttacks = 3;

    public:
        Goblin(Team team) : Monster(team, 20, 7) {};

        ~Goblin() override = default;

        void attack(Monster* target) override {
            Orc* orcTarget = NULL;
            if (dynamic_cast<Orc*>(target)) {
                orcTarget = (Orc*) target; 
            }

            int attackCount = 0;
            while (attackCount < numAttacks) {
                if (orcTarget != NULL) {
                    Monster::attackOrc(target, orcTarget->damageBlocked, orcTarget->damageReflected);
                } else {
                    Monster::attack(target);
                }
                attackCount++;
            }
        }
};

class Troll : public Monster {
    private:
        const int regen = 5;

        void regenerate() {
            cout << printName() << " regenerates " << regen << " health.";
            health += regen;
        }

    public:
        Troll(Team team) : Monster(team, 100, 15) {};

        ~Troll() override = default;

        void attack(Monster* target) override {
            Orc* orcTarget = NULL;
            if (dynamic_cast<Orc*>(target)) {
                orcTarget = (Orc*) target; 
            }

            if (orcTarget != NULL) {
                Monster::attackOrc(target, orcTarget->damageBlocked, orcTarget->damageReflected);
            } else {
                Monster::attack(target);
            }

            if (health > 0) {
                regenerate();
            }
        }
};


int main() {
    vector<Monster> red = {Goblin(RED), Troll(RED), Orc(RED)};
    vector<Monster> blue = {Goblin(BLUE), Troll(BLUE), Orc(BLUE)};

    gameLoop(red, blue);

    return 0;
}

void printBattleIntro(Monster* monster1, Monster* monster2) {
    cout << "[ RED | " << typeid(monster1).name() << '(' << monster1->health << ") ] vs [ "
    << typeid(monster2).name() << '(' << monster2->health << ") | BLUE ]" << endl;
}

void printBarrier() {
    cout << "--------------------------------------------------------------------------" << endl;
}

void gameLoop(vector<Monster>& red, vector<Monster>& blue) {
    // todo: add game loop
}