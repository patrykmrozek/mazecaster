#include "map.h"

// map dimensions
const int MAP_WIDTH = 8;
const int MAP_HEIGHT = 8;
const int TILE_SIZE = 64;


// map is going to be stored as a matrix, 0s are empty spaces, 1s represent a wall
const int MAP[][8] =
{
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
};


int **generate_maze(int n) {
  //only going to visit all even cells, eg: (0, 2) or (4, 0) or (2, 6) etc..
  int size = 2*n+1; // as to avoid open spaces being generated
  bool *visited = calloc(n*n, sizeof(bool)); //keep track of visited nodes
  //Graph* graph = create_graph(size);

  //dynamically sized matrix
  int** maze = malloc(sizeof(int*)*size);
  for (int i = 0; i < size; i++) {
    maze[i] = malloc(sizeof(int)*size);
    for (int j = 0; j < size; j++) {
      maze[i][j] = 1; //initialize all cells to 1;
    }
  }
 
  //if you choose 1,1 as starting coords, due to the nature of the 2n+1 all, walls will surround the maze by defualt
  visited[1] = true;
  maze[1][1] = 0;
  _generate_maze(maze, visited, 1, 1, size, n);

  
  for (int i = 0; i < size; i ++) {
    for (int j = 0; j < size; j++) { 
      printf("%d ", maze[i][j]);
    }
    printf("\n");
  }


  return maze;
}

void _generate_maze(int** maze, bool* visited, int row, int col, int size, int n) {
  int directions[4][2] = {
    {-2, 0},//up
    {0, 2},//right
    {2, 0},//down
    {0, -2}//left
  };

  //need to shuffle the directions
  for (int i = 0; i < 3; i++) {
    int r = rand() & (i+1);
    int temp0 = directions[i][0];
    int temp1 = directions[i][1];
    directions[i][0] = directions[r][0];
    directions[i][1] = directions[r][1];
    directions[r][0] = temp0;
    directions[r][1] = temp1;
  }
  
  for (int d = 0; d < 4; d++) {
    int drow = directions[d][0];
    int dcol = directions[d][1];
    int nrow = drow + row;
    int ncol = dcol + col;

    if (nrow >= 0 && nrow < size && ncol >= 0 && ncol < size) {
      //need to translate from cell in maze -> index in visited
      int neighbour_index = ((nrow/2) * n) + (ncol/2);
      if (!visited[neighbour_index]) {
        visited[neighbour_index] = true;
        //since were jumping 2 cells at a time, if we find a valid unvisited cell
        //we need to clear the wall between the two cells
        int wall_row = (row + nrow)/2;
        int wall_col = (col + ncol)/2;
        maze[wall_row][wall_col] = 0; //clear wall between cells
        maze[nrow][ncol] = 0;//clear new found cell
        _generate_maze(maze, visited, nrow, ncol, size, n);
      } 
    }
  }

}




