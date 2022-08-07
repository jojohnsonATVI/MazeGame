#include <iostream>

#include "Player.h"
#include "Key.h"
#include "AudioManager.h"

using namespace std;

constexpr int kStartingNumberOfLives = 3;

Player::Player()
	: PlacableActor(0, 0)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_lives(kStartingNumberOfLives)
{

}

bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = key;
}

void Player::UseKey()
{
	if (m_pCurrentKey)
	{
		m_pCurrentKey->Remove();
		m_pCurrentKey = nullptr;
	}
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		AudioManager::GetInstance()->PlayKeyDropSound();
		m_pCurrentKey->Place(m_pPosition->x - (m_lastDirection == LAST_DIRECTION::RIGHT) + (m_lastDirection == LAST_DIRECTION::LEFT), m_pPosition->y - (m_lastDirection == LAST_DIRECTION::UP) + (m_lastDirection == LAST_DIRECTION::DOWN));
		m_pCurrentKey = nullptr;
	}
}

void Player::SetPosition(int x, int y)
{
	if (x < m_pPosition->x && y == m_pPosition->y)
	{
		m_lastDirection = LAST_DIRECTION::LEFT;
	}
	else if (x == m_pPosition->x && y > m_pPosition->y)
	{
		m_lastDirection = LAST_DIRECTION::UP;
	}
	else if (x == m_pPosition->x && y < m_pPosition->y)
	{
		m_lastDirection = LAST_DIRECTION::DOWN;
	}
	else
	{
		m_lastDirection = LAST_DIRECTION::RIGHT;
	}

	PlacableActor::SetPosition(x, y);
}

void Player::Draw()
{
	cout << "@";
}
