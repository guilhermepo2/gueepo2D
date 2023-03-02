#include "SpriteAnimation.h"

namespace gueepo {
	void SpriteAnimation_Update(SpriteAnimation& anim, float DeltaTime) {
		if (anim.animationFrames.size() == 0) {
			return;
		}

		anim.timeElapsed += DeltaTime;

		if (anim.timeElapsed >= anim.animationFrames[anim.currentFrame].timeOnThisFrame) {
			anim.timeElapsed -= anim.animationFrames[anim.currentFrame].timeOnThisFrame;

			if (anim.shouldLoop) {
				anim.currentFrame = (anim.currentFrame + 1) % anim.animationFrames.size();
			}
			else {
				anim.currentFrame += 1;
				if (anim.currentFrame >= anim.animationFrames.size()) {
					anim.currentFrame = anim.animationFrames.size() - 1;
					anim.animationEnded = true;
				}
			}
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

	void SpriteAnimation::Reset() {
		currentFrame = 0;
		timeElapsed = 0.0f;
		animationEnded = false;
	}

}
