//
// Created by Itay on 05/05/2022.
//

#include "Card.h"

Card::Card(CardType type, const CardStats& stats) : m_effect(type), m_stats(CardStats())
{
    m_stats.buff = stats.buff;
    m_stats.cost = stats.cost;
    m_stats.force = stats.force;
    m_stats.heal = stats.heal;
    m_stats.hpLossOnDefeat = stats.hpLossOnDefeat;
    m_stats.loot = stats.loot;
}

void Card::applyEncounter(Player &player) const
{
    if (m_effect == CardType::Battle)
    {
        bool win = player.getAttackStrength() >= m_stats.force;
        if (win)
        {
            player.levelUp();
            player.addCoins(m_stats.loot);
        }
        else
        {
            player.damage(m_stats.hpLossOnDefeat);
        }
        printBattleResult(win);
        return;
    }
    if (m_effect == CardType::Buff)
    {
        if (player.pay(m_stats.cost))
        {
            player.buff(m_stats.buff);
        }
        return;
    }
    if (m_effect == CardType::Heal)
    {
        if (player.pay(m_stats.cost))
        {
            player.heal(m_stats.heal);
        }
        return;
    }
    if (m_effect == CardType::Treasure)
    {
        player.addCoins(m_stats.loot);
    }
}

void Card::printInfo() const
{
    if (m_effect == CardType::Battle)
    {
        printBattleCardInfo(m_stats);
        return;
    }
    if (m_effect == CardType::Buff)
    {
        printBuffCardInfo(m_stats);
        return;
    }
    if (m_effect == CardType::Heal)
    {
        printHealCardInfo(m_stats);
        return;
    }
    if (m_effect == CardType::Treasure)
    {
        printTreasureCardInfo(m_stats);
        return;
    }
}