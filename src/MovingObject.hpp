#ifndef CHARACTER_H
#define CHARACTER_H

#include "DisplayableObject.hpp"

/*
*	A MovingObject can be a player, an enemy, or a moving item, such as a power-up
*/
class MovingObject : public DisplayableObject
{
	public:
		MovingObject(std::string _name, sf::Vector2f _coord, State _state = UNKNOWN);
		MovingObject(std::string _name, float _x, float _y, State _state = UNKNOWN);
		~MovingObject();

		void Init();

		virtual InfoForDisplay GetInfoForDisplay();

		void UpdatePosition(float _dt);
		void UpdateAfterCollision(CollisionDirection _dir);

		void SetVelX(float _x) { m_velocity.x = _x; };
		void SetVelY(float _y) { m_velocity.y = _y; }
		void SetJumpState(JumpState _state) { m_jumpState = _state; };
		void Kill() { m_isDead = true; };
		bool IsDead() { return m_isDead; };
		bool IsInTheAir() { return m_jumpState != ONFLOOR; };

#ifdef DEBUG_MODE
		DebugInfo GetDebugInfo();
#endif


	protected:
		Direction m_facing;

		JumpState m_jumpState;
		State m_previousState; // When in the air, store the previous state for acceleration calculation

		void UpdateAcceleration();
		void UpdateVelocity(float _dt);
		float GetMaxAbsVelocity_X();

		virtual void AddOwnAcceleration() = 0;

		int m_maxSpeed;
		sf::Vector2f m_velocity;
		sf::Vector2f m_acceleration;

		bool m_isRunning;

		bool m_isDead;
};

#endif