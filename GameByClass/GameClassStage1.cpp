#include "GameClassStage1.h"
#include "GameClassPhase.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include<vector>

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int lec;

extern int moving;
extern bool shoes;
extern int warn;

Mix_Chunk *wave1;
Mix_Chunk *wave2;

Stage1::Stage1()
{
		// ���ȭ��(stage1)�� ����̹��� �۾�
		SDL_Surface* temp_surface = IMG_Load("../img/main.jpg");
		texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);

		SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
		destination_rectangle_.x = source_rectangle_.x = 0;
		destination_rectangle_.y = source_rectangle_.y = 0;
		destination_rectangle_.w = source_rectangle_.w;
		destination_rectangle_.h = source_rectangle_.h;

		GameDistance::CreateInstance();//itemmanager(�����ۺ���)Ŭ�������� �ѹ��� �������.
		gDis = GameDistance::GetSingleton();

		GameTime::CreateInstance(); //MyCharacter�� Ŭ������ ��ü�� �ѹ��� ���� ����.
		gtime = GameTime::GetSingleton();

		MyCharacter::CreateInstance(); //MyCharacter�� Ŭ������ ��ü�� �ѹ��� ���� ����.
		my = MyCharacter::GetSingleton();
		//my->MiniResize();//��ĳ���� ������ ����
		
		Teacher::CreateInstance();//teacherŬ�������� �ѹ��� �������.
		cha = Teacher::GetSingleton();

		ItemManager::CreateInstance();//itemmanager(�����ۺ���)Ŭ�������� �ѹ��� �������.
		itemM = ItemManager::GetSingleton();

		GameWarning::CreateInstance();//itemmanager(�����ۺ���)Ŭ�������� �ѹ��� �������.
		gWarn = GameWarning::GetSingleton();


		//����ȭ��
		SDL_Surface* lec_surface = IMG_Load("../img/lecture.jpg");
		lec_texture = SDL_CreateTextureFromSurface(g_renderer, lec_surface);
		SDL_FreeSurface(lec_surface);

		SDL_QueryTexture(lec_texture, NULL, NULL, &lec_source.w, &lec_source.h);
		lec_source.x = 0;
		lec_source.y = 0;

		lec_destination.x = 349;
		lec_destination.y = 281;
		lec_destination.w = 240;
		lec_destination.h = 150;
		
		moving = 0;
		shoes = false;
		collision = false;

		Mix_VolumeMusic(128);

		wave1 = Mix_LoadWAV("../Resources/shout.wav");
		if (wave1 == NULL)
		{
			printf("Couldn't load the wav: %s\n", Mix_GetError());
		}
		wave2 = Mix_LoadWAV("../Resources/eating.wav");
		if (wave2 == NULL)
		{
			printf("Couldn't load the wav: %s\n", Mix_GetError());
		}
}

Stage1::~Stage1()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(lec_texture);
	SDL_DestroyTexture(title_score_en);
	if (wave1) Mix_FreeChunk(wave1);
	if (wave2) Mix_FreeChunk(wave2);
}


void Stage1::Update() {
	gtime->Update();

	my->Update();//�� ĳ���� �������� ����
	itemM->Update();
	cha->Update();
	gDis->Update();
	gWarn->Update();

	//������&��ֹ��� ���Ϳ� ĳ���Ͱ� �浹 �ߴ��� ���ߴ��� �˻�
	//ĳ������ x��ǥ�� �������ִ�.
	//�̴Ͽ����� ĳ���� x �߰� ��ġ
	//�̴� = > 445
	if (itemM->v.size() != 0) {//������ ũ�Ⱑ 0�� �ƴ϶��
		for (int n = 0; n < itemM->v.size(); n++) {
			if (itemM->v.at(n).y_num == my->y_num&&(-25<445-(itemM->v.at(n).x)&&445 - (itemM->v.at(n).x)<15)) {

				if (0 <= itemM->v.at(n).itemType && itemM->v.at(n).itemType < 4) {
					//��ֹ��̶� �΋H������ ��¿����.
					collision_last_time = SDL_GetTicks();
					collision = true;
					Mix_PlayChannel(-1, wave1, 0);
				}

				if (itemM->v.at(n).itemType == 4) {//�ð�
					gtime->bonus_time += 10;
					Mix_PlayChannel(-1, wave2, 0);
				}
				if (itemM->v.at(n).itemType == 5) {//�Ź�
					shoes = true;
					shoes_last_time= SDL_GetTicks();
					Mix_PlayChannel(-1, wave2, 0);
				}
				if (itemM->v.at(n).itemType == 6) {//��Ʈ
					warn -= 1;
					if (warn < 1) {
						warn = 0;
						Mix_PlayChannel(-1, wave2, 0);
					}
				}
				vector<Item>::iterator it = itemM->v.begin() + n;//�� ���� ��Ҵ� ���ֹ���
				itemM->v.erase(it);
			}
			
		}
	}
	if (collision) {//�浹�Ǿ��ִ� ���¶��, 2�ʵ����� �ƹ��͵� ���� ���ƾ��Ѵ�.
		Uint32 collision_cur_time = SDL_GetTicks();
		int col_time = collision_cur_time -collision_last_time;
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

void Stage1::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0,255,255,0);
	SDL_RenderClear(g_renderer); //���� ����

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_); //stage1���

	itemM->MiniRender();//�����ۺ���


	my->Draw();//��ĳ����
	cha->Draw();//������
	gtime->Draw();
	gDis->Draw();
	gWarn->Draw();


	if (lec == 1)//tab�� ������ ���¶�� ����ȭ���� �������� ���������.
	{
		SDL_RenderCopy(g_renderer, lec_texture, &lec_source, &lec_destination);

	}

	SDL_RenderPresent(g_renderer); // draw to the screen
}

void Stage1::HandleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_UP)
			{
				if(lec==0){
					if(!collision){
						if (my->y_num != 0)//�������� ���ο� �ִ� ���̾ƴ϶��
						my->y_num--; //�� ĳ���� ���� ��ĭ�̵�.
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				if(lec==0){
					if(!collision){
						if (my->y_num != 2)//���� �Ʒ��� ������ �ִ� ���� �ƴϸ�
						my->y_num++; // �� ĳ���;Ʒ��� ��ĭ�̵�.
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)//�����ʹ�ư�� ������
			{
				if (lec == 0) {
					if (!collision) {
						itemM->Move();//�����ۺ��͵� ��ĭ�� �̵��Ͽ� �ٰ���
						gDis->distance += 1;
						moving = 1;
						
						if (shoes)
						{
							itemM->Move_c();
						}
					}
				}

			}
			if (event.key.keysym.sym == SDLK_SPACE) // tabŰ�� ������, lec���¹ٲ���.
			{
				if (lec == 0)
				{
					lec = 1;
				}
				else if (lec == 1)
				{
					lec = 0;
				}

			}
			if (event.key.keysym.sym == SDLK_RETURN) { //���͸� ������
				if(lec==0)
					g_current_game_phase = PHASE_STAGE2; // Ȯ��ȭ��(stage2)�� �̵�
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
