#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include <iostream>
#include <string>
#include "CharacterTpl.h"

using namespace std;

namespace seneca {

    template<typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        double m_baseAttack{};
        double m_baseDefense{};

        Ability_t m_ability{};

		Weapon_t m_weapon[2];

    public:
        // Constructor
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense,
            Weapon_t primaryWeapon, Weapon_t secondaryWeapon) : CharacterTpl<T>(name, healthMax)
        {
			m_baseAttack = baseAttack;
			m_baseDefense = baseDefense;
            m_weapon[0] = primaryWeapon;
            m_weapon[1] = secondaryWeapon;
        }

       
        int getAttackAmnt() const override;
      
        int getDefenseAmnt() const;

        
        Character* clone() const override;

        
        void attack(Character* enemy) override;

        
        void takeDamage(int dmg) override;
    };

}

#include "barbarian.h"
#endif // SENECA_BARBARIAN_H