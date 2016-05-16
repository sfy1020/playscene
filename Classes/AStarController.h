#ifndef __ASTARCONTROLLER_H__
#define __ASTARCONTROLLER_H__
#include "AStar.h"
#include <iostream>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "constant.h"

class AstarController{
public:
	bool run(int board[BOARD_Y][BOARD_X], vector<pair<int, int>> &finalpath, int sx, int sy, int fx, int fy){

	TPathNode* path = nullptr;			// A*�� ���� ���
	int path_length;				// A*�� ��� Node ��
	CAStar star_search;				// A* object

	// Ž���� �迭 ����
	TTerrainNode terrain[BOARD_Y * BOARD_X];

	int t_cost[BOARD_Y * BOARD_X]= {0};

	for(int i=0; i<BOARD_Y; i++){
		for(int j=0; j<BOARD_X; j++){
			if(board[i][j]==EMPTY){
				t_cost[BOARD_X*i+j] = 0;
			}else{
				t_cost[BOARD_X*i+j] = -1;
			}
		}
	}

	// �迭 �ʱ�ȭ
	for (int i = 0; i < BOARD_Y * BOARD_X; i++)
		terrain[i].terrain_cost = t_cost[i];

	// cost �ʱ�ȭ
	star_search.Init(10);

	// A*�� �ִܰ�� ���ϱ�
	if (star_search.FindPath(terrain, BOARD_Y, BOARD_X, sy, sx,
		fy, fx, path, path_length) < 0) {
		star_search.Shutdown();
		return false;
	}else {
		for (int k = 0; k < path_length; k++){
			finalpath.push_back(std::pair<int, int>(path[k].col, path[k].row));
		}
		star_search.Shutdown();
		return true;
		}
	}
};
#endif

