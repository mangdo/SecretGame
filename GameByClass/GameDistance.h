#pragma once
#include "SDL_ttf.h"

class GameDistance {
private:
	GameDistance();
	~GameDistance();
	static GameDistance* instance;

	TTF_Font *game_font1;

	SDL_Texture *text_time_; //���߿� �Ÿ��� ������ �����Ͱ��Ƽ� ���ܳ��þ��..
	SDL_Rect text_time_rect_;


public:
	int distance;


	void Draw();

	void Renewal();
	static void CreateInstance() {
		if (instance != 0) return;
		instance = new GameDistance;

	}
	static GameDistance* GetSingleton() {
		return instance;
	}
	void Update();

};