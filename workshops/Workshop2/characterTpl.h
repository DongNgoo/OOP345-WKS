
#ifndef SENECA_CHARACTER_TPL_H
#define SENECA_CHARACTER_TPL_H

#include <iostream>
#include <string>
#include "character.h"

namespace seneca {

    template<typename T, typename Ability_t>
    class CharacterTpl : public Character {
        int m_healthMax;
        T m_health;

    public:

        CharacterTpl(const std::string& name, int healthMax)
            : Character(name), m_healthMax(healthMax), m_health(healthMax) {}


        void takeDamage(int dmg) override {
            m_health -= dmg;

            if (m_health <= 0) {
                std::cout << getName() << " has been defeated!" << std::endl;
            }
            else {
                std::cout << getName() << " took " << dmg
                    << " damage, " << static_cast<int>(m_health)
                    << " health remaining." << std::endl;
            }
        }

        /* auto getHealth = [&]() const override {
             return static_cast<int>(m_health)};

     }*/

        int gethealth() const override {
            return static_cast<int>(m_health);
        }


        int getHealthMax() const override {
            return m_healthMax;
        }


        void setHealth(int health) override {
            m_health = health;
        }


        void setHealthMax(int health) override {
            m_healthMax = health;
            m_health = health;
        }


    };

}

#endif 