#pragma once

#include "MyCharacter.h"
#include "SDL_image.h"
#include "SDL.h"
//��ֹ������� �̹��� �ٸ��⶧���� Ŭ���������ϰ� �ξ����ϴ�! 
//���߿� �������� �̹�����, �浹�� �۵��ϴ� �Լ������� �ٸ��Ͱ��� �����Լ��� �����ϴ°��� �����Ͱ��ƿ�!

class Item {
public:
	int itemType;
	int x;
	int y_num;
	~Item();
	Item();
	bool block;

	Item(int a,int item_y);//������ ���� ���ε��ϰԲ�+y��ġ ����( ��ֹ��� ������ �ٸ��� )
	void Draw();
	void Move();//������ ��ĭ����.
	void Update();
	void crush();//�浹�� ���� �Ͼ�� ���.
	// void virtual crush(); ���� �߻�Ŭ���� �����Ϸ��ٰ� ���Լ� �ϳ��� �ٸ��Ŷ� ���� �׷����ϳ�?
	//�ϸ鼭 itemType��� ������ ���� �ΰ� �� �������°� �Լ��� �����ϴ°� �����غþ��!
	void Move_c();

	SDL_Rect item_source_rect;
	SDL_Rect item_destination_rect;
	SDL_Texture* item_texture;

private:

};
