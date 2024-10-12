#include "guild.h"

namespace seneca {

    // Default constructor
    Guild::Guild() : m_members(nullptr), m_size(0), m_capacity(0), m_name("Unnamed Guild") {}

    // Parameterized constructor
    Guild::Guild(const char* name) : m_members(nullptr), m_size(0), m_capacity(0), m_name(name) {}

    // Rule of Five

    // Destructor
    Guild::~Guild() {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_members[i]; // Free the characters, assuming they were dynamically allocated.
        }
        delete[] m_members; // Free the array of pointers
    }

    // Copy constructor
    Guild::Guild(const Guild& other)
        : m_members(new Character* [other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity), m_name(other.m_name) {
        for (size_t i = 0; i < m_size; ++i) {
            m_members[i] = other.m_members[i]->clone(); // Assuming clone() creates a copy of Character
        }
    }

    // Copy assignment operator
    Guild& Guild::operator=(const Guild& other) {
        if (this != &other) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i]; // Free current members
            }
            delete[] m_members; // Free the old array

            m_capacity = other.m_capacity;
            m_size = other.m_size;
            m_name = other.m_name;

            m_members = new Character * [m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                m_members[i] = other.m_members[i]->clone();
            }
        }
        return *this;
    }

    // Move constructor
    Guild::Guild(Guild&& other) noexcept
        : m_members(other.m_members), m_size(other.m_size), m_capacity(other.m_capacity), m_name(std::move(other.m_name)) {
        other.m_members = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // Move assignment operator
    Guild& Guild::operator=(Guild&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;

            m_members = other.m_members;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_name = std::move(other.m_name);

            other.m_members = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    void Guild::resize() {
        size_t newCapacity = m_capacity == 0 ? 1 : m_capacity * 2; // Double the capacity
        Character** newMembers = new Character * [newCapacity];

        for (size_t i = 0; i < m_size; ++i) {
            newMembers[i] = m_members[i];
        }

        delete[] m_members; // Free old array
        m_members = newMembers;
        m_capacity = newCapacity;
    }

    void Guild::addMember(Character* c) {
        // Check if the character is already a member
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                std::cout << c->getName() << " is already in the guild." << std::endl;
                return;
            }
        }

        // Resize if necessary
        if (m_size >= m_capacity) {
            resize();
        }

        // Add the character to the guild and increase health
        m_members[m_size] = c;
        c->increaseMaxHealth(300); // Assuming a method to increase health
        ++m_size;
    }

    void Guild::removeMember(const std::string& c) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c) {
                m_members[i]->decreaseMaxHealth(300); // Assuming a method to decrease health
                delete m_members[i]; // Free the character
                m_members[i] = m_members[m_size - 1]; // Move last member to current position
                --m_size;
                std::cout << c << " has left the guild." << std::endl;
                return;
            }
        }
        std::cout << c << " is not in the guild." << std::endl;
    }

    Character* Guild::operator[](size_t idx) const {
        if (idx < m_size) {
            return m_members[idx];
        }
        return nullptr; // Out of bounds
    }

    void Guild::showMembers() const {
        std::cout << "[Guild] " << m_name << std::endl;
        if (m_size == 0) {
            std::cout << "No guild." << std::endl;
        }
        else {
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << (i + 1) << ": " << *m_members[i] << std::endl; // Use operator<< defined for Character
            }
        }
    }

}
