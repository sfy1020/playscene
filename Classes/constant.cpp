#include "constant.h"
float square(float x){
	return x*x;
}
float distance2D(float x, float y, float other_x, float other_y){
	return (x-other_x)*(x-other_x) + (y-other_y)*(y-other_y);
}

bool inRange(int x, int y, int other_x, int other_y, int range){		//float에 대한 수정이 필요함
	if((float)(range*range) >= distance2D((float)x,(float)y,(float)other_x,(float)other_y))return true;
	else return false;
}

DIRECTION getDirection(int sx, int sy, int fx, int fy){
	if(fx - sx < 0 && fy -sy == 0)  return	DIRECTION::LEFT;
	else if(fx - sx>0  && fy - sy==0)return DIRECTION::RIGHT;
	else if(fx - sx==0 && fy - sy<0)return	DIRECTION::UP;
	else if(fx - sx==0 && fy - sy>0)return	DIRECTION::DOWN;
	else {
		EXCEPTION("direction is not valid!")
			return DIRECTION::EMPTY;
	}
}
int P(int a, int b){
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 mt_rand(seed);
	mt_rand();
	return mt_rand() % (b - a + 1) + a;
}

void make_around_position(int &around_x, int &around_y, int target_x, int target_y, int board[BOARD_Y][BOARD_X]){
	std::queue<std::pair<int, int>> que;
	const int RANGE = 13;
	int i = 0, j = 0;
	int vi, vj;
	bool success = false;
	bool visited[RANGE][RANGE] = { 0 };
	que.push(std::pair<int, int>(target_y, target_x));
	while (!que.empty()){
		i = que.front().first;
		j = que.front().second;
		if (board[i][j] == EMPTY){
			success = true;
			around_x = j;
			around_y = i;
			break;
		}
		vi = i + RANGE / 2 - target_y;
		vj = j + RANGE / 2 - target_x;
		que.pop();
		if (board[i + 1][j] == EMPTY && 0 <= i + 1 && i + 1<BOARD_Y && 0 <= j&&j<BOARD_X && visited[vi + 1][vj] == false && 0 <= vi + 1 && vi + 1<RANGE && 0 <= vj&&vj<RANGE){
			que.push(std::pair<int, int>(i + 1, j));
			visited[vi + 1][vj] = true;
		}
		if (board[i - 1][j] == EMPTY && 0 <= i - 1 && i - 1<BOARD_Y && 0 <= j&&j<BOARD_X && visited[vi - 1][vj] == false && 0 <= vi - 1 && vi - 1<RANGE && 0 <= vj&&vj<RANGE){
			que.push(std::pair<int, int>(i - 1, j));
			visited[vi - 1][vj] = true;
		}
		if (board[i][j + 1] == EMPTY && 0 <= i&&i<BOARD_Y && 0 <= j + 1 && j + 1<BOARD_X && visited[vi][vj + 1] == false && 0 <= vi&&vi<RANGE && 0 <= vj + 1 && vj + 1<RANGE){
			que.push(std::pair<int, int>(i, j + 1));
			visited[vi][vj + 1] = true;
		}
		if (board[i][j - 1] == EMPTY && 0 <= i&&i<BOARD_Y && 0 <= j - 1 && j - 1<BOARD_X && visited[vi][vj - 1] == false && 0 <= vi&&vi<RANGE && 0 <= vj - 1 && vj - 1<RANGE){
			que.push(std::pair<int, int>(i, j - 1));
			visited[vi][vj - 1] = true;
		}
	}
	if (!success){
		EXCEPTION("no around position from target");
	}
}


void allPrint(cocos2d::Node * root){
	for (auto e : root->getChildren()){
		std::cout << std::left
			<< "tag : " << std::setw(8) << e->getTag() << std::setw(5)
			<< "name : " << std::setw(25) << e->getName() << std::setw(15)
			<< "childCnt : " << std::setw(5) << e->getChildrenCount()
			<< std::endl;
		allPrint(e);
	}
}