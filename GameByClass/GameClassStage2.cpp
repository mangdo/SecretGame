#include"GameClassStage2.h"
#include "GameClassPhase.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_mixer.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;

extern bool g_flag_running;
extern int moving;
extern int warn;

extern bool shoes;

Mix_Chunk *wave;
Mix_Chunk *wave_2;

Stage2::Stage2() {
	//stage2�� ����̹��� �۾�
	SDL_Surface* temp_surface = IMG_Load("../img/space.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = 800;
	destination_rectangle_.h = 500;

	gtime = GameTime::GetSingleton();
	my = MyCharacter::GetSingleton();
	itemM = ItemManager::GetSingleton();
	gDis = GameDistance::GetSingleton();
	cha = Teacher::GetSingleton();
	gWarn = GameWarning::GetSingleton();

	moving = 0;

	shoes = false;
	collision = false;

	wave = Mix_LoadWAV("../Resources/shout.wav");
	if (wave == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	wave_2 = Mix_LoadWAV("../Resources/eating.wav");
	if (wave_2 == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}

}

Stage2::~Stage2() {
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(title_score_en);
	if (wave) Mix_FreeChunk(wave);
	if (wave_2) Mix_FreeChunk(wave_2);
}



void Stage2::Render() {

	SDL_SetRenderDrawColor(g_renderer, 0, 255, 255, 0);
	SDL_RenderClear(g_renderer); // ��������

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); //���ȭ�� �׸�.

	itemM->FullRender();//�����ۺ���
	my->Draw();//�� ĳ���� �׸�
	gtime->Draw();
	cha->Draw();//������
	gDis->Draw();
	gWarn->Draw();
	
	SDL_RenderPresent(g_renderer); // draw to the screen



}

void Stage2::Update() {
	my->Update();//��ĳ���� �������� ����
	itemM->Update();
	gtime->Update();
	cha->Update();
	gDis->Update();
	gWarn->Update();

	if (itemM->v.size() != 0) {//������ ũ�Ⱑ 0�� �ƴ϶��
		for (int n = 0; n < itemM->v.size(); n++) {
			if (itemM->v.at(n).y_num == my->y_num && (-25<445 - (itemM->v.at(n).x) && 445 - (itemM->v.at(n).x)<15)) {


				if (0 <= itemM->v.at(n).itemType && itemM->v.at(n).itemType < 4) {
					//��ֹ��̶� �΋H������ ��¿����.
					collision_last_time = SDL_GetTicks();
					collision = true;
					Mix_PlayChannel(-1, wave, 0);
				}

				if (itemM->v.at(n).itemType == 4) {//�ð�
					gtime->bonus_time += 10;
					Mix_PlayChannel(-1, wave_2, 0);
				}
				if (itemM->v.at(n).itemType == 5) {//�Ź�
					shoes = true;
					shoes_last_time = SDL_GetTicks();
					Mix_PlayChannel(-1, wave_2, 0);
				}
				if (itemM->v.at(n).itemType == 6) {//��Ʈ
					warn -= 1;
					if (warn < 1) {
						warn = 0;
						Mix_PlayChannel(-1, wave_2, 0);
					}
				}

				vector<Item>::iterator it = itemM->v.begin() + n;//�� ���� ��Ҵ� ���ֹ���
				itemM->v.erase(it);
			}
		}
	}

	if (collision) {//�浹�Ǿ��ִ� ���¶��, 2�ʵ����� �ƹ��͵� ���� ���ƾ��Ѵ�.
		Uint32 collision_cur_time = SDL_GetTicks();
		int col_time = collision_cur_time - collision_last_time;
		moving = 2;
		if (col_time > 3000) {//3�����Ŀ��� �浹���¸� Ǯ���ش�.
			collision = false;
			moving = 0;

		}
	}
	if (shoes) {
		Uint32 shoes_cur_time = SDL_GetTicks();
		int col_time = shoes_cur_time - shoes_last_time;
		if (col_time > 10000) {//10�����Ŀ��� �Ź� �ν��� ���¸� Ǯ���ش�.
			shoes = false;
		}
	}
	if (PHASE_ENDING <= g_current_game_phase&&g_current_game_phase <= PHASE_HIDDEN)
		Mix_FadeOutMusic(200);
}

void Stage2::HandleEvents() {

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;


		case SDL_KEYDOWN:
			// If the left arrow key is pressed. 
			if (event.key.keysym.sym == SDLK_UP)
			{

				if (!collision) {
					if (my->y_num != 0)//�������� ���ο� �ִ� ���̾ƴ϶��
						my->y_num--; //���� ��ĭ�̵�.
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				if (!collision) {
					if (my->y_num != 2)//���� �Ʒ��� ������ �ִ� ���� �ƴϸ�
						my->y_num++; // �Ʒ��� ��ĭ�̵�.
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)//�����ʹ�ư�� ������
			{
				if (!collision) {
					itemM->Move();//�����ۺ��͵� ��ĭ�� �̵��Ͽ� �ٰ���
					gDis->distance += 1;
					moving = 1;

					if (shoes) {
						itemM->Move_c();
					}
				}
			}
			if (event.key.keysym.sym == SDLK_RETURN) {//���ʹ�����
				g_current_game_phase = PHASE_STAGE1;//���ȭ��(stage1)���� �̵�
			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_RIGHT) {
				moving = 0;
			}

		default:
			break;
		}
	}
}