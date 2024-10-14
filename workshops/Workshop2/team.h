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

        void cleanup();

    public:
        Team();
        Team(const char* name);
        Team(const Team& other);
        Team& operator=(const Team& other);
        Team(Team&& other) noexcept;
        Team& operator=(Team&& other) noexcept;
        ~Team();

        void addMember(const Character* c);
        void removeMember(const std::string& name);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };

}

#endif 
