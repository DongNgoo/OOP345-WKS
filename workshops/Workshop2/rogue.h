#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include <iostream>
#include "characterTpl.h"
#include "weapons.h" 

namespace seneca {

    template<typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
    private:
        int m_baseDefense;
        int m_baseAttack;
        FirstAbility_t m_firstAbility;
        SecondAbility_t m_secondAbility;
        Dagger m_weapon; // Assuming Dagger is a class that has conversion to double for weapon damage.

    public:
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax),
            m_baseAttack(baseAttack),
            m_baseDefense(baseDefense) {}

        int getAttackAmnt() const {
            // Assuming Dagger has a conversion to double defined
            return m_baseAttack + 2 * static_cast<int>(m_weapon); // Adjust if Dagger has a different way to get damage
        }

        int getDefenseAmnt() const {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Rogue(*this);
        }

        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            // Activate first special ability
            m_firstAbility.useAbility(this);

            // Activate second special ability
            m_secondAbility.useAbility(this);

            int damage = getAttackAmnt();

            // Transform damage dealt by abilities
            m_firstAbility.transformDamageDealt(damage);
            m_secondAbility.transformDamageDealt(damage);

            std::cout << "Rogue deals " << damage << " melee damage!" << std::endl;

            // Apply damage to the enemy
            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "Rogue has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

            dmg -= getDefenseAmnt();
            if (dmg < 0) {
                dmg = 0; // Ensure damage cannot be negative
            }

            // Transform damage received by abilities
            m_firstAbility.transformDamageReceived(dmg);
            m_secondAbility.transformDamageReceived(dmg);

            CharacterTpl<T>::takeDamage(dmg); // Call base class takeDamage
        }
    };

}

#endif // SENECA_ROGUE_H
