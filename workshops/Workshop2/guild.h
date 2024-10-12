#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <cstring>
#include <vector>
#include "character.h" // Ensure you have a Character class implemented.

namespace seneca {

    class Guild {
    private:
        Character** m_members; // Array of pointers to Character
        size_t m_size;         // Current number of members
        size_t m_capacity;     // Capacity of the array
        std::string m_name;    // Name of the guild

        void resize(); // Resize the members array

    public:
        // Default constructor
        Guild();

        // Parameterized constructor
        Guild(const char* name);

        // Rule of Five
        ~Guild();
        Guild(const Guild& other);
        Guild& operator=(const Guild& other);
        Guild(Guild&& other) noexcept;
        Guild& operator=(Guild&& other) noexcept;

        // Add member to the guild
        void addMember(Character* c);

        // Remove member from the guild
        void removeMember(const std::string& c);

        // Access operator
        Character* operator[](size_t idx) const;

        // Show members
        void showMembers() const;
    };

}

#endif // SENECA_GUILD_H
