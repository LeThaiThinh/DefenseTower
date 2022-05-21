#include "GSIntro.h"
#include "GameStateMachine.h"
#include <GameStates/Record.h>
#include "irrKlang.h"
#include "Upgrade/Upgrade.h"
#include "GSMenu.h"
GSIntro::GSIntro() : GameStateBase(StateType::STATE_INTRO), m_time(0.0f)
{
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{
	srand(time(0));
	Record::GetInstance()->ReadAll();
	if(GSMenu::sfx)
		ResourceManagers::GetInstance()->GetSound("intro.mp3")->PlaySoundFromStart2D(false);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UI/logo.tga");

	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_logo->SetISize(300, 225);

	ResourceManagers::GetInstance()->AddFont("Brightly Crush Shine.otf");
	ResourceManagers::GetInstance()->AddFont("arialbd.ttf");
	ResourceManagers::GetInstance()->AddShader("TextShader");
	ResourceManagers::GetInstance()->AddShader("AnimationShader");
	//UI
	ResourceManagers::GetInstance()->AddTexture("UI/bg_2.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/table.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_empty.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/btton_empty.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_close_2.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_settings.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_left.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_right.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_music.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_music_off.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_sound.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_sound_off.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/rope_big.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_0.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_1.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_2.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_3.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_4.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_5.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_6.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_7.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_8.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_9.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bar_1.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bar_2.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bar_3.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bar_4.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bar_bg.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bg_bar.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/header_levels.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/lock.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_shop.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/window_1.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/coin.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/tower_upgrade.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/health_icon.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/attack_damage_icon.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/attack_range_icon.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/attack_speed_icon.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bg_land.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_menu.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_restart.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/header_shop.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/header_settings.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_hard.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_easy.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_normal.tga");
	ResourceManagers::GetInstance()->AddTexture("MainCharacter/main_character_walk_right.tga");
	ResourceManagers::GetInstance()->AddTexture("MainCharacter/main_character_walk_left.tga");
	ResourceManagers::GetInstance()->AddTexture("MainCharacter/main_character_walk_attack_right.tga");
	ResourceManagers::GetInstance()->AddTexture("MainCharacter/main_character_walk_attack_left.tga");
	ResourceManagers::GetInstance()->AddTexture("MainCharacter/main_character_avatar.tga");
	ResourceManagers::GetInstance()->AddTexture("Tower/main_tower_1.tga");
	ResourceManagers::GetInstance()->AddTexture("Tower/upgrade_tower.tga");
	ResourceManagers::GetInstance()->AddTexture("Tower/spot_tower.tga");
	ResourceManagers::GetInstance()->AddTexture("Tower/upgrade_tower_one.tga");
	ResourceManagers::GetInstance()->AddTexture("Tower/upgrade_tower_two.tga");
	ResourceManagers::GetInstance()->AddTexture("Tower/obstacle_border.tga");
	ResourceManagers::GetInstance()->AddTexture("Tower/way_point.tga");
	ResourceManagers::GetInstance()->AddTexture("TowerOnelvl1.tga");
	ResourceManagers::GetInstance()->AddTexture("TowerOnelvl2.tga");
	ResourceManagers::GetInstance()->AddTexture("TowerOnelvl3.tga");
	ResourceManagers::GetInstance()->AddTexture("TowerTwolvl1.tga");
	ResourceManagers::GetInstance()->AddTexture("TowerTwolvl2.tga");
	ResourceManagers::GetInstance()->AddTexture("TowerTwolvl3.tga");
	ResourceManagers::GetInstance()->AddTexture("Tower/remove_tower.tga");
	ResourceManagers::GetInstance()->AddTexture("Tower/main_tower_1.tga");
	ResourceManagers::GetInstance()->AddTexture("Tower/main_tower_2.tga");
	ResourceManagers::GetInstance()->AddTexture("Tower/main_tower_3.tga");
	ResourceManagers::GetInstance()->AddTexture("Bullet/bullet_main_character.tga");
	ResourceManagers::GetInstance()->AddTexture("Bullet/enemy_two_bullet.tga");
	ResourceManagers::GetInstance()->AddTexture("Bullet/bullet_tower_one.tga");
	ResourceManagers::GetInstance()->AddTexture("ElectricBullet.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_one_attack_right.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_one_attack_left.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_one_walk_right.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_one_walk_left.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_one_avatar.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_two_attack_right.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_two_attack_left.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_two_walk_right.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_two_walk_left.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_two_avatar.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_three_attack_right.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_three_attack_left.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_three_walk_right.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_three_walk_left.tga");
	ResourceManagers::GetInstance()->AddTexture("Enemy/enemy_three_avatar.tga");


	//sound
	ResourceManagers::GetInstance()->AddSound("epic.mp3");
	ResourceManagers::GetInstance()->AddSound("maincharacter_attack.mp3");
}

void GSIntro::Exit()
{
}


void GSIntro::Pause()
{
}

void GSIntro::Resume()
{
}


void GSIntro::HandleEvents()
{
}

void GSIntro::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSIntro::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSIntro::HandleMouseMoveEvents(int x, int y)
{
}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 2.0f)
	{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		m_time = 0;
	}
}

void GSIntro::Draw()
{
	m_logo->Draw();
}
