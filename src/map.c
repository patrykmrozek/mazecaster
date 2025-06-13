#include "map.h"

/*
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

*/

map_t* generate_maze(int n) {
  //only going to visit all even cells, eg: (0, 2) or (4, 0) or (2, 6) etc..
  int size = 2*n+1; // as to avoid open spaces being generated
  bool *visited = calloc(n*n, sizeof(bool)); //keep track of visited nodes
  //graph_t* graph = create_graph(size);

  //dynamically sized matrix
  map_t* map = malloc(sizeof(map_t));
  map->width = size; //number of tiles
  map->height = size; //number of tiles
  map->tile_size = 64; //tile size in world units

  map->grid = malloc(sizeof(int*)*size);
  for (int i = 0; i < size; i++) {
    map->grid[i] = malloc(sizeof(int)*size);
    for (int j = 0; j < size; j++) {
      map->grid[i][j] = 1; //initialize all cells to 1;
    }
  }
 
  //if you choose 1,1 as starting coords, due to the nature of the 2n+1 alg, walls will surround the maze by defualt
  visited[1] = true;
  map->grid[1][1] = 0;
  _generate_maze(map, visited, 1, 1, size, n);
  graph_t* graph = create_graph(map->width * map->height);
  generate_maze_exit(map, graph);
  destroy_graph(graph); //can be immediately destroyed as we only need it for generating the exit

 /* 
  for (int i = 0; i < size; i ++) {
    for (int j = 0; j < size; j++) { 
      printf("%d ", map->grid[i][j]);
    }
    printf("\n");
  }
*/

  return map;
}

void _generate_maze(map_t* map, bool* visited, int row, int col, int size, int n) {
  //printf("SIZE: %d\n", map->width);
  int directions[4][2] = {
    {-2, 0},//up
    {0, 2},//right
    {2, 0},//down
    {0, -2}//left
  };

  //need to shuffle the directions
  for (int i = 0; i < 3; i++) {
    int r = i + rand() % (4-i);  
    int temp0 = directions[i][0]; 
    int temp1 = directions[i][1];
    directions[i][0] = directions[r][0];
    directions[i][1] = directions[r][1];
    directions[r][0] = temp0;
    directions[r][1] = temp1;
  }

  //for each direction
  for (int d = 0; d < 4; d++) {
    int drow = directions[d][0]; //direction row = the first value from each of the directions (only affect row value)
    int dcol = directions[d][1]; //direction col = the second value from each of the directions (only affect col values)
    int nrow = drow + row; //neighbour row = current row + the direction row
    int ncol = dcol + col; //nrighbour col = current col + the direction col
  
    //if nrow and ncol are still within the map
    if (nrow >= 0 && nrow < size && ncol >= 0 && ncol < size) {
      //need to translate from cell in maze -> index in visited
      int neighbour_index = ((nrow/2) * n) + (ncol/2);
      // if the cell nrow ncol has not yet been visited
      if (!visited[neighbour_index]) {
        visited[neighbour_index] = true; //set it to visited
        //since were jumping 2 cells at a time, if we find a valid unvisited cell
        //we need to clear the wall between the two cells
        int wall_row = (row + nrow)/2;
        int wall_col = (col + ncol)/2;
        map->grid[wall_row][wall_col] = 0; //clear wall between cells
        map->grid[nrow][ncol] = 0;//clear new found cell
        _generate_maze(map, visited, nrow, ncol, size, n);
      } 
    }
  }

}

graph_t* map_to_graph(map_t* map, graph_t* graph) {
  int w = map->width;
  int h = map->height;
  //for every cell in the map
  for (int i=0; i < h; i++) {
    for (int j=0; j < w; j++) {
      //if the current cell is not a wall
      if (map->grid[i][j]==0) {
        int curr = i * w + j; //each cell must have a unique vertex ID for add_edge to work
        //if the cell to the right is not a wall
        if ((j+1 < w) && (map->grid[i][j+1]==0)) {
          int next = i * w + (j+1); //next cell = cell to the right
          add_edge(graph, curr, next);
        }
        //if the cell below is not a wall
        if ((i+1 < h) && (map->grid[i+1][j]==0)) {
          int next = (i+1) * w + j; //next cell = cell above
          add_edge(graph, curr, next);
        }
      }
    }
  }

  return graph;
}

bool is_exit(map_t* map, int i, int j) {
  return false;
}

void generate_maze_exit(map_t* map, graph_t* graph) {
  //printf("GRAPH SIZE: %d\n", graph->num_vertices);
  graph_t* g = map_to_graph(map, graph);
  bool* marked = calloc(g->num_vertices, sizeof(bool)); //marked array initialized to 0
  int start_cell = map->width + 1; //starting vertex is the cell where the player spawns
  int final_cell = 0; //will hold the final cell that was updated in the dfs, candidate for maze exit (passed by pointer)
  //printf("START CELL: %d\n", start_cell);
  marked[start_cell] = 1; //mark the first cell as visited
  _dfs(g, marked, start_cell, &final_cell);
  //print_graph(g);
  /*
  for (int i = 0; i < graph->num_vertices; i++) {
    printf("%d - ", marked[i]);
  }
  */
  //printf("\n");
  //printf("FINAL CELL: %d\n", final_cell);
  int final_row = (int)(final_cell/map->width);
  int final_col = (int)(final_cell%map->height);
  
  //add final row and col to map struct under exit as a point_t type
  map->exit = (point_t){final_row, final_col};
  //printf("ROW: %d - COL: %d\n", map->exit.x, map->exit.y);
  map->grid[final_row][final_col] = 2;  
  free(marked);
}

void _dfs(graph_t* g, bool marked[], int v, int* final_cell) { //v = index of the vertex in the graph
  dll* adj = g->adj_lists[v]; //adj is the list of all edges adjacent to v
  //printf("%d\n", adj->head->next->data);
  Node* current = adj->head->next;
  //int current_data = current->data;
  //printf("CURR DATA: %d\n", current->data);

  for (int i=0; i<adj->size; i++) {
    //printf("CURRENT IN MARKED: %d\n", marked[current->data]);
    if (current && marked[current->data] == 0) { //if current exists and it is not marked yet
      marked[current->data] = 1; //mark current
      *final_cell = current->data; //updates value at pointer given by final_cell (allows for manipulation of data outside of the function parameters thrpugh passed by pointer)
      _dfs(g, marked, current->data, final_cell); //recurse on current
    }
    current=current->next; //update current to the next adjacent vertex to v
  }
}

SDL_Rect get_map_rect(map_t* map) { //returns the size of the rectangle in which the map will be fit into
  float map_aspect = (float)map->width/map->height;
  SDL_Rect map_rect;
  map_rect.w = WIDTH/2;
  map_rect.h = (int)(map_rect.w/map_aspect);
  map_rect.x = 0;
  map_rect.y = (HEIGHT - map_rect.h)/2;

  return map_rect;
}

void destroy_map(map_t* map) {
  //free map
  for (int i = 0; i < map->height; i++) {
    free(map->grid[i]);
  }
  free(map->grid);
  free(map);
}



