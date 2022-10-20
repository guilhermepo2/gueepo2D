#include "gueepo2Dpch.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "Audio.h"
#include "core/Containers/string.h"

namespace gueepo {

	ma_engine* Audio::m_audioEngine = nullptr;

	void Audio::Init() {
		ma_result result;
		m_audioEngine = new ma_engine;

		result = ma_engine_init(nullptr, m_audioEngine);

		if (result != MA_SUCCESS) {
			LOG_ERROR("error initializing the audio engine!");
			delete m_audioEngine;
			return;
		}
	}

	void Audio::Play(AudioClip* audioClip) {
		g2dassert(m_audioEngine != nullptr, "can't play an audio without initializing the audio engine!");
		g2dassert(audioClip != nullptr && audioClip->audioClip != nullptr, "there's something wrong here");

		ma_sound_start(audioClip->audioClip[audioClip->currentClip]);
		audioClip->AdvanceClip();
	}

	void Audio::Shutdown() {
		if (m_audioEngine != nullptr) {
			ma_engine_uninit(m_audioEngine);
			delete m_audioEngine;
		}
	}

	gueepo::AudioClip* Audio::CreateAudioClip(gueepo::string path) {
		g2dassert(m_audioEngine != nullptr, "can't create an audio clip without initializing the audio engine!");

		ma_result result;
		ma_sound* newSound = new ma_sound;
		result = ma_sound_init_from_file(m_audioEngine, path, 0, nullptr, nullptr, newSound);

		if (result != MA_SUCCESS) {
			LOG_INFO("error creating audio clip: {0}", path);
			delete newSound;
			return nullptr;
		}



		AudioClip* newClip = new AudioClip;
		newClip->currentClip = 0;
		newClip->audioClip[0] = newSound;

		for (int i = 1; i < MA_SOUND_AMOUNT; i++) {
			ma_sound* iSound = new ma_sound;
			ma_sound_init_from_file(m_audioEngine, path, 0, nullptr, nullptr, iSound);
			newClip->audioClip[i] = iSound;
		}

		return newClip;
	}

	void Audio::DestroyAudioClip(AudioClip* clip) {
		if (clip != nullptr) {
			for (int i = 0; i < MA_SOUND_AMOUNT; i++) {
				ma_sound_uninit(clip->audioClip[i]);
				delete clip->audioClip[i];
			}

			delete clip;
		}
	}

	void AudioClip::AdvanceClip() {
		currentClip = (currentClip + 1) % MA_SOUND_AMOUNT;
	}

}