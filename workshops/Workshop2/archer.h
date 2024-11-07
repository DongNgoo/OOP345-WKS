#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include <iostream>
#include <string>
#include "characterTpl.h"
#include "character.h"
#include "health.h"


namespace seneca {

    template<typename Weapon_t>
    class Archer : public CharacterTpl<seneca::SuperHealth> {
        int m_baseDefense;
        int m_baseAttack;
        Weapon_t m_weapon;

    public:
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<seneca::SuperHealth>(name, healthMax),
            m_baseAttack(baseAttack),
            m_baseDefense(baseDefense),
            m_weapon(weapon) {}

        int getAttackAmnt() const {
            // Formula: 1.3 * base_attack
            return static_cast<int>(1.3 * m_baseAttack);
        }

        int getDefenseAmnt() const {
            // Formula: 1.2 * base_defense
            return static_cast<int>(1.2 * m_baseDefense);
        }

        Character* clone() const override {
            // Create a dynamically allocated 
            return new Archer<Weapon_t>(*this);
        }

        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            int damage = getAttackAmnt();
            std::cout << "Archer deals " << damage << " ranged damage!" << std::endl;

            
            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;

           
            int defense = getDefenseAmnt();
            std::cout << "Archer has a defense of " << defense << ". Reducing damage received." << std::endl;

            
            dmg -= defense;
            if (dmg < 0) {
                dmg = 0;  // Damage cannot be less than 0
            }

          
            CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
        }
    };
}

#endif // SENECA_ARCHER_H