#include "GameDistance.h"
#include "GameClassPhase.h"
#include <string>


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;

GameDistance* GameDistance::instance = 0; //const����� �ܺο��� 0���� �ѹ� �ʱ�ȭ�������.

GameDistance::GameDistance(){
	game_font1 = TTF_OpenFont("../Resources/moris.ttf", 40);

	distance = 0;

}

void GameDistance::Renewal() {
	distance = 0;
}
void GameDistance::Update() {
	int d = 100-distance/2;//��ǥ�Ÿ� 100
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface *tmp_surface = TTF_RenderText_Blended(game_font1, std::to_string((long long)d).c_str(), white);

	text_time_rect_.x = 0;
	text_time_rect_.y = 0;
	text_time_rect_.w = tmp_surface->w;
	text_time_rect_.h = tmp_surface->h;

	text_time_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

	SDL_FreeSurface(tmp_surface);
	if (d <= 0)//������ 10�ʰ� ������ �ڵ������� ����ȭ������.
	{
		g_current_game_phase = PHASE_ENDING;
	}
}

void GameDistance::Draw() {
	if (g_current_game_phase == PHASE_STAGE1)
	{ //���ȭ�鿡 �°� �Ÿ����� ����
		SDL_Rect r;
		r.x = 630;
		r.y = 40;
		r.w = text_time_rect_.w;
		r.h = text_time_rect_.h;
		SDL_RenderCopy(g_renderer, text_time_, 0, &r);
	}
	else if (g_current_game_phase == PHASE_STAGE2)
	{//Ȯ��ȭ�鿡 �°� �Ÿ����� ����
		SDL_Rect r;
		r.x = 380;
		r.y = 0;
		r.w = text_time_rect_.w;
		r.h = text_time_rect_.h;
		SDL_RenderCopy(g_renderer, text_time_, 0, &r);
	}

}