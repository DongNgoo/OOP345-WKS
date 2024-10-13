#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <iostream>
#include <string>

namespace seneca {

    class Guild {
    private:
        Character** m_members; // Pointer to dynamically allocated array of Character pointers
        size_t m_size;         // Current size of the guild (number of members)
        size_t m_capacity;     // Maximum capacity of the members array
        std::string m_name;    // Name of the guild

        void resize(); // Resizes the members array when needed

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

        
        void addMember(Character* c);

       
        void removeMember(const std::string& c);

        
        Character* operator[](size_t idx) const;

        
        void showMembers() const;
    };
}

#endif // SENECA_GUILD_H
