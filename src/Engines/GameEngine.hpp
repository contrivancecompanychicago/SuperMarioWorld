#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Engine.hpp"
#include "../Characters/Player.hpp"
#include "../Items/Box.hpp"
#include "../Characters/Goomba.hpp"
#include "../Items/Pipe.hpp"
#include "../irrXML/irrXML.h"

/*
    Game engine: Handles the movements of the player, collisions, etc.
*/
class GameEngine : public Engine
{
    public:
        GameEngine(Game *_g);
        ~GameEngine();

		void Frame();
		void Frame(float _dt);

    private:
		bool m_levelStarted;

		sf::Vector2f m_initPosMario;
		int m_indexMario; // Index of Mario in m_characters. -1 if he's not in it.

		std::vector<MovingObject*> m_characters;
		std::map<unsigned int, DisplayableObject*> m_listForegroundItems; // Part of the level the characters can be in collision with. Pointers stored to allow polymorphism.

		void ProcessEvent(EngineEvent& _event);
		void HandlePressedKey(sf::Keyboard::Key _key);
		bool CanRespawnMario();
		void HandleReleasedKey(sf::Keyboard::Key _key);

		void CheckCharacterDeath(MovingObject& _character);
		void KillCharacter(MovingObject& _character);
		void SendCharacterPosition(int _indexCharacter);

		/*
		 *	Collisions
		 */
		void UpdateCharacterPosition(MovingObject& _character, float _dt);
		void HandleCollisionsWithMapEdges(MovingObject& _obj);
		void HandleCollisionsWithLevel(MovingObject& _obj);
		CollisionDirection HandleCollisionWithRect(unsigned int _objId, sf::FloatRect _ref);
		CollisionDirection DetectCollisionWithRect(unsigned int _objId, sf::FloatRect _ref);
		void ReactToCollision(unsigned int _objId, sf::FloatRect _ref, CollisionDirection _direction);

		void StartLevel(std::string _lvlName);
		int AddCharacterToArray(MovingObject *_character);

		/* 
		 * XML Level 
		 */
		irr::io::IrrXMLReader *m_lvlFile;

		bool LoadLevel(std::string _lvlName);
		void StoreCharactersInitialPositions();
		void StoreListForegroundTileNames();
		void StoreBox();
		void StorePipe();
		PipeType GetPipeTypeFromXML();
		void StoreFloor();

		std::string GetAttributeValue(const char* _name, bool _optionalAttribute = false);
		float GetAttributeValueAsFloat(const char* _name);
		int GameEngine::GetAttributeValueAsInt(const char* _name);
		void SendInfoPosLvlToGFX(InfoForDisplay _info);
		void GetCoordinatesAndTileName(sf::Vector2f *_coords, std::string *_tileName);

		bool m_deathSoundIsPlaying; // No input is taken into account while this sound is playing [see sound engine]

		static const std::string levelsPath;
};

#endif // GAMEENGINE_H