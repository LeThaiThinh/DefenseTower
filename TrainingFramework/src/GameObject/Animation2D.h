#pragma once
#include "Sprite2D.h"
class Animation2D :
    public Sprite2D
{
protected:
    int m_numFrames;
    int m_numFramesInLine;
    int m_currentFrame;
    float m_frameTime;
    float m_currentFrameTime;
    int m_currentLine;
    int m_currentColumn;

public:
    Animation2D();
    Animation2D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, float frameTime, float x, float y);
    Animation2D(int numFrames, float frameTime, int numFramesInLine, float x, float y);
    ~Animation2D();
    void Init() override;
    void Draw() override;
    void Update(GLfloat deltatime) override;

};

