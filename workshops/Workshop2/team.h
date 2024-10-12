#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <iostream>
#include <cstring>
#include "character.h" // Ensure you have a Character class implemented.

namespace seneca {

    class Team {
    private:
        Character** m_members; // Array of pointers to Character
        size_t m_size;         // Current number of members
        size_t m_capacity;     // Capacity of the array
        std::string m_name;    // Name of the team

        void resize(); // Resize the members array

    public:
        // Default constructor
        Team();

        // Parameterized constructor
        Team(const char* name);

        // Rule of Five
        ~Team();
        Team(const Team& other);
        Team& operator=(const Team& other);
        Team(Team&& other) noexcept;
        Team& operator=(Team&& other) noexcept;

        // Add member to the team
        void addMember(const Character* c);

        // Remove member from the team
        void removeMember(const std::string& c);

        // Access operator
        Character* operator[](size_t idx) const;

        // Show members
        void showMembers() const;
    };

}

#endif // SENECA_TEAM_H
