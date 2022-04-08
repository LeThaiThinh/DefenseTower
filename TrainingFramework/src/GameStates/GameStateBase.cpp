#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSCredit.h"
#include "GSMenuAfterGame.h"
#include "GSMenuInGame.h"
#include "GSSelectStage.h"
#include "GSTutorial.h"
#include "GSSetting.h"

#include "GameStatebase.h"
#include <GameStates/GSLoadGame.h>
#include <GameStates/GSShop.h>

GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		break;
	case StateType::STATE_CREDIT:
		gs = std::make_shared<GSCredit>();
		break;
	case StateType::STATE_MENU_AFTER_GAME:
		gs = std::make_shared<GSMenuAfterGame>();
		break;
	case StateType::STATE_MENU_IN_GAME:
		gs = std::make_shared<GSMenuInGame>();
		break;
	case StateType::STATE_SELECT_STAGE:
		gs = std::make_shared<GSSelectStage>();
		break;
	case StateType::STATE_TUTORIAL:
		gs = std::make_shared<GSTutorial>();
		break;
	case StateType::STATE_SETTING:
		gs = std::make_shared<GSSetting>();
		break;
	case StateType::STATE_LOAD_GAME:
		gs = std::make_shared<GSLoadGame>();
		break;
	case StateType::STATE_SHOP:
		gs = std::make_shared<GSShop>();
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}