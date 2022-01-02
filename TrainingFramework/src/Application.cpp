#include "Application.h"
#include "GameStates/GameStateMachine.h"
#include "GameStates/GameStatebase.h"
#include "GameStates/Record.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create a 2D camera
	m_camera = std::make_shared<Camera>(0, 0.f, (float)Globals::screenWidth, 0.f, (float)Globals::screenHeight, -1.0f, 1.0f, 300.0f,Vector3(0,0,0));

	GameStateMachine::GetInstance()->PushState(StateType::STATE_INTRO);
}

void Application::Update(GLfloat deltaTime)
{
	GameStateMachine::GetInstance()->PerformStateChange();

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->Update(deltaTime);
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->Draw();
}

void Application::HandleKeyEvent(unsigned char key, bool bIsPresseded)
{
	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleKeyEvents(key, bIsPresseded);

}

void Application::HandleTouchEvent(GLint x, GLint y, bool bIsPresseded)
{
	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleTouchEvents(x, y, bIsPresseded);
}

void Application::HandleMouseMoveEvent(GLint x, GLint y)
{
	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleMouseMoveEvents(x, y);
}

void Application::Exit()
{
	Record::GetInstance()->WriteAll();
	exit(0);
}
