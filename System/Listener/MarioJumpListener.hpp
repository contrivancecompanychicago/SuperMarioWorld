#ifndef MARIO_JUMP_LISTENER_H
#define MARIO_JUMP_LISTENER_H

#include "../EventEngine/Event.hpp"
#include "../EventEngine/EventListener.hpp"
#include "../../Sound/SoundEngine.hpp"
#include <string>

/**
* @author Kevin Guillaumond <kevin.guillaumond@gmail.com>
*/
class MarioJumpListener : public EventListener
{
	public:
		MarioJumpListener(SoundEngine* _soundEngine);

		/**
		* Called when an mario_jump event is dispatched
		* @param string eventType Type of received event
		* @param Event* event
		*/
		void onEvent(const std::string &_eventType, Event* _event);

	private:
		SoundEngine* m_soundEngine;
};

#endif // MARIO_JUMP_LISTENER_H
