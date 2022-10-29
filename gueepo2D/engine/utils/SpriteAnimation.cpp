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
}
