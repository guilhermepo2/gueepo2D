#include <gueepo2Dpch.h>
#include "SpriteAnimation.h"

namespace gueepo {
	void SpriteAnimation_Update(SpriteAnimation& anim, float DeltaTime) {
		anim.timeElapsed += DeltaTime;

		if (anim.timeElapsed >= anim.animationFrames[anim.currentFrame].timeOnThisFrame) {
			anim.timeElapsed -= anim.animationFrames[anim.currentFrame].timeOnThisFrame;
			anim.currentFrame = (anim.currentFrame + 1) % anim.animationFrames.size();
		}

	}

	void SpriteAnimation::AddAnimationFrame(TextureRegion* texRegion, float timeOnFrame) {
		AnimationFrame frame;
		frame.sprite.textureRegion = texRegion;
		frame.timeOnThisFrame = timeOnFrame;

		animationFrames.add(frame);
	}

	gueepo::TextureRegion* SpriteAnimation::GetCurrentFrameTextureRegion() {
		return animationFrames[currentFrame].sprite.textureRegion;
	}

}
