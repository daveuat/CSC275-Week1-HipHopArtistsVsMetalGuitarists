#include <iostream>
#include <string>
#include <cstdlib> // for rand() function
#include <ctime> // for time() function

using namespace std;

// GameStructure class with Help method as pure virtual function
class GameStructure {
public:
    virtual void Help() = 0;
};

// Character class and it inherits from GameStructure
class Character : public GameStructure {
public:
    string Name;
    void Talk(string stuffToSay);
    void Talk(string name, string stuffToSay);
    virtual int attack();
    virtual int specialAttack();

protected:
    int Health;

public:
    int getHealth();
    void setHealth(int health);

    void Help() override;

};

// Hip Hop Artist class and it inherits from Character
class HipHopArtist : public Character {
public:
    HipHopArtist(string name, int health);
    void ThrowMic();
    int attack() override;
    int specialAttack() override;
    void Help() override;
};

// Metal Guitarist class inherits from Character
class MetalGuitarist : public Character {
public:
    MetalGuitarist(string name, int health);
    void ThrowGuitar();
    int attack() override;
    int specialAttack() override;
    void Help() override;
};

// Implementations for Character classes and with stufftosay added from guidelines
void Character::Talk(string stuffToSay) {
    cout << Name << ": " << stuffToSay << endl;
}

void Character::Talk(string name, string stuffToSay) {
    cout << name << ": " << stuffToSay << endl;
}

int Character::attack() {
    return 10;
}

int Character::specialAttack() {
    return 0;
}

int Character::getHealth() {
    return Health;
}

void Character::setHealth(int health) {
    if (health < 0) {
        Health = 0;
        cout << "Character has Expired..." << endl;
    }
    else {
        Health = health;
    }
}

void Character::Help() {
    cout << "This is a character in the game. It has the ability to attack and use special attacks to defeat the enemy." << endl;
}

// Implementations for HipHopArtist class in game
HipHopArtist::HipHopArtist(string name, int health) {
    Name = name;
    setHealth(health);
}

void HipHopArtist::ThrowMic() {
    cout << "Eat this! *Throws mics*" << endl;
}

int HipHopArtist::attack() {
    int damage = rand() % 10 + 1; // random damage from 1-10
    return damage;
}

int HipHopArtist::specialAttack() {
    int damage = 0;
    int chance = rand() % 2; // 50% chance of special attack

    if (chance == 0) {
        damage = rand() % 15 + 5; // random damage +5
        cout << Name << " unleashes a devastating freestyle rap for " << damage << " damage!" << endl;
    }
    else {
        cout << Name << " tries to use a special attack, but it fails!" << endl;
    }

    return damage;
}

void HipHopArtist::Help() {
    cout << "Hip Hop Artists are really witty. Watch out!" << endl;
}

// Implementations for MetalGuitarist class
MetalGuitarist::MetalGuitarist(string name, int health) {
    Name = name;
    setHealth(health);
}

void MetalGuitarist::ThrowGuitar() {
    cout << "Wail on this Axe!" << endl;
}

int MetalGuitarist::attack() {
    int damage = rand() % 10 + 1; // random damage from 1-10
    return damage;
}

int MetalGuitarist::specialAttack() {
    int damage = 0;
    int chance = rand() % 2; // 50% chance of special attack

    if (chance == 0) {
        damage = rand() % 11 + 5; // random damage from 5-15
        cout << Name << " shreds an epic guitar solo for " << damage << " damage!" << endl;
    }
    else {
        cout << Name << " tries to use a special attack, but it fails!" << endl;
    }

    return damage;
}

void MetalGuitarist::Help() {
    cout << "Metal Guitarists are really fast. Be careful!" << endl;
}

// Main function
int main() {
    // Display game intro
    cout << "Welcome to Hip Hop Artists vs Metal Guitarists!" << endl;

    // Create game loop
    bool exitGame = false;
    while (!exitGame) {
        // Character selection
        cout << "Select your character:" << endl;
        cout << "1. Hip Hop Artist" << endl;
        cout << "2. Metal Guitarist" << endl;
        cout << "Enter your choice (1 or 2): ";
        int choice;
        cin >> choice;

        // Initialize player and enemy based on user selection
        Character* player;
        Character* enemy;

        if (choice == 2) {
            player = new MetalGuitarist("Metal Guitarist", 100);
            enemy = new HipHopArtist("Hip Hop Artist", 100);
        }
        else {
            player = new HipHopArtist("Hip Hop Artist", 100);
            enemy = new MetalGuitarist("Metal Guitarist", 100);
        }

        // Start the fight
        bool exitFight = false;
        while (!exitFight) {
            // Player's turn
            cout << endl;
            cout << player->Name << "'s turn:" << endl;
            cout << "1. Attack" << endl;
            cout << "2. Special Attack" << endl;
            cout << "Enter your choice (1 or 2): ";
            cin >> choice;

            if (choice == 2) {
                player->specialAttack();
            }
            else {
                int damage = player->attack();
                enemy->setHealth(enemy->getHealth() - damage);
                cout << player->Name << " attacks " << enemy->Name << " for " << damage << " damage!" << endl;
            }

            if (enemy->getHealth() <= 0) {
                cout << endl;
                cout << enemy->Name << " has been defeated!" << endl;
                exitFight = true;
            }

            // Enemy's turn
            if (!exitFight) {
                cout << endl;
                cout << enemy->Name << "'s turn:" << endl;

                int damage = enemy->attack();
                player->setHealth(player->getHealth() - damage);
                cout << enemy->Name << " attacks " << player->Name << " for " << damage << " damage!" << endl;

                if (player->getHealth() <= 0) {
                    cout << endl;
                    cout << player->Name << " has been defeated!" << endl;
                    exitFight = true;
                }
            }
        }

        // Cleanup player and enemy objects
        delete player;
        delete enemy;





        // Ask user if they want to exit the game or play again
        bool validChoice = false;
        while (!validChoice) {
            cout << "Do you want to exit the game or play again? (e/p): ";
            char exitChoice;
            cin >> exitChoice;
            if (exitChoice == 'e' || exitChoice == 'E') {
                exitGame = true;
                validChoice = true;
            }
            else if (exitChoice == 'p' || exitChoice == 'P') {
                validChoice = true;
            }
            else {
                cout << "Invalid choice. ";
            }
        }
    }

    return 0;
}