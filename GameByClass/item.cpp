#include <iostream>
#include <vector>
#include "GameClassPhase.h"

#include "Item.h"
extern SDL_Renderer* g_renderer;



Item::Item(int a,int item_y) {

	y_num = item_y;
	x = 569;
	//��ֹ��� �̹����� �ٸ��� �׿ܿ� �� �����ϱ⿡ ���� Ŭ���� ���� ���߽��ϴ�!
	if (a == 0) {//0�� ��ֹ�
		SDL_Surface*temp_surface = IMG_Load("../img/0.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		itemType = 0;
	}
	else if (a == 1) {//1�� ��ֹ�
		SDL_Surface*temp_surface = IMG_Load("../img/1.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_SetTextureAlphaMod(item_texture, 20);
		SDL_FreeSurface(temp_surface);
		itemType = 1;

	}
	else if (a == 2) {//2�� ��ֹ�
		SDL_Surface*temp_surface = IMG_Load("../img/2.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		itemType = 2;

	}

	else if (a == 3) {//3�� ��ֹ�
		SDL_Surface*temp_surface = IMG_Load("../img/3.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		itemType = 3;

	}
	else if (a == 4) {//4��/ (���������δ� ù��°), �ð�
		SDL_Surface*temp_surface = IMG_Load("../img/4.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		itemType = 4;

	}
	else if (a == 5) {//�ι�° ������, �Ź�
		SDL_Surface*temp_surface = IMG_Load("../img/5.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		itemType = 5;

	}
	else if (a == 6) {//����° ������, ��Ʈ
		SDL_Surface*temp_surface = IMG_Load("../img/6.png");
		item_source_rect.x = 0;
		item_source_rect.y = 0;
		item_source_rect.w = 80;
		item_source_rect.h = 80;
		item_texture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		itemType = 6;

	}
}

Item::~Item() {
	//SDL_DestroyTexture(item_texture);
}

void Item::crush() {
	//�浹�� ���� �Ͼ�� ���.
	// void virtual crush(); ���� �߻�Ŭ���� �����Ϸ��ٰ� ���Լ� �ϳ��� �ٸ��Ŷ� ���� �׷����ϳ�?
	//�ϸ鼭 itemType��� ������ ���� �ΰ� �� �������°� �Լ��� �����ϴ°� �����غþ��!

	if (0 <= itemType&&itemType < 4) {
		//��ֹ��̶� �΋H������ ��¿����.
	}
	else if (itemType == 4) {//�ð�
	}
	else if (itemType == 5) {//�Ź�
	}
	else if (itemType == 6) {//��Ʈ
	}


}
void Item::Update() {
	if (g_current_game_phase == PHASE_STAGE1) {//���ȭ���̶��
		item_destination_rect.h = 20;
		item_destination_rect.w = 20;
		item_destination_rect.x = x;
		item_destination_rect.y = 340 + y_num * 30;
		SDL_SetTextureAlphaMod(item_texture, 40);     //���� �����ϱ� 
	}
	else {//Ȯ��ȭ���̶��
		item_destination_rect.h = 20 * (8.0 / 2.4);
		item_destination_rect.w = 20*(8.0 / 2.4);
		item_destination_rect.x = x* (8.0 / 2.4)-348* (8.0 / 2.4);
		item_destination_rect.y = 200 + y_num * 100;
		SDL_SetTextureAlphaMod(item_texture, 250);     //���� �����ϱ�
	}
}

void Item::Draw() {
	SDL_RenderCopy(g_renderer, item_texture, &item_source_rect, &item_destination_rect);//�� ĳ���� �׸���

}

void Item::Move() {
	x -= 20;
}

void Item::Move_c() {
	x -= 40;
}