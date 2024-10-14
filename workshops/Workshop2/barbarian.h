#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include <iostream>
#include "characterTpl.h"  
using namespace std;

namespace seneca {

    template<typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> 
    {
    private:
        int m_baseDefense{};     
        int m_baseAttack{};      
        Ability_t m_ability{};   
        Weapon_t m_weapon[2]{};  

    public:
        
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, 
            Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpL<T>(name, healthMax)
        {
            m_baseAttack(baseAttack),
                m_baseDefense(baseDefense),
                
                m_weapon[0] = primaryWeapon;
                m_weapon[1] = secondaryWeapon;
            
        }

        
        int getAttackAmnt() const override{
            double weapon1Damage = static_cast<double>(m_weapon[0]) / 2;
            double weapon2Damage = static_cast<double>(m_weapon[1]) / 2;
            return m_baseAttack + static_cast<int>(weapon1Damage + weapon2Damage);
        }

        
        int getDefenseAmnt() const {
            return m_baseDefense;
        }

        
        Character* clone() const override {
            return new Barbarian<T, Ability_t, Weapon_t>(*this);
        }

       
        void attack(Character* enemy) override {
            cout << this->getName() << " is attacking " << enemy->getName() << ".\n";

          
            m_ability.useAbility(this);

            
            int damage = getAttackAmnt();

           
            m_ability.transformDamageDealt(damage);

            cout << "Barbarian deals " << damage << " melee damage!\n";

        
            enemy->takeDamage(damage);
        }

       
            cout << this->getName() << " is attacked for " << dmg << " damage.\n";
            cout << "Barbarian has a defense of " << getDefenseAmnt() << ". Reducing damage received.\n";

           
            dmg -= getDefenseAmnt();
            dmg = (dmg < 0) ? 0 : dmg;

            
            m_ability.transformDamageReceived(dmg);

            
            CharacterTpl<T>::takeDamage(dmg);
        
    };

} // namespace seneca

#endif // SENECA_BARBARIAN_H
