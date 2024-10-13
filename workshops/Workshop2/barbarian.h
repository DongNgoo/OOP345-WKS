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

       
        int getAttackAmnt() const;

      
        int getDefenseAmnt() const;

        
        Character* clone() const override;

        
        void attack(Character* enemy) override;

        
        void takeDamage(int dmg) override;
    };

}

#include "barbarian.h"
#endif // SENECA_BARBARIAN_H