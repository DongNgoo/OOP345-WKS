#include "team.h"
#include <utility>
#include "iostream"
#include "character.h"
using namespace std;
namespace seneca {

    
    Team::Team(const char* name) : m_name{name} { }

   
    Team::Team(const Team& other) : Team() {
		*this = other;
	}
    Team& Team::operator=(const Team& other) {
        if (this != &other) {
        {
            cleanup();

            this->m_name = other.m_name;
			this->m_cnt = other.m_cnt;
            if (other.m_cnt > 0u) 
            {
            this->m_members = new Character * [other.m_cnt];}
			for (size_t i = 0; i < other.m_cnt; ++i) 
			{this->m_members[i] = other.m_members[i]->clone();}
            }
        }
        return *this;
    }
    Team::Team(Team&& other) noexcept : Team()
    {
		*this = std::move(other);
    }
    Team& Team::operator=(Team&& other) noexcept
    {
        if (this != &other)
        {
			cleanup();
            this->m_cnt = other.m_cnt;
            this->m_name = other.m_name;

			this->m_members = other.m_members;
            other.m_members = {};
            other.m_cnt = {};
            other.m_name = {};
        }
		return *this;
    }
    Team::~Team()
    {
        cleanup();
    }
    void Team::addMember(const Character* c)
    {
        for (size_t i = 0; i < m_cnt; ++i)
            if (m_members[i]->getName() == c->getName())
                return;

        Character** tmp = new Character * [m_cnt + 1];
        for(size_t i = 0; i < m_cnt; ++i)
            tmp[i] = m_members[i];
        tmp[m_cnt] = c->clone();

		delete[] m_members;
		m_members = tmp;
		++m_cnt;

    }

    void Team::removeMember(const std::string& name)
    {
        size_t idx = 0;
        while (idx < m_cnt && m_members[idx]->getName() != name)
            ++idx;

		if (idx < m_cnt)
		{
            Character** tmp = new Character * [m_cnt - 1];
			for (size_t i = 0; i < idx; ++i)
				tmp[i] = m_members[i];

			for (size_t i = idx + 1; i < m_cnt; ++i)
				tmp[i - 1] = m_members[i];

			delete[] m_members;
			m_members = tmp;
			--m_cnt;
		}

	}
    
    Character* Team::operator[](size_t idx) const {
        if (idx < m_cnt) {
            return m_members[idx];
        }
        return nullptr; // Out of bounds
    }

    void Team::showMembers() const {
        std::cout << "[Team] " << m_name << std::endl;
        if (m_cnt == 0) {
            std::cout << "No team." << std::endl;
        }
        else {
            for (size_t i = 0; i < m_cnt; ++i) {
                std::cout << (i + 1) << ": " << *m_members[i] << std::endl; // Use operator<< defined for Character
            }
        }
    }

}