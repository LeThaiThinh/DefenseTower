#pragma once
#include "Sound.h"
#include "ResourceManagers.h"
class BackgroundMusic:public CSingleton<BackgroundMusic>
{
public:
	BackgroundMusic() {
		m_ingame = ResourceManagers::GetInstance()->GetSound("torch.mp3");
		m_menu = ResourceManagers::GetInstance()->GetSound("epic.mp3");
		m_ingame->PlaySoundFromStart2D(true);
		m_menu->PlaySoundFromStart2D(true);
		m_menu->Pause(true);
		m_ingame->Pause(true);
	};
	void PlayBGMIngame() {
		m_ingame->PlaySoundFromStart2D(true);
		m_ingame->Volumn(0.5);
		m_menu->Pause(true);
	}
	void PlayBGMMenu() {
		m_menu->PlaySoundFromStart2D(true);
		m_menu->Volumn(0.7);
		m_ingame->Pause(true);
	}
	void StopBGMIngame() {
		m_ingame->Pause(true);
	}
	void StopBGMMenu() {
		m_menu->Pause(true);
	}

	~BackgroundMusic(){};

private:
	std::shared_ptr<Sound> m_ingame;
	std::shared_ptr<Sound> m_menu;
};
