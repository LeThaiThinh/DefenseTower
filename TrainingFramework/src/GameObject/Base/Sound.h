#pragma once
#include <string>
#include "irrKlang.h"
#include "utilities.h"
#define SOUND_DISTANCE_UNIT 400
class Sound
{
public:
	static irrklang::ISoundEngine* engine ;
	Sound(const std::string& path) {
		InitSound(path);
	};
	void InitSound(const std::string& path);
	void PlaySoundFromStart2D(bool playLooped);
	void PlaySoundFromStart(bool playLooped, irrklang::vec3df pos);
	void PlaySoundContinue();
	void PlayLoop(bool playLooped);
	void Pause(bool pause);

	void Volumn(float volumn);

private:
	irrklang::ISound* sound;
	std::string m_path;
};

