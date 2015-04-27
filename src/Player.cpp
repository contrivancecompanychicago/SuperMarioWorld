#include "Player.hpp"

Player::Player(std::string _name, sf::Vector2f _coord) : MovingObject(_name, _coord)
{
	Init();
}

Player::Player(std::string _name, float _x, float _y) : MovingObject(_name, _x, _y)
{
	Init();
}

void Player::Init()
{
	m_facing = DRIGHT;
	m_isRunning = false;
	m_isJumping = false;
}

Player:: ~Player()
{

}

InfoForDisplay Player::GetInfoForDisplay()
{
	m_reverseSprite = (m_facing == DLEFT);
	return MovingObject::GetInfoForDisplay();
}

void Player::AddOwnAcceleration()
{
	switch (m_state)
	{
		case WALK:
			m_acceleration.x = PhysicsConstants::PlayerAcc_Walk * (m_facing == DLEFT ? -1 : 1);
			break;
		case RUN:
			m_acceleration.x = PhysicsConstants::PlayerAcc_Run * (m_facing == DLEFT ? -1 : 1);
			break;
	}
}

void Player::ToggleRun(bool _mustRun)
{
	if (_mustRun && m_state == WALK)
		m_state = RUN;
	if (!_mustRun && m_state == RUN)
		m_state = WALK;
	m_isRunning = _mustRun;
}

void Player::Move(int _a)
{
	if (_a > 0)
	{
		if (m_facing == DLEFT)
			m_velocity.x = 0; // Player should skid
		m_facing = DRIGHT;

		m_state = m_isRunning ? RUN : WALK;
	}
	else if (_a < 0)
	{
		if (m_facing == DRIGHT)
			m_velocity.x = 0; // Player should skid
		m_facing = DLEFT;

		m_state = m_isRunning ? RUN : WALK;
	}
	else
		m_state = STATIC;
}

void Player::Jump()
{

}