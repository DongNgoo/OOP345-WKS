//#include "rogue.h"
//
//namespace seneca {
//
//    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
//    Rogue<T, FirstAbility_t, SecondAbility_t>::Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
//        : CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon() {}
//
//    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
//    int Rogue<T, FirstAbility_t, SecondAbility_t>::getAttackAmnt() const {
//        // Calculate attack damage using the specified formula
//        return m_baseAttack + 2 * static_cast<double>(m_weapon);
//    }
//
//    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
//    int Rogue<T, FirstAbility_t, SecondAbility_t>::getDefenseAmnt() const {
//        return m_baseDefense;
//    }
//
//    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
//    Character* Rogue<T, FirstAbility_t, SecondAbility_t>::clone() const {
//        return new Rogue(*this); // Clone the current instance
//    }
//
//    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
//    void Rogue<T, FirstAbility_t, SecondAbility_t>::attack(Character* enemy) {
//        std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;
//
//        // Use the first ability
//        m_firstAbility.useAbility(this);
//
//        // Use the second ability
//        m_secondAbility.useAbility(this);
//
//        int damage = getAttackAmnt(); // Get attack amount
//
//        // Enhance damage using first ability
//        m_firstAbility.transformDamageDealt(damage);
//
//        // Enhance damage using second ability
//        m_secondAbility.transformDamageDealt(damage);
//
//        std::cout << "Rogue deals " << damage << " melee damage!" << std::endl;
//
//        // Apply damage to the enemy
//        enemy->takeDamage(damage);
//    }
//
//    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
//    void Rogue<T, FirstAbility_t, SecondAbility_t>::takeDamage(int dmg) {
//        std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
//        std::cout << "Rogue has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;
//
//        // Block damage using defense
//        dmg = std::max(0, dmg - getDefenseAmnt());
//
//        // Use first ability to further reduce damage
//        m_firstAbility.transformDamageReceived(dmg);
//
//        // Use second ability to further reduce damage
//        m_secondAbility.transformDamageReceived(dmg);
//
//        // Call base class takeDamage
//        CharacterTpl<T>::takeDamage(dmg);
//    }
//
//    // Explicit template instantiation for common types
//    template class Rogue<int, FirstAbilityType, SecondAbilityType>; // Change FirstAbilityType and SecondAbilityType to your actual types
//
//}
