#pragma once
#include <map>
#include <vector>

#include "GameSprite.h"

class AnimatedGameSprite : public GameSprite
{
public:
	AnimatedGameSprite();
	AnimatedGameSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height,
					   int posX, int posY, float timeToUpdate, float scale = 1.0f);
	~AnimatedGameSprite();

	void PlayAnimation(const std::string& animation, bool once = false);
	virtual void Update(float elapsedTime);
	virtual void Draw(Graphics& graphics);

protected:
	double timeToUpdate;
	bool currentAnimationOnce;
	std::string currentAnimation;

	void SetVisible(bool visible);

	void AddAnimation(const std::string& animationName, int frames, int x, int y, int width, int height, sf::Vector2f offset);
	void ResetAnimations();
	void StopAnimation();

	virtual void SetupAnimations() = 0;
	virtual void AnimationDone(const std::string& currentAnimation) = 0;

private:
	std::map<std::string, std::vector<sf::IntRect> > animations;
	std::map<std::string, sf::Vector2f> offsets;

	int frameIndex;
	float timeElapsed;
	bool visible;
};