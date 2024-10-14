#include "guild.h"

namespace seneca {

    // Default constructor
    Guild::Guild()
        : m_members{ nullptr }, m_size{ 0 }, m_capacity{ 0 }, m_name{ "Unnamed Guild" } {}

    // Constructor with name parameter
    Guild::Guild(const char* name)
        : m_members{ nullptr }, m_size{ 0 }, m_capacity{ 0 }, m_name{ name } {}

    // Destructor
    Guild::~Guild() {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_members[i];
        }
        delete[] m_members;
    }

    // Copy constructor
    Guild::Guild(const Guild& other)
        : m_members{ nullptr }, m_size{ 0 }, m_capacity{ 0 }, m_name{ other.m_name } {
        *this = other;
    }

    // Copy assignment operator
    Guild& Guild::operator=(const Guild& other) {
        if (this != &other) {
            // Clean up existing members
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;

            m_name = other.m_name;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_members = new Character * [m_capacity];

            // Copy each character
            for (size_t i = 0; i < m_size; ++i) {
                m_members[i] = other.m_members[i]->clone();
            }
        }
        return *this;
    }

    // Move constructor
    Guild::Guild(Guild&& other) noexcept
        : m_members{ other.m_members }, m_size{ other.m_size },
        m_capacity{ other.m_capacity }, m_name{ std::move(other.m_name) } {
        other.m_members = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // Move assignment operator
    Guild& Guild::operator=(Guild&& other) noexcept {
        if (this != &other) {
            // Clean up existing members
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

    // Add a member to the guild
    void Guild::addMember(Character* c) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return; // Avoid adding a duplicate
            }
        }

        if (m_size == m_capacity) {
            resize();
        }

        m_members[m_size++] = c->clone();
    }

    // Remove a member by name
    void Guild::removeMember(const std::string& name) {
        size_t idx = 0;
        while (idx < m_size && m_members[idx]->getName() != name) {
            ++idx;
        }

        if (idx < m_size) {
            delete m_members[idx];
            for (size_t i = idx; i < m_size - 1; ++i) {
                m_members[i] = m_members[i + 1];
            }
            --m_size;
        }
    }

    // Access a member by index
    Character* Guild::operator[](size_t idx) const {
        if (idx < m_size) {
            return m_members[idx];
        }
        return nullptr;
    }

    // Show the guild members
    void Guild::showMembers() const {
        std::cout << "[Guild] " << m_name << std::endl;
        if (m_size == 0) {
            std::cout << "No members in the guild." << std::endl;
        }
        else {
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << std::setw(5) << i + 1 << ": " << *m_members[i] << std::endl;
            }
        }
    }

    // Resize the member array when capacity is reached
    void Guild::resize() {
        m_capacity = (m_capacity == 0) ? 2 : m_capacity * 2;
        Character** new_members = new Character * [m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            new_members[i] = m_members[i];
        }
        delete[] m_members;
        m_members = new_members;
    }

} // namespace seneca
