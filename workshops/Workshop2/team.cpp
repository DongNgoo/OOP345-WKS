#include "team.h"
#include <iostream>
#include <iomanip>
#include "character.h"

using namespace std;

namespace seneca {
    Team::Team(const char* name) : m_name{ name }, m_cnt{ 0 }, m_members{ nullptr } { }

    Team::Team(const Team& other) : Team() {
        *this = other;
    }

    Team& Team::operator=(const Team& other) {
        if (this != &other) {
            cleanup();
            this->m_cnt = other.m_cnt;
            this->m_name = other.m_name;
            if (other.m_cnt > 0u) {
                this->m_members = new Character * [m_cnt];
                for (size_t i = 0u; i < m_cnt; ++i)
                    this->m_members[i] = other.m_members[i]->clone();
            }
        }
        return *this;
    }

    Team::Team(Team&& other) noexcept : Team() {
        *this = std::move(other);
    }

    Team& Team::operator=(Team&& other) noexcept {
        if (this != &other) {
            cleanup();
            this->m_cnt = other.m_cnt;
            this->m_name = std::move(other.m_name);

            this->m_members = other.m_members;
            other.m_members = nullptr;
            other.m_cnt = 0;
        }
        return *this;
    }

    Team::~Team() {
        cleanup();
    }

    void Team::addMember(const Character* c) {
        for (size_t i = 0; i < m_cnt; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return;  // Prevent duplicate members
            }
        }

        Character** tmp = new Character * [m_cnt + 1];
        for (size_t i = 0u; i < m_cnt; ++i) {
            tmp[i] = m_members[i];
        }
        tmp[m_cnt] = c->clone();
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
            delete m_members[idx];
            Character** tmp = new Character * [m_cnt - 1];
            for (size_t i = 0u; i < idx; ++i) {
                tmp[i] = m_members[i];
            }
            for (size_t i = idx; i < m_cnt - 1; ++i) {
                tmp[i] = m_members[i + 1];
            }
            delete[] m_members;
            m_members = tmp;
            --m_cnt;
        }
    }

    Character* Team::operator[](size_t idx) const {
        if (idx < m_cnt) {
            return m_members[idx];
        }
        return nullptr;
    }

    void Team::showMembers() const {
        if (!m_name.empty()) {
            cout << "[Team] " << m_name << "\n";
            for (size_t i = 0u; i < m_cnt; ++i) {
                cout << std::setw(5) << i + 1 << ": " << *m_members[i] << "\n";
            }
        }
        else {
            cout << "No team.\n";
        }
    }

    void Team::cleanup() {
        for (size_t i = 0u; i < m_cnt; i++) {
            delete m_members[i];
        }
        delete[] m_members;
        m_members = nullptr;
        m_cnt = 0;
    }
}
