#include "Agent.h"
#include <Bengine\ResourceManager.h>
#include "Level.h"
#include <algorithm>



Agent::Agent()
{
}


Agent::~Agent()
{
}
bool Agent::collideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePosition;
	//check 4 corners
	//1st 
	
	checkTilePosition(collideTilePosition, levelData, _position.x, _position.y);
	checkTilePosition(collideTilePosition, levelData, _position.x + AGENT_WIDTH, _position.y);
	checkTilePosition(collideTilePosition, levelData, _position.x, _position.y + AGENT_WIDTH);
	checkTilePosition(collideTilePosition, levelData, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);
	
	
	if (collideTilePosition.size() == 0)
	{
		return false;
	}
	for (auto i = 0; i < collideTilePosition.size(); i++)
	{
		collideWithTile(collideTilePosition[i]);
	}
	
	return true;

}
void Agent::draw(Bengine::SpriteBatch& spriteBatch)
{
	
	const glm::vec4 uvRect(0, 0, 1, 1);
	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	


	spriteBatch.draw(destRect, uvRect, m_textureID, 0.0f, _color, m_direction);
}
void Agent::checkTilePosition(std::vector<glm::vec2>& collideTilePosition,
								const std::vector<std::string>& levelData,
								float x, float y)
{
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));


	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].length() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size())
	{
		return;
	}

	if (levelData[cornerPos.y][cornerPos.x] != '.')
	{
		collideTilePosition.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}
//AABB Collision
void Agent::collideWithTile(glm::vec2 tilePos)
{

	
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	
	glm::vec2 centerPlayerPos = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPlayerPos - tilePos;
	float xdepth = MIN_DISTANCE - abs(distVec.x);
	float ydepth = MIN_DISTANCE - abs(distVec.y);

	

	if (xdepth > 0 && ydepth > 0)
	{
		if (std::max(xdepth, 0.0f) < std::max(ydepth, 0.0f))
		{
			if (distVec.x < 0)
			{
				_position.x -= xdepth;
			}
			else{
				_position.x += xdepth;
			}
		}
		else{
			if (distVec.y < 0)
			{
				_position.y -= ydepth;
			}
			else{
				_position.y += ydepth;
			}
		}
	}
}
bool Agent::collideWithAgent(Agent* agent)
{

	const float MIN_DISTANCE = AGENT_RADIUS * 2.0f;
	glm::vec2 centerPosA = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVect = centerPosA - centerPosB;

	float distance = glm::length(distVect);
	float collisionDepth = MIN_DISTANCE - distance;
	if (collisionDepth > 0)
	{
		glm::vec2 collisionDepthVec = glm::normalize(distVect) * collisionDepth;
		_position += collisionDepthVec / 2.0f;
		agent->_position -= collisionDepthVec /2.0f;
		return true;
	}
	return false;



}

bool Agent::applyDamage(float damage)
{
	_health -= damage;
	if (_health <= 0)
	{
		return true;
	}
	return false;

}