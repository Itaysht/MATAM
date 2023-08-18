//
// Created by itay on 21/05/2022.
//
#include "HealthPoints.h"

HealthPoints::HealthPoints(const int healthPoints)
{
    if (healthPoints <= 0){
        throw InvalidArgument();
    }
    m_currentHealthPoints = healthPoints;
    m_maxHealthPoints = healthPoints;
}

HealthPoints &HealthPoints::operator+=(int hp)
{
    m_currentHealthPoints += hp;
    if (m_maxHealthPoints < m_currentHealthPoints)
    {
        m_currentHealthPoints = m_maxHealthPoints;
    }
    else
    {
        if (m_currentHealthPoints < 0)
        {
            m_currentHealthPoints = 0;
        }
    }
    return *this;
}

HealthPoints &HealthPoints::operator-=(int hp)
{
    this->operator+=((-1)*hp);
    return *this;
}

HealthPoints HealthPoints::operator+(int hp2) const
{
    HealthPoints hp3 = *this;
    hp3 += hp2;
    return hp3;
}

HealthPoints operator+(int hp2, const HealthPoints &hp1)
{
    return (hp1 + hp2);
}

HealthPoints HealthPoints::operator-(int hp2) const
{
    HealthPoints hp3 = *this;
    hp3 -= hp2;
    return hp3;
}

bool operator==(const HealthPoints& hp1, const HealthPoints& hp2)
{
    if (hp1.m_currentHealthPoints == hp2.m_currentHealthPoints)
    {
        return true;
    }
    return false;
}

bool operator<(const HealthPoints& hp1, const HealthPoints& hp2)
{
    if (hp1.m_currentHealthPoints < hp2.m_currentHealthPoints)
    {
        return true;
    }
    return false;
}

bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2)
{
    if (hp1 == hp2)
    {
        return false;
    }
    return true;
}

bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2)
{
    if (hp1 < hp2)
    {
        return false;
    }
    return true;
}

bool operator>(const HealthPoints& hp1, const HealthPoints& hp2)
{
    if (hp2 < hp1)
    {
        return true;
    }
    return false;
}

bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2)
{
    if (hp2 < hp1)
    {
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& hp)
{
    return os << hp.m_currentHealthPoints << "(" << hp.m_maxHealthPoints << ")";
}