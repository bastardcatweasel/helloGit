#include "Agent.h"
#include <Bengine\ResourceManager.h>
#include "Level.h"

Agent::Agent()
{
}


Agent::~Agent()
{
}
void Agent::collideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePosition;
	//check 4 corners

	glm::ivec2 cornerPos1 = glm::ivec2(floor(_position.x / (float)TILE_WIDTH),
									  floor(_position.y / (float)TILE_WIDTH));


	


}
void Agent::draw(Bengine::SpriteBatch& spriteBatch)
{
	static int textureID = Bengine::ResourceManager::getTexture("Textures/circle.png").id;
	const glm::vec4 uvRect(0, 0, 1, 1);
	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;



	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
}