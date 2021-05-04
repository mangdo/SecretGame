#pragma once
#include "SDL.h"
#include "SDL_mixer.h"

class MyCharacter {

private:
	MyCharacter();//�� ĳ���� ��ü�� �ѹ��� �����ǰԲ� ������ֱ�����!
	static MyCharacter* instance;

	SDL_Rect jet_source_rect[5];
	SDL_Rect jet_destination_rect;
	SDL_Texture* jet_texture;


	//TTF_Font *game_font1;

	//SDL_Texture *text_time_;
	//SDL_Rect text_time_rect_;

public:
	~MyCharacter();
	void Draw();
	void Update();
	void Renewal();

	int y_num; //��ǥ�� ����. y���� 1,2,3���ϳ�.

	static void CreateInstance() {
		if (instance != 0) return; 
		instance = new MyCharacter;
		
	}
	static MyCharacter* GetSingleton() {
		return instance;
	}
	int time_ms;
	int index;
	int moveControl;

};