#pragma once
#include "SDL_ttf.h"

class GameWarning {
private:
	GameWarning();
	~GameWarning();
	static GameWarning* instance;

	TTF_Font *game_font1;

	SDL_Texture *text_time_; //���߿� �Ÿ��� ������ �����Ͱ��Ƽ� ���ܳ��þ��..
	SDL_Rect text_time_rect_;

	SDL_Rect t_source_rect[3];
	SDL_Rect t_destination_rect[3];
	SDL_Texture* jet_texture;



public:
	int distance;


	void Draw();

	void Renewal();
	static void CreateInstance() {
		if (instance != 0) return;
		instance = new GameWarning;

	}
	static GameWarning* GetSingleton() {
		return instance;
	}
	void Update();

};