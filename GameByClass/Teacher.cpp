#include "Teacher.h"
#include "GameClassPhase.h"

#include "SDL_image.h"

#include <cstdlib>
#include <ctime>

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern int g_time_ms;
extern int t;
extern int lec;

extern int warn;

Teacher* Teacher::instance = 0; //const����� �ܺο��� 0���� �ѹ� �ʱ�ȭ�������.

Teacher::Teacher() {
	warn = 0;

	// �� ĳ���� �̹����۾�(������)
	SDL_Surface*temp_surface = IMG_Load("../img/teacher.png");
	t_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);

	//  Rect
	// �̹��� ��ȯ(�ִϸ��̼�)
	{
		static const int left_x[3] = { 0, 147, 290 };
		static const int right_x[3] = { 147, 290, 575 };

		for (int i = 0; i<3; i++)
		{
			t_source_rect[i].x = left_x[i];
			t_source_rect[i].y = 0;

			t_source_rect[i].w = right_x[i] - left_x[i];
			t_source_rect[i].h = 428;
		}
	}

	t_destination_rect[0].x = 22;
	t_destination_rect[0].y = 135;
	t_destination_rect[0].w = 150;
	t_destination_rect[0].h = 428;

	t_destination_rect[1].x = 27;
	t_destination_rect[1].y = 135;
	t_destination_rect[1].w = 150;
	t_destination_rect[1].h = 428;

	t_destination_rect[2].x = 20;
	t_destination_rect[2].y = 76;
	t_destination_rect[2].w = 275;
	t_destination_rect[2].h = 428;

	index = 0;
	SDL_FreeSurface(temp_surface);

	gtime = GameTime::GetSingleton();
	tcount = 4000;

	//���ȭ�鿡 �ִ� ������ ��
	{
		SDL_Surface*temp_surface = IMG_Load("../img/face.png");
		t_texture_face = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		{
			static const int left_x_face[3] = { 0, 50,100 };
			static const int right_x_face[3] = { 50, 100,150 };

			for (int i = 0; i<3; i++)
			{
				t_source_rect_face[i].x = left_x_face[i];
				t_source_rect_face[i].y = 0;

				t_source_rect_face[i].w = 50;
				t_source_rect_face[i].h = 50;
			}
		}

		t_destination_rect_face.x = 540;
		t_destination_rect_face.y = 2;
		t_destination_rect_face.w = 40;
		t_destination_rect_face.h = 40;

		SDL_FreeSurface(temp_surface);
	}
}

Teacher::~Teacher() {
	SDL_DestroyTexture(t_texture);

}

void Teacher::Update() {
	
	
	if (tcount <= gtime->time_ms) { //������ timecount (ms����)�ð��� �������� ���¸� �ٲ��ش�.

		if (index == 0) {
			index = 1;
			tcount = gtime->time_ms + 2000;//state2����(���) 2������

		}

		else if (index == 1) {		//����2(���) 2���̹� �����߰� ������·� ��ȭ�ұ�?

			if (lec == 0) {//����ȭ�� �ƴϿ��� -> ����3����
				index = 2;
				tcount = gtime->time_ms + 3000;//1����3(����) 2������
				warn += 1;							   //��� ���� �ѹ�����.
				if (warn == 3) {
					g_current_game_phase = PHASE_ENDING3;
				}
			}
			else {//����ȭ���̿��� -> �ٽ� ����1��
				index = 0;
				int n = rand() % 11;
				tcount = gtime->time_ms + n * 200 + 3000;//����1(�ʷ�)�����ð� ����.
			}

		}

		else if (index == 2) {//����3���� �ٽ� ����1�� ����������.
			index = 0;
			int n = rand() % 11;
			tcount = gtime->time_ms + n * 200 + 3000;//����1(�ʷ�)�����ð� ����.
		}
	}




}

void Teacher::Draw() {//������ĳ���� �׸���
	if (g_current_game_phase == PHASE_STAGE1) {
			SDL_RenderCopy(g_renderer, t_texture, &t_source_rect[index], &t_destination_rect[index]);

	}
	else if (g_current_game_phase == PHASE_STAGE2) {
		SDL_RenderCopy(g_renderer, t_texture_face, &t_source_rect_face[index], &t_destination_rect_face);

	}
}

void Teacher::renewal() {
	tcount = 4000;
	index = 0;
	warn = 0;

}