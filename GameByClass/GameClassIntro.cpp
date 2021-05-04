#include "GameClassIntro.h"
#include "GameClassPhase.h"
#include "SDL_image.h"
#include <iostream>


extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
bool timecontrol;//Ÿ�̸� �������ִ� ����
extern bool shoes;
extern int moving;
extern int lec;

extern int a;


Intro::Intro()
{
	// ������Ʈ��(gamestart)ȭ�� �̹��� �۾�

	SDL_Surface* temp_surface = IMG_Load("../img/start.jpg");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);

	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w = 800;
	destination_rectangle_.h = source_rectangle_.h = 500;

	timecontrol = false;

	cha = Teacher::GetSingleton();//������ �ʱ�ȭ ���ؼ�
	itemM = ItemManager::GetSingleton();//������ �ʱ�ȭ ���ؼ�
	gDis = GameDistance::GetSingleton();
	mycha = MyCharacter::GetSingleton();
	moving = 0;
}

Intro::~Intro()
{
	SDL_DestroyTexture(texture_);
}

void Intro::Update()
{
}


void Intro::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // ��������

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Intro::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT) //���콺 ����Ŭ���ϸ� ���ӽ���ȭ������
			{
				g_current_game_phase = PHASE_RULE;
				timecontrol = true; //�ð�������� true�� �ٲ���.
				itemM->renewal(); //������ �ʱ�ȭ
				cha->renewal(); //������ �ʱ�ȭ
				gDis->Renewal(); //�Ÿ� �ʱ�ȭ
				moving = 0; //�ִϸ��̼� �ʱ�ȭ
				shoes = false;
				lec = 0; //����ȭ�� ���� �ʱ�ȭ
				mycha->Renewal(); //ĳ���� ��ġ �ʱ�ȭ
				a = 0;
			}
			break;

		default:
			break;
		}
	}
}
