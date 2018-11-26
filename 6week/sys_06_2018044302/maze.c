#include<stdio.h>
#define    N   8

const int UNVISITIED_WAY = 0;
const int WALL = 1;
const int BLOCKED = 3;
const int POSSIBLE_WAY = 2;
int maze[N][N] = {
	{0, 0, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 0, 1, 1, 0, 1},
	{0, 0, 0, 1, 0, 0, 0, 1},
	{0, 1, 0, 0, 1, 1, 0, 0},
	{0, 1, 1, 1, 0, 0, 1, 1},
	{0, 1, 0, 0, 0, 1, 0, 1},
	{0, 0, 0, 1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0, 1, 0, 0}
}

int findPath(int x, int y) {
    if (x < 0 || y < 0 || x >= N || y >= N)
        return 0;
    else if (maze[x][y] != UNVISITIED_WAY)
        return 0;
    else if (x == N - 1 && y == N - 1) {
        maze[x][y] = POSSIBLE_WAY;
        return 1;
    }
    else {
        maze[x][y] = POSSIBLE_WAY;
        if (findPath(x - 1, y) || findPath(x, y + 1) || findPath(x + 1, y) || findPath(x, y - 1)) {
            return 1;
        }
        maze[x][y] = BLOCKED;
        return 0;
    }
}


int main(){
	int i, j;
	printf("Escape the maze from (0,0) to (%d,%d) : %d\n",N-1,N-1,findPath(0,0));
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d ",maze[i][j]);
		}
		printf("\n");
	}
	return 0;
}
