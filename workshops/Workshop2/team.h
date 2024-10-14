#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <iostream>
#include <string>
#include <iomanip>
#include "character.h"

namespace seneca {

    class Team {
    private:
        Character** m_members = nullptr; 
        size_t m_cnt = 0;                
        std::string m_name;             

        void cleanup() {
            for (size_t i = 0; i < m_cnt; ++i)
                delete m_members[i];

            delete[] m_members;
            m_members = nullptr;
            m_cnt = 0;
            m_name.clear();
        }

    public:
       
        Team() = default;

       
        Team(const char* name) : m_name{ name } {}

        
        Team(const Team& other) : Team() {
            *this = other;
        }

        
        Team& operator=(const Team& other) {
            if (this != &other) {
                cleanup();

                m_name = other.m_name;
                m_cnt = other.m_cnt;

                if (other.m_cnt > 0) {
                    m_members = new Character * [other.m_cnt];
                    for (size_t i = 0; i < other.m_cnt; ++i) {
                        m_members[i] = other.m_members[i]->clone();
                    }
                }
            }
            return *this;
        }

        
        Team(Team&& other) noexcept : Team() {
            *this = std::move(other);
        }

        
        Team& operator=(Team&& other) noexcept {
            if (this != &other) {
                cleanup();

                m_cnt = other.m_cnt;
                m_name = std::move(other.m_name);
                m_members = other.m_members;

                other.m_members = nullptr;
                other.m_cnt = 0;
            }
            return *this;
        }

        
        ~Team() {
            cleanup();
        }

        
        void addMember(const Character* c) {
            for (size_t i = 0; i < m_cnt; ++i) {
                if (m_members[i]->getName() == c->getName()) {
                    return; 
                }
            }

            Character** tmp = new Character * [m_cnt + 1];
            for (size_t i = 0; i < m_cnt; ++i) {
                tmp[i] = m_members[i];
            }
            tmp[m_cnt] = c->clone();

            delete[] m_members;
            m_members = tmp;
            ++m_cnt;
        }

        
        void removeMember(const std::string& name) {
            size_t idx = 0;
            while (idx < m_cnt && m_members[idx]->getName() != name) {
                ++idx;
            }

            if (idx < m_cnt) {
                Character** tmp = new Character * [m_cnt - 1];
                for (size_t i = 0; i < idx; ++i) {
                    tmp[i] = m_members[i];
                }
                for (size_t i = idx + 1; i < m_cnt; ++i) {
                    tmp[i - 1] = m_members[i];
                }

                delete m_members[idx];
                delete[] m_members;
                m_members = tmp;
                --m_cnt;
            }
        }

        
        Character* operator[](size_t idx) const {
            return (idx < m_cnt) ? m_members[idx] : nullptr;
        }

       
        void showMembers() const {
            if (!m_name.empty()) {
                std::cout << "[Team] " << m_name << "\n";
                for (size_t i = 0; i < m_cnt; ++i) {
                    std::cout << std::setw(5) << i + 1 << ": " << *m_members[i] << "\n";
                }
            }
            else {
                std::cout << "No team.\n";
            }
        }
    };

} 

#endif // SENECA_TEAM_H
