#include "GameWarning.h"
#include "GameClassPhase.h"
#include "SDL_image.h"


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern int warn;

extern bool timecontrol;
extern int t;

GameWarning* GameWarning::instance = 0; //const����� �ܺο��� 0���� �ѹ� �ʱ�ȭ�������.

GameWarning::GameWarning() {
	SDL_Surface*temp_surface = IMG_Load("../img/warning.png");

	//  Rect
	// �̹��� ��ȯ(�ִϸ��̼�)
	{
		static const int left_y[4] = { 0, 76, 152 ,309};
		static const int right_y[4] = { 76, 152, 228 };

		for (int i = 0; i<4; i++)
		{
			t_source_rect[i].x = 0;
			t_source_rect[i].y = left_y[i];

			t_source_rect[i].w = 189;
			t_source_rect[i].h = right_y[i] - left_y[i];
		}
	}

	t_destination_rect[warn].x = 600;
	t_destination_rect[warn].y = 135;
	t_destination_rect[warn].w = 100;
	t_destination_rect[warn].h = 54;

	jet_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

}

void GameWarning::Renewal() {
	
}

void GameWarning::Update() {
	
}

void GameWarning::Draw() {
	if (g_current_game_phase == PHASE_STAGE1)
	{ //���ȭ�鿡 �°� �Ÿ����� ����
		t_destination_rect[warn].x = 630;
		t_destination_rect[warn].y = 144;
		t_destination_rect[warn].w = 115;
		t_destination_rect[warn].h = 50;
		SDL_RenderCopy(g_renderer, jet_texture, &t_source_rect[warn], &t_destination_rect[warn]);//�� ĳ���� �׸���
	}
	else if (g_current_game_phase == PHASE_STAGE2)
	{//Ȯ��ȭ�鿡 �°� �Ÿ����� ����
		t_destination_rect[warn].x = 690;
		t_destination_rect[warn].y = 2;
		t_destination_rect[warn].w = 100;
		t_destination_rect[warn].h = 44;
		SDL_RenderCopy(g_renderer, jet_texture, &t_source_rect[warn], &t_destination_rect[warn]);//�� ĳ���� �׸���
	}

}