//
// Created by itay on 21/05/2022.
//

#ifndef HEALTHPOINTS_H
#define HEALTHPOINTS_H

#include <iostream>

class HealthPoints{
    int m_currentHealthPoints;
    int m_maxHealthPoints;

public:
    HealthPoints(int healthPoints = 100);
    HealthPoints(const HealthPoints& hp) = default;
    ~HealthPoints() = default;
    HealthPoints& operator=(const HealthPoints&) = default;
    HealthPoints& operator+=(int hp);
    HealthPoints& operator-=(int hp);
    HealthPoints operator+(int hp2) const;
    HealthPoints operator-(int hp2) const;

    friend bool operator==(const HealthPoints& hp1, const HealthPoints& hp2);
    friend bool operator<(const HealthPoints& hp1, const HealthPoints& hp2);
    friend std::ostream& operator<<(std::ostream& os, const HealthPoints& hp);

    class InvalidArgument {};
};

HealthPoints operator+(int hp2, const HealthPoints& hp1);
bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator>(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2);

#endif // HEALTHPOINTS_H
