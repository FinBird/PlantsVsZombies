#include "GlobalVariable.h"

Global* Global::_instance = nullptr;

Global* Global::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new (std::nothrow)Global;
	}
	return _instance;
}

int Global::changeBgMusic(const std::string& _musicName,bool _loop)
{
	/* ��ͣ��ǰ�ı������� */
	for (auto sp : GlobalMusic.BackGroundMusic)
	{
		AudioEngine::stop(sp);
	}
	GlobalMusic.BackGroundMusic.clear();

	/* �����µı������� */
	int AudioID = AudioEngine::play2d(MusicsPath.find(_musicName)->second, _loop);
	AudioEngine::setVolume(AudioID, GlobalMusic.BackGroundMusicVolume);

	GlobalMusic.BackGroundMusic.push_back(AudioID);

	return AudioID;
}
