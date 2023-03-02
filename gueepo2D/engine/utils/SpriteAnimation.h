#pragma once
#include "core/containers/vector.h"

// --------------------------------------------------------------------
// #todo: maybe should add a "ShouldLoop" boolean to SpriteAnimation?
// #todo: maybe should a function callback to the AnimationFrame?
// --------------------------------------------------------------------

namespace gueepo {

	class Texture;
	class TextureRegion;

	union Sprite {
		Texture* texture;
		TextureRegion* textureRegion = nullptr;
	};

	struct AnimationFrame {
		Sprite sprite;
		float timeOnThisFrame = 0.0f;
	};

	struct SpriteAnimation {
	public:
		vector<AnimationFrame> animationFrames;
		int currentFrame = 0;
		float timeElapsed = 0.0f;

		void AddAnimationFrame(TextureRegion* texRegion, float timeOnFrame);
		TextureRegion* GetCurrentFrameTextureRegion();
	};

	// ----------------------------------------------
	// I *could* have a Update(float DeltaTime) function on the SpriteAnimation, and do something like myAnimation.Update(DeltaTime)
	// but having it like this makes it more data-oriented friendly, I believe.
	void SpriteAnimation_Update(SpriteAnimation& anim, float DeltaTime);
}