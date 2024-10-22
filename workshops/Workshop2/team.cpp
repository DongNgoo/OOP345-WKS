#include "team.h"

namespace seneca {

    void Team::cleanup() {
        for (size_t i = 0; i < m_cnt; ++i)
            delete m_members[i];  // Delete each character

        delete[] m_members;  // Free the dynamic array
        m_members = nullptr;
        m_cnt = 0;
        m_name.clear();
    }

    Team::Team() = default;

    Team::Team(const char* name) : m_name{ name } {}

    Team::Team(const Team& other) : Team() {
        *this = other;  // Delegate to copy assignment operator
    }

    Team& Team::operator=(const Team& other) {
        if (this != &other) {
            cleanup();  // Free existing resources

            m_name = other.m_name;
            m_cnt = other.m_cnt;

            if (other.m_cnt > 0) {
                m_members = new Character * [other.m_cnt];
                for (size_t i = 0; i < other.m_cnt; ++i) {
                    m_members[i] = other.m_members[i]->clone();  // Clone each character
                }
            }
        }
        return *this;
    }

    Team::Team(Team&& other) noexcept : Team() {
        *this = std::move(other);  // Delegate to move assignment operator
    }

    Team& Team::operator=(Team&& other) noexcept {
        if (this != &other) {
            cleanup();  // Free existing resources

            m_cnt = other.m_cnt;
            m_name = std::move(other.m_name);
            m_members = other.m_members;

            other.m_members = nullptr;
            other.m_cnt = 0;
        }
        return *this;
    }

    Team::~Team() {
        cleanup();
    }

    void Team::addMember(const Character* c) {
        // Check if the team already has a character with the same name
        for (size_t i = 0; i < m_cnt; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return;  // Character with the same name exists, so don't add
            }
        }

        // If no duplicate is found, create a copy of the character using clone()
        Character* newMember = c->clone();

        // Resize the members array to accommodate the new member
        Character** tmp = new Character * [m_cnt + 1];
        for (size_t i = 0; i < m_cnt; ++i) {
            tmp[i] = m_members[i];  // Copy existing members
        }
        tmp[m_cnt] = newMember;  // Add the new member at the end

        // Delete the old members array and update the team
        delete[] m_members;
        m_members = tmp;
        ++m_cnt;
    }

    void Team::removeMember(const std::string& name) {
        size_t idx = 0;
        while (idx < m_cnt && m_members[idx]->getName() != name) {
            ++idx;
        }

        if (idx < m_cnt) {
            Character** tmp = new Character * [m_cnt - 1];
            for (size_t i = 0; i < idx; ++i) {
                tmp[i] = m_members[i];
            }
            for (size_t i = idx + 1; i < m_cnt; ++i) {
                tmp[i - 1] = m_members[i];
            }

            delete m_members[idx];
            delete[] m_members;
            m_members = tmp;
            --m_cnt;
        }
    }

    Character* Team::operator[](size_t idx) const {
        return (idx < m_cnt) ? m_members[idx] : nullptr;
    }

    void Team::showMembers() const {
        if (!m_name.empty()) {
            std::cout << "[Team] " << m_name << "\n";
            for (size_t i = 0; i < m_cnt; ++i) {
                std::cout << std::setw(5) << i + 1 << ": " << *m_members[i] << "\n";
            }
        }
        else {
            std::cout << "No team.\n";
        }
    }

}
