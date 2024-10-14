#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <iostream>
#include <string>
#include <iomanip>

namespace seneca {

    class Guild {
    private:
        Character** m_members;
        size_t m_size;
        size_t m_capacity;
        std::string m_name;

        void resize();

    public:
        // Default constructor
        Guild();

        // Constructor with name parameter
        Guild(const char* name);

        // Destructor
        ~Guild();

        // Copy constructor
        Guild(const Guild& other);

        // Copy assignment operator
        Guild& operator=(const Guild& other);

        // Move constructor
        Guild(Guild&& other) noexcept;

        // Move assignment operator
        Guild& operator=(Guild&& other) noexcept;

        // Add a member to the guild
        void addMember(Character* c);

        // Remove a member by name
        void removeMember(const std::string& name);

        // Access a member by index
        Character* operator[](size_t idx) const;

        // Show the guild members
        void showMembers() const;
    };

} // namespace seneca

#endif // SENECA_GUILD_H
