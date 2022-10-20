#pragma once

struct ma_engine;
struct ma_sound;

// Why do we have multiple ma_sound* in an AudioClip?
// https://github.com/mackron/miniaudio/issues/249
// "Each time you want to play a sound, even if it's the same underlying sound file, you need a separate ma_sound object."
// Important: "The underlying sound data is reference counted which means the sound file will only be loaded once."
#define MA_SOUND_AMOUNT 5

namespace gueepo {

	class string;

	class AudioClip {
	public:
		ma_sound* audioClip[MA_SOUND_AMOUNT];
		int currentClip;

		void AdvanceClip();
	};

	class Audio {
	public:
		static void Init();
		static void Play(AudioClip* audioClip);
		static void Shutdown();

		static AudioClip* CreateAudioClip(gueepo::string path);
		static void DestroyAudioClip(AudioClip* clip);
	private:
		static ma_engine* m_audioEngine;
	};
}