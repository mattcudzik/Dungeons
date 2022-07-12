#include "Animation.h"

#include "TextureHandler.h";
#include "Level.h"

//TMP
Animation::Animation(int animNumber, sf::Vector2i size): currentFrame(0), frameTime(1.0f/8.0f)
{
	for (int i = 0; i < 4; i++)
	{
		frames.push_back(sf::IntRect(size.x * i, animNumber * size.y, size.x, size.y));
	}
}
sf::IntRect& Animation::GetNextFrame()
{
	currentFrame++;
	if (currentFrame >= frames.size())
		currentFrame = 0;
	return frames[currentFrame];
}
void Animation::ResetAnimation()
{
	this->currentFrame = 0;
}