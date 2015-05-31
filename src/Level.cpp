/*
Level.cpp: All operations dealing with the XML file representing a level
*/

#include "GraphicsEngine.hpp"

using namespace irr;
using namespace io;

const std::string GraphicsEngine::levelsPath = "../assets/levels/";

bool GraphicsEngine::m_levelLoaded = false; // TEMPORARY


bool GraphicsEngine::LoadLevel(std::string _lvlName)
{
	GraphicsEngine::m_levelLoaded = true;
	bool fileNotEmpty = false;
	std::string lvlFullName = GraphicsEngine::levelsPath + _lvlName + ".xml";
	IrrXMLReader* lvlFile = createIrrXMLReader(lvlFullName.c_str());

	while (lvlFile && lvlFile->read())
	{
		fileNotEmpty = true;
		switch (lvlFile->getNodeType())
		{
			case EXN_ELEMENT:
				if (!strcmp("level", lvlFile->getNodeName()))
					m_currentBackgroundName = GetAttributeValue(lvlFile, "background");
				if (!strcmp("characters", lvlFile->getNodeName()))
					SendCharactersInitialPositions(lvlFile);
				if (!strcmp("foreground", lvlFile->getNodeName()))
					FillListForegroundTileNames(lvlFile);
				break;
			default:
				break;
		}
	}

	if (!fileNotEmpty)
	{
		std::cerr << "Can't read level file " << lvlFullName << std::endl;
		return false;
	}

	delete lvlFile;
	return true;
}

void GraphicsEngine::SendCharactersInitialPositions(irr::io::IrrXMLReader *_lvlFile)
{
	sf::Vector2f tmpCoords;
	InfoForDisplay tmpDisplayInfo;
	EngineEvent tmpEvent;
	bool foundOneCharacter = false;

	while (_lvlFile && _lvlFile->read())
	{
		switch (_lvlFile->getNodeType())
		{
		case EXN_ELEMENT:
			foundOneCharacter = true;
			if (!strcmp("mario", _lvlFile->getNodeName()))
			{
				tmpDisplayInfo.name = "mario";
				tmpDisplayInfo.coordinates.x = GetAttributeValueAsFloat(_lvlFile, "x");
				tmpDisplayInfo.coordinates.y = GetAttributeValueAsFloat(_lvlFile, "y");
				tmpEvent.set(INFO_POS_CHAR, tmpDisplayInfo);
				m_engines["g"]->PushEvent(tmpEvent);
			}
		case EXN_ELEMENT_END:
			if (!foundOneCharacter)
				std::cerr << "No character in level file." << std::endl;
			return;
		default:
			break;
		}
	}
}

void GraphicsEngine::FillListForegroundTileNames(irr::io::IrrXMLReader *_lvlFile)
{
	sf::Vector2f tmpCoords;
	std::string tmpTileName;
	State tmpState;
	bool foundTiles = false;

	while (_lvlFile && _lvlFile->read())
	{
		switch (_lvlFile->getNodeType())
		{
			case EXN_ELEMENT:
				foundTiles = true;
				if (!strcmp("bloc", _lvlFile->getNodeName()))
				{
					tmpCoords.x = GetAttributeValueAsFloat(_lvlFile, "x");
					tmpCoords.y = GetAttributeValueAsFloat(_lvlFile, "y");
					tmpTileName = GetAttributeValue(_lvlFile, "sprite");
					tmpState = GetAttributeValue(_lvlFile, "state", true) == "empty" ? EMPTY : NORMAL;
					DisplayableObject tmpObj(tmpTileName, tmpCoords, tmpState);
					m_listForegroundItemsTileNames[tmpObj] = tmpTileName;
				}
				if (!strcmp("floor_tile", _lvlFile->getNodeName()))
				{
					tmpCoords.x = GetAttributeValueAsFloat(_lvlFile, "x");
					tmpCoords.y = GetAttributeValueAsFloat(_lvlFile, "y");
					tmpTileName = GetAttributeValue(_lvlFile, "sprite");
					DisplayableObject tmpObj(tmpTileName, tmpCoords, NORMAL);
					m_listFloorTileNames[tmpObj] = tmpTileName;
				}
				break;
			case EXN_ELEMENT_END:
				if (!foundTiles)
					std::cerr << "No foreground items in level file." << std::endl;
				return;
			default:
				break;
		}
	}
}

std::string GraphicsEngine::GetAttributeValue(IrrXMLReader *_lvlFile, const char* _name, bool _optionalAttribute)
{
	std::string str(_lvlFile->getAttributeValueSafe(_name));
	if (str == "" && !_optionalAttribute)
		std::cerr << "Can't read attribute " << _name << std::endl;
	return str;
}

float GraphicsEngine::GetAttributeValueAsFloat(IrrXMLReader *_lvlFile, const char* _name)
{
	float ret = _lvlFile->getAttributeValueAsFloat(_name);
	if (ret == -1)
		std::cerr << "Can't read attribute " << _name << std::endl;
	return ret;
}