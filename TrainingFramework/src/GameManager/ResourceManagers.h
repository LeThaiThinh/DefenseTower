#pragma once
#include <map>
#include "GameManager/Singleton.h"
#include "GameConfig.h"
#include "Base/Shader.h"
#include "Base/Texture.h"
#include "Base/Model.h"
#include "Base/Font.h"
#include "Base/Camera.h"
#include "Base/Sprite2D.h"
#include "Base/Sprite3D.h"
#include "Base/Text.h"
#include "Base/Sound.h"

class ResourceManagers : public CSingleton<ResourceManagers>
{
public:
	ResourceManagers();
	~ResourceManagers();

	void AddShader(const std::string& name);
	void AddModel(const std::string& name);
	void AddTexture(const std::string& name);
	void AddFont(const std::string& name);
	void AddSound(const std::string& name);

	void RemoveShader(const std::string& name);
	void RemoveModel(const std::string& name);
	void RemoveTexture(const std::string& name);
	void RemoveFont(const std::string& name);
	void RemoveSound(const std::string& name);

	std::shared_ptr<Shader> GetShader(const std::string& name);
	std::shared_ptr<Texture> GetTexture(const std::string& name);
	std::shared_ptr<Model> GetModel(const std::string& name);
	std::shared_ptr<Font> GetFont(const std::string& name);
	std::shared_ptr<Sound> GetSound(const std::string& name);

private:
	std::map<std::string, std::shared_ptr<Shader>> m_MapShader;
	std::map<std::string, std::shared_ptr<Texture>> m_MapTexture;
	std::map<std::string, std::shared_ptr<Model>> m_MapModels;
	std::map<std::string, std::shared_ptr<Font>> m_MapFont;
	std::map<std::string, std::shared_ptr<Sound>> m_MapSound;

	std::string m_ShaderPath;
	std::string m_TexturePath;
	std::string m_ModelsPath;
	std::string m_FontPath;
	std::string m_SoundPath;

};
