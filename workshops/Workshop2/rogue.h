#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h" // Include the base character template class
#include "weapons.h"      // Include the Dagger weapon class

namespace seneca {

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpL<T> {
    private:
        int m_baseDefense;               // Basic defense of the character
        int m_baseAttack;                // Basic attack power of the character
        FirstAbility_t m_firstAbility;   // First special ability
        SecondAbility_t m_secondAbility;  // Second special ability
        Dagger m_weapon;                  // Weapon used in battle

    public:
        // Constructor
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
            : CharacterTpL<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {}

        // Calculate the attack amount based on the specified formula
        int getAttackAmnt() const override {
            return m_baseAttack + 2 * static_cast<double>(m_weapon); // Using dagger's damage
        }

        // Return the base defense value
        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        // Clone method to create a copy of the Rogue instance
        Character* clone() const override {
            return new Rogue(*this); // Clone using copy constructor
        }

        // Attack method implementation
        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            // Use special abilities
            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);

            // Calculate damage
            int damage = getAttackAmnt();

            // Transform damage using special abilities
            m_firstAbility.transformDamageDealt(damage);
            m_secondAbility.transformDamageDealt(damage);

            std::cout << "Rogue deals " << damage << " melee damage!" << std::endl;

            // Apply damage to the enemy
            enemy->takeDamage(damage);
        }

        // Take damage method implementation
        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;

            int defense = getDefenseAmnt();
            std::cout << this->getName() << " has a defense of " << defense << ". Reducing damage received." << std::endl;

            // Adjust damage by defense
            dmg -= defense;
            if (dmg < 0) {
                dmg = 0; // Ensure damage is not negative
            }

            // Transform damage received using special abilities
            m_firstAbility.transformDamageReceived(dmg);
            m_secondAbility.transformDamageReceived(dmg);

            // Call base class to update health
            CharacterTpL<T>::takeDamage(dmg);
        }
    };

} // namespace seneca

#endif // SENECA_ROGUE_H
