#ifndef SENECA_BARBARIAN_CPP
#define SENECA_BARBARIAN_CPP

#include "Barbarian.h"

namespace seneca {

    template<typename T, typename Ability_t, typename Weapon_t>
    Barbarian<T, Ability_t, Weapon_t>::Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense,
        Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
        : CharacterTpl<T, Ability_t>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {
        m_weapon[0] = primaryWeapon;
        m_weapon[1] = secondaryWeapon;
    }

    template<typename T, typename Ability_t, typename Weapon_t>
    int Barbarian<T, Ability_t, Weapon_t>::getAttackAmnt() const {
        // Convert weapon damages to double and halve them as per the formula.
        double weaponDamage1 = static_cast<double>(m_weapon[0]) / 2.0;
        double weaponDamage2 = static_cast<double>(m_weapon[1]) / 2.0;

        // Calculate the total attack amount.
        int totalAttack = m_baseAttack + static_cast<int>(weaponDamage1) + static_cast<int>(weaponDamage2);

        return totalAttack;
    }



    template<typename T, typename Ability_t, typename Weapon_t>
    int Barbarian<T, Ability_t, Weapon_t>::getDefenseAmnt() const {
        return m_baseDefense;
    }

    template<typename T, typename Ability_t, typename Weapon_t>
    Character* Barbarian<T, Ability_t, Weapon_t>::clone() const {
        return new Barbarian(*this);
    }

    template<typename T, typename Ability_t, typename Weapon_t>
    void Barbarian<T, Ability_t, Weapon_t>::attack(Character* enemy) {
        std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

        // Use the special ability to enhance the character's own capabilities
        m_ability.useAbility(this);

        // Get the base damage
        int damage = getAttackAmnt();

        // Enhance the damage dealt using the special ability
        m_ability.transformDamageDealt(damage);

        // Print the enhanced damage
        std::cout << "Barbarian deals " << damage << " melee damage!" << std::endl;

        // Apply the damage to the enemy
        enemy->takeDamage(damage);
    }

    template<typename T, typename Ability_t, typename Weapon_t>
    void Barbarian<T, Ability_t, Weapon_t>::takeDamage(int dmg) {
        std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
        std::cout << "Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

        // Subtract the defense amount from the incoming damage
        dmg -= m_baseDefense;
        if (dmg < 0) {
            dmg = 0;
        }

        // Further reduce damage using the special ability
        m_ability.transformDamageReceived(dmg);

        // Call base class function to update health
        CharacterTpl<T, Ability_t>::takeDamage(dmg);
    }

}

#endif // SENECA_BARBARIAN_CPP
