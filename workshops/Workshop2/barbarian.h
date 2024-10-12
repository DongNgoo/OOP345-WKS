#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include <iostream>
#include <string>
#include "CharacterTpl.h"

namespace seneca {

    template<typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T, Ability_t> {
        int m_baseDefense;
        int m_baseAttack;
        Ability_t m_ability;
        Weapon_t m_weapon[2]; 

    public:
        // Constructor
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense,
            Weapon_t primaryWeapon, Weapon_t secondaryWeapon);

        // Get the total attack amount, including weapons' contributions
        int getAttackAmnt() const;

        // Get the base defense amount
        int getDefenseAmnt() const;

        // Clone the current instance
        Character* clone() const override;

        // Attack an enemy character
        void attack(Character* enemy) override;

        // Take damage from an attack
        void takeDamage(int dmg) override;
    };

}

#include "barbarian.h"
#endif // SENECA_BARBARIAN_H
