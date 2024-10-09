#ifndef SENECATEAM_H
#define SENECATEAM_H

#include <string>
#include "character.h"

namespace seneca {
    class Team {
        std::string m_name;          // Team name
        size_t m_cnt;                // Number of team members
        Character** m_members;       // Array of pointers to team members (Character objects)

    public:
        Team(const char* name = ""); // Constructor with default name
        Team(const Team& other);     // Copy constructor
        Team& operator=(const Team& other); // Copy assignment operator
        Team(Team&& other) noexcept; // Move constructor
        Team& operator=(Team&& other) noexcept; // Move assignment operator
        ~Team();                     // Destructor

        void addMember(const Character* c);    // Adds a member to the team
        void removeMember(const std::string& name); // Removes a member from the team by name
        Character* operator[](size_t idx) const; // Accesses a member by index
        void showMembers() const;     // Displays the team's members
        void cleanup();               // Cleans up the dynamically allocated memory
    };
}

#endif // SENECATEAM_H
