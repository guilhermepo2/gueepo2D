#pragma once

struct ma_engine;
struct ma_sound;

namespace gueepo {

	class string;

	class AudioClip {
	public:
		ma_sound* audioClip = nullptr;
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