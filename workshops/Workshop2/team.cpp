#include "team.h"

namespace seneca {

    // Default constructor
    Team::Team() : m_members(nullptr), m_size(0), m_capacity(0), m_name("Unnamed Team") {}

    // Parameterized constructor
    Team::Team(const char* name) : m_members(nullptr), m_size(0), m_capacity(0), m_name(name) {}

    // Rule of Five

    // Destructor
    Team::~Team() {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_members[i]; // Free the characters, assuming they were cloned dynamically.
        }
        delete[] m_members; // Free the array of pointers
    }

    // Copy constructor
    Team::Team(const Team& other)
        : m_members(new Character* [other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity), m_name(other.m_name) {
        for (size_t i = 0; i < m_size; ++i) {
            m_members[i] = other.m_members[i]->clone(); // Assuming clone() creates a copy of Character
        }
    }

    // Copy assignment operator
    Team& Team::operator=(const Team& other) {
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
                m_members[i] = other.m_members[i]->clone(); // Clone each member
            }
        }
        return *this;
    }

    // Move constructor
    Team::Team(Team&& other) noexcept
        : m_members(other.m_members), m_size(other.m_size), m_capacity(other.m_capacity), m_name(std::move(other.m_name)) {
        other.m_members = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // Move assignment operator
    Team& Team::operator=(Team&& other) noexcept {
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

    void Team::resize() {
        size_t newCapacity = m_capacity == 0 ? 1 : m_capacity * 2; // Double the capacity
        Character** newMembers = new Character * [newCapacity];

        for (size_t i = 0; i < m_size; ++i) {
            newMembers[i] = m_members[i];
        }

        delete[] m_members; // Free old array
        m_members = newMembers;
        m_capacity = newCapacity;
    }

    void Team::addMember(const Character* c) {
        // Check if the character is already a member
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                std::cout << c->getName() << " is already in the team." << std::endl;
                return;
            }
        }

        // Resize if necessary
        if (m_size >= m_capacity) {
            resize();
        }

        // Add the character to the team using clone to make a copy
        m_members[m_size] = c->clone();
        ++m_size;
    }

    void Team::removeMember(const std::string& c) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c) {
                delete m_members[i]; // Free the character
                m_members[i] = m_members[m_size - 1]; // Move last member to current position
                --m_size;
                std::cout << c << " has left the team." << std::endl;
                return;
            }
        }
        std::cout << c << " is not in the team." << std::endl;
    }

    Character* Team::operator[](size_t idx) const {
        if (idx < m_size) {
            return m_members[idx];
        }
        return nullptr; // Out of bounds
    }

    void Team::showMembers() const {
        std::cout << "[Team] " << m_name << std::endl;
        if (m_size == 0) {
            std::cout << "No team." << std::endl;
        }
        else {
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << (i + 1) << ": " << *m_members[i] << std::endl; // Use operator<< defined for Character
            }
        }
    }

}
