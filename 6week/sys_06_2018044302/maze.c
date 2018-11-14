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
};

int findPath(int x, int y){
	if (x==7&&y==7){
		maze[x][y]=2;
		return 1;
	 }
	else{
		if ((maze[x-1][y]==0)&&(x>0)){
			maze[x][y] = 2;
        	findPath(x-1,y);
		}
		else if ((maze[x][y+1]==0)&&(y<7)){
			maze[x][y] = 2;
			findPath(x,y+1);
		}
		else if ((maze[x+1][y]==0)&&(x<7)){
			maze[x][y] = 2;
			findPath(x+1,y);
		}
		else if ((maze[x][y-1]==0)&&(y>0)){
			maze[x][y] = 2;
			findPath(x,y-1);
		}
		else if ((maze[x-1][y]==2)&&(x>0)){
			maze[x][y] = 3;
			findPath(x-1,y);
		}
		else if ((maze[x][y+1]==2)&&(y<7)){
			maze[x][y] = 3;
			findPath(x,y+1);
		}
		else if ((maze[x+1][y]==2)&&(x<7)){
			maze[x][y] = 3;
			findPath(x+1,y);
		}
		else if ((maze[x][y-1]==2)&&(y>0)){
			maze[x][y] = 3;
			findPath(x,y-1);
		}   
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
