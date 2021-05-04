#pragma once
#include "SDL.h"
#include "GameTime.h"

class Teacher {
private:
	//double attack_power;

	Teacher();
	~Teacher();
	//�� ĳ���� ��ü�� �ѹ��� �����ǰԲ� ������ֱ�����!
	static Teacher* instance;

	SDL_Rect t_source_rect[3];
	SDL_Rect t_destination_rect[3];

	SDL_Rect t_source_rect_face[3];
	SDL_Rect t_destination_rect_face;


public:
	void Draw();
	void Update();

	//������ �׸� �迭 �ε���
	//stage���� ����ϱ� ����.?
	int index;

	SDL_Texture* t_texture;
	SDL_Texture* t_texture_face;

	//void GetAttacked(double power);

	static void CreateInstance() {
		if (instance != 0) return;
		instance = new Teacher;

	}
	static Teacher* GetSingleton() {
		return instance;
	}
	int tcount;
	void renewal();
	GameTime *gtime;//�ð������� ��������

};