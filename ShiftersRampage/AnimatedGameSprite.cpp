#include "AnimatedGameSprite.h"



AnimatedGameSprite::AnimatedGameSprite() :
	GameSprite(),
	timeToUpdate(0.0f),
	currentAnimation(""),
	currentAnimationOnce(false),
	frameIndex(0),
	timeElapsed(0.0f),
	visible(false)
{
}

AnimatedGameSprite::AnimatedGameSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height,
									   int posX, int posY, float timeToUpdate, float scale) :
	GameSprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY, scale),
	timeToUpdate(timeToUpdate),
	currentAnimation(""),
	currentAnimationOnce(false),
	frameIndex(0),
	timeElapsed(0.0f),
	visible(true)
{}

AnimatedGameSprite::~AnimatedGameSprite()
{
}

void AnimatedGameSprite::PlayAnimation(const std::string& animation, bool once)
{
	currentAnimationOnce = once;

	if (currentAnimation != animation)
	{
		currentAnimation = animation;
		frameIndex = 0;
	}
}

void AnimatedGameSprite::Update(float elapsedTime)
{
	GameSprite::Update(elapsedTime);

	timeElapsed += elapsedTime;

	if (timeElapsed > timeToUpdate)
	{
		timeElapsed -= timeToUpdate;

		if (frameIndex < animations[currentAnimation].size() - 1)
			frameIndex++;
		else
		{
			frameIndex = 0;
			AnimationDone(currentAnimation);
		}
	}
}

void AnimatedGameSprite::Draw(Graphics& graphics)
{
	if (visible)
	{
		sourceRect = animations[currentAnimation][frameIndex];
		graphics.BlitSurface(sprite, sourceRect);
	}
}

void AnimatedGameSprite::SetVisible(bool visible) { this->visible = visible; }

void AnimatedGameSprite::AddAnimation(const std::string& animationName, int frames, int x, int y, int width, int height, sf::Vector2f offset)
{
	std::vector<sf::IntRect> rectangles;

	for (int i = 0; i < frames; i++)
	{
		sf::IntRect rectangle;

		rectangle.left = (i * width) + x;
		rectangle.top = y;
		rectangle.width = width;
		rectangle.height = height;

		rectangles.push_back(rectangle);
	}

	animations.insert(std::pair<std::string, std::vector<sf::IntRect> >(animationName, rectangles));
	offsets.insert(std::pair<std::string, sf::Vector2f>(animationName, offset));
}

void AnimatedGameSprite::ResetAnimations()
{
	animations.clear();
	offsets.clear();
}

void AnimatedGameSprite::StopAnimation()
{
	frameIndex = 0;
	AnimationDone(currentAnimation);
}