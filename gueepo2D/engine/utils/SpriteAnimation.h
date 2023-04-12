//
// SpriteAnimation.h
// @description Sprite Animation handles having an array of textures and transitioning between them.
//
// --------------------------------------------------------------------
// #todo: maybe should a function callback to the AnimationFrame?
// --------------------------------------------------------------------

#pragma once
#include "core/containers/vector.h"

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
		bool shouldLoop = true;
		bool animationEnded = false;

		void AddAnimationFrame(TextureRegion* texRegion, float timeOnFrame);
		TextureRegion* GetCurrentFrameTextureRegion();
		void Reset();
	};

	// ----------------------------------------------
	// I *could* have a Update(float DeltaTime) function on the SpriteAnimation, and do something like myAnimation.Update(DeltaTime)
	// but having it like this makes it more data-oriented friendly, I believe. 
	// It just sucks that it's literally the only thing in the engine that works like that.
	void SpriteAnimation_Update(SpriteAnimation& anim, float DeltaTime);
}