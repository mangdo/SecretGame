#include "GameTime.h"
#include "GameClassPhase.h"
#include <string>

extern int ending_page;
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool timecontrol;
extern int t;

GameTime* GameTime::instance = 0; //const����� �ܺο��� 0���� �ѹ� �ʱ�ȭ�������.

GameTime::GameTime() {
	//��Ʈ load
	game_font1 = TTF_OpenFont("../Resources/moris.ttf", 40);
	time_ms = 0;
	bonus_time = 0;
	gDis= GameDistance::GetSingleton();
}

GameTime::~GameTime() {
}

void GameTime::Draw() {
	if (g_current_game_phase == PHASE_STAGE1)
	{ //���ȭ�鿡 �°� time���� ����
		SDL_Rect r;
		r.x = 330;
		r.y = 40;
		r.w = text_time_rect_.w;
		r.h = text_time_rect_.h;
		SDL_RenderCopy(g_renderer, text_time_, 0, &r);
	}
	else if (g_current_game_phase == PHASE_STAGE2)
	{//Ȯ��ȭ�鿡 �°� time���� ����
		SDL_Rect r;
		r.x = 140;
		r.y = 0;
		r.w = text_time_rect_.w;
		r.h = text_time_rect_.h;
		SDL_RenderCopy(g_renderer, text_time_, 0, &r);
	}
}



void GameTime::Update() {

	Uint32 cur_time = SDL_GetTicks();
	static Uint32 last_time = SDL_GetTicks();

	if (timecontrol == true) {//intro���� Ŭ�������� Ÿ�̸� ������� true�� �ѹ��Ǵµ�
		last_time = cur_time;//�̶� last_time�� ��������.
		timecontrol = false;
		bonus_time = 0;

		//MiniResize();
	}
	time_ms = cur_time - last_time;
	//int time_ms = cur_time - last_time;
	t = 60-(time_ms / 1000) + bonus_time; //������ 60��¥�� ����.


	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font1, std::to_string((long long)t).c_str(), white);

	text_time_rect_.x = 0;
	text_time_rect_.y = 0;
	text_time_rect_.w = tmp_surface->w;
	text_time_rect_.h = tmp_surface->h;

	text_time_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

	SDL_FreeSurface(tmp_surface);

	if (t <= 0)//������ 10�ʰ� ������ �ڵ������� ����ȭ������.
	{
		last_time = cur_time;
		g_current_game_phase = PHASE_ENDING2;

		if (gDis->distance == 0) {
			g_current_game_phase = PHASE_HIDDEN;
		}
	}

}