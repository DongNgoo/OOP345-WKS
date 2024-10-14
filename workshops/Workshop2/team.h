#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <string>
#include "character.h"

namespace seneca {

    class Team {
        std::string m_name{};          // Name of the team
        Character** m_members{};       // Dynamically allocated array of Character pointers
        size_t m_cnt{};                // Current number of members in the team

        // Helper function to clean up the allocated memory
        void cleanup();

    public:
        // Constructors
        Team() = default;
        Team(const char* name);

        // Copy constructor
        Team(const Team& other);

        // Copy assignment operator
        Team& operator=(const Team& other);

        // Move constructor
        Team(Team&& other) noexcept;

        // Move assignment operator
        Team& operator=(Team&& other) noexcept;

        // Destructor
        ~Team();

        // Adds a member to the team (makes a clone of the character)
        void addMember(const Character* c);

        // Removes a member from the team by name
        void removeMember(const std::string& name);

        // Overloads the subscript operator to access team members by index
        Character* operator[](size_t idx) const;

        // Displays the team members' details
        void showMembers() const;
    };

} // namespace seneca

#endif // SENECA_TEAM_H
