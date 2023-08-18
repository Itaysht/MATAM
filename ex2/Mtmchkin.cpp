  //
// Created by itay on 06/05/2022.
//
#include "Mtmchkin.h"

const int MAX_LEVEL = 10;

Card *Mtmchkin::allocateCardsArray(const Card *cardsArray, int numOfCards)
{
    Card* temp = new Card[numOfCards];
    for (int i=0; i < numOfCards; i++)
    {
        temp[i] = cardsArray[i];
    }
    return temp;
}

Mtmchkin::Mtmchkin(const char *playerName, const Card *cardsArray, int numOfCards) :
        m_player(Player(std::string(playerName))), m_cards_array(allocateCardsArray(cardsArray, numOfCards)),
        m_size(numOfCards), m_index(0), m_game_status(GameStatus::MidGame)
{}

Mtmchkin::~Mtmchkin()
{
    delete[] m_cards_array;
}

Mtmchkin::Mtmchkin(const Mtmchkin &other) :
        m_player(other.m_player), m_cards_array(allocateCardsArray(other.m_cards_array, other.m_size)),
        m_size(other.m_size), m_index(0), m_game_status(GameStatus::MidGame)
{}

Mtmchkin &Mtmchkin::operator=(const Mtmchkin &other)
{
    if (this == &other)
    {
        return *this;
    }
    delete[] m_cards_array;
    m_player = other.m_player;
    m_cards_array = allocateCardsArray(other.m_cards_array, other.m_size);
    m_size = other.m_size;
    m_index = 0;
    m_game_status = GameStatus::MidGame;
    return *this;
}

GameStatus Mtmchkin::getGameStatus() const
{
    return this->m_game_status;
}

void Mtmchkin::playNextCard()
{
    Card playingCard = m_cards_array[m_index];
    playingCard.printInfo();
    playingCard.applyEncounter(m_player);
    if (m_player.getLevel() == MAX_LEVEL)
    {
        m_game_status = GameStatus::Win;
    }
    if (m_player.isKnockedOut())
    {
        m_game_status = GameStatus::Loss;
    }
    m_player.printInfo();
    m_index++;
    if (m_index == m_size)
    {
        m_index = 0;
    }
}

bool Mtmchkin::isOver() const
{
    if (GameStatus::MidGame == m_game_status)
    {
        return false;
    }
    return true;
}
