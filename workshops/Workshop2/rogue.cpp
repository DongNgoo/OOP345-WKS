

#include "rogue.h"
#include <iostream>

namespace seneca {

    template<typename T, typename FirstAbility_t, typename SecondAbility_t>
    Rogue<T, FirstAbility_t, SecondAbility_t>::Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
        : CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {}

    template<typename T, typename FirstAbility_t, typename SecondAbility_t>
    int Rogue<T, FirstAbility_t, SecondAbility_t>::getAttackAmnt() const {
        // Assuming weapon damage is not considered as per your request
        return m_baseAttack; // Modify if needed to add weapon damage
    }

    template<typename T, typename FirstAbility_t, typename SecondAbility_t>
    int Rogue<T, FirstAbility_t, SecondAbility_t>::getDefenseAmnt() const {
        return m_baseDefense;
    }

    template<typename T, typename FirstAbility_t, typename SecondAbility_t>
    Character* Rogue<T, FirstAbility_t, SecondAbility_t>::clone() const {
        return new Rogue(*this); // Clone the current instance
    }

    template<typename T, typename FirstAbility_t, typename SecondAbility_t>
    void Rogue<T, FirstAbility_t, SecondAbility_t>::attack(Character* enemy) {
        std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";

        // Use the first ability
        m_firstAbility.useAbility(this);
        // Use the second ability
        m_secondAbility.useAbility(this);

        int damage = getAttackAmnt();
        m_firstAbility.transformDamageDealt(damage);
        m_secondAbility.transformDamageDealt(damage);

        std::cout << "Rogue deals " << damage << " melee damage!\n";
        enemy->takeDamage(damage);
    }

    template<typename T, typename FirstAbility_t, typename SecondAbility_t>
    void Rogue<T, FirstAbility_t, SecondAbility_t>::takeDamage(int dmg) {
        std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
        std::cout << "Rogue has a defense of " << getDefenseAmnt() << ". Reducing damage received.\n";

        dmg -= getDefenseAmnt();
        if (dmg < 0) dmg = 0;

        // Use the first ability to reduce damage taken
        m_firstAbility.transformDamageReceived(dmg);
        // Use the second ability to reduce damage taken
        m_secondAbility.transformDamageReceived(dmg);

        CharacterTpl<T>::takeDamage(dmg);
    }
}

// Explicit instantiation for common health types and abilities
template class seneca::Rogue<seneca::SuperHealth, FirstAbilityType, SecondAbilityType>; // Replace with actual ability types

