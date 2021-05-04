#include "ItemManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

ItemManager* ItemManager::instance = 0; //const����� �ܺο��� 0���� �ѹ� �ʱ�ȭ�������.

ItemManager::ItemManager() {
	gDis = GameDistance::GetSingleton();
	distancecount = 0;
	itemCount = 20;//������ ó�������� ���
	srand((unsigned int)time(NULL));//���� ��

}

void ItemManager::Update() {


	if (v.size() != 0) {//������ ũ�Ⱑ 0�� �ƴ϶��
		for (int n = 0; n < v.size(); n++) {
			v.at(n).Update();//���� ��� �ϳ��ϳ��� �� ��ġ ����
			if (v.at(n).x <= 330) {//��ǻ�� ȭ���� ���� �����ϸ�
				vector<Item>::iterator it = v.begin() + n;//�� ���� ��Ҵ� ���ֹ���
				v.erase(it);
			}
		}
	}

	//��ֹ��̳� ������ ���� ���Ϳ� �ֱ�.
	if (distancecount <= gDis->distance) {//���� �Ÿ� ���������� �ٽ� ����
		lastBlock = gDis->distance;//��ֹ��� ���� ��ġ ����.

		int n = rand() % 4;//3~6ĭ����
		distancecount = gDis->distance + n + 3;//distancecount �ٽ�����
		int item_n = rand() % 4;//��ֹ��� ������ 4��(0,1,2,3) 

		int item_y = rand() % 3;//y��ǥ�� 0 1 2�� �ϳ� ����.
		Item tempitem(item_n, item_y);//�� ������0��ü����

		v.push_back(tempitem);//������ �ǵڿ� �־������

	}
	//�������� �������� �� �����. ������, ��ֹ��� �̹� ���� distancecount��� �Ѿ��.
	if (itemCount <= gDis->distance) {

		if (gDis->distance == lastBlock) {//��ֹ��� ������� ��ġ�� �����ϴٸ�
			itemCount = lastBlock + 2;//���� ���� ��ֹ� ������ 2ĭ ������

		}
		else {
			int n = rand() % 5;//20~25ĭ���� ������ ����.
			itemCount = gDis->distance + n + 20;//������
			int item_tmp_n = rand() % 10;
			int item_y = rand() % 3;//y��ǥ�� 0 1 2�� �ϳ� ����.
			int item_n;

			if (0 <= item_tmp_n&&item_tmp_n < 5) //Ȯ���� �����Բ�.
				item_n = 4;
			else if (5 <= item_tmp_n&&item_tmp_n < 9)
				item_n = 5;
			else if (item_tmp_n = 10)
				item_n = 6;
			Item tempitem(item_n, item_y);//�� ������0��ü����
			v.push_back(tempitem);//������ �ǵڿ� �־������
		}

	}
}

void ItemManager::MiniRender() {
	if (v.size() != 0) {
		for (int n = 0; n < v.size(); n++) {
			
			v.at(n).Draw();
			
		}

	}
}

void ItemManager::FullRender() {
	if (v.size() != 0) {
		for (int n = 0; n < v.size(); n++) {

			v.at(n).Draw();	
		}

	}
}

void ItemManager::Move() {
	if (v.size() != 0) {
		for (int n = 0; n < v.size(); n++) {
			v.at(n).Move();
		}

	}

}

void ItemManager::Move_c() {
	if (v.size() != 0) {
		for (int n = 0; n < v.size(); n++) {
			v.at(n).Move_c();
		}

	}

}


void ItemManager::renewal() {
	timecount = 0;
	distancecount = 0;
	lastBlock = 0;
	itemCount = 0;
	if(!v.empty())//���ִٸ�
		v.clear();//�� ���� �����.
}