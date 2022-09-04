#include "Stack.cpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;
	
pair<int, int> directions[4] = {
	make_pair(1, 0),
	make_pair(0, 1),
	make_pair(-1, 0),
	make_pair(0, -1)
};

struct cell {
	int x, y;
	bool isVisited;
	char walls[4];
	bool canMove[4]; 

	cell(int x, int y): x(x), y(y), isVisited(false) { for(int i = 0; i < 4; i++) { walls[i] = '1';	canMove[i] = true; } };
};

void fillVec(vector<vector<cell>> & maze, const int & row, const int & col){
	for(int i = 0; i < row; i++){
		maze.push_back(vector<cell>());
		for(int j = 0; j < col; j++){
			cell k(j, row - i - 1);	maze[i].push_back(k);
		}
	}
}

bool checkBounds(const int & row, const int & col, const int & newRow, const int & newCol){
	return ( newRow < 0 || newRow >= row || newCol < 0 || newCol >= col ); 
}

void makeMove(cell* & currCell, cell* & toMove, const int & moveIndex){
	toMove->isVisited = true;

	if(moveIndex > 1){
		toMove->walls[moveIndex - 2] = '0';
	}

	else{
		toMove->walls[moveIndex + 2] = '0';
	}
	currCell->walls[moveIndex] = '0';
}

vector<vector<cell>> createAMaze(const int & row, const int & col){
	vector<vector<cell>> maze;
	fillVec(maze, row, col);

	Stack<cell*> currPath;	currPath.push(&maze[row - 1][0]);
	currPath.top()->isVisited = true;

	int wallsToBreak = row * col - 1, brokenWalls = 0, newRow, newCol;
	pair<int, int> currPos;

	while(brokenWalls < wallsToBreak){
		bool hasMove = false;

		cell* currCell = currPath.top();
		currPos = make_pair(row - currCell->y - 1, currCell->x);

		for(int i = 0; i < 4; i++){
			newRow = currPos.first + directions[i].first;
			newCol = currPos.second + directions[i].second;

			if( checkBounds(row, col, newRow, newCol) || maze[newRow][newCol].isVisited){
				currCell->canMove[i] = false;
			}

			else{
				hasMove = true;
			}
		}

		if(hasMove){
			int randMove = rand() % 4;
			while(!currCell->canMove[randMove]){
				randMove = rand() % 4;
			}

			newRow = currPos.first + directions[randMove].first;
			newCol = currPos.second + directions[randMove].second;

			cell* toMove = &maze[newRow][newCol];
			makeMove(currCell, toMove, randMove);

			currPath.push(toMove);
			brokenWalls++;
		}

		else{
			currPath.pop();
		}
	}	
	
	return maze;
}

void writeMazeFile(ofstream & file, const vector<vector<cell>> & maze, const int & row, const int & col){
	file << to_string(row) + " " + to_string(col) << endl;

	for(int i = row - 1; i >= 0; i--){
		for(int j = 0; j < col; j++){
			cell currCell = maze[i][j];
			file << 
			"x=" << currCell.x << " " <<
			"y=" << currCell.y << " " <<

			"l=" << currCell.walls[3] << " " <<
			"r=" << currCell.walls[1] << " " <<
			"u=" << currCell.walls[2] << " " <<
			"d=" << currCell.walls[0] << " " << endl;
		}
	}
}

void resetVisited(vector<vector<cell>> & maze, const int & row, const int & col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			maze[i][j].isVisited = false;
			std::fill( begin(maze[i][j].canMove), end(maze[i][j].canMove), true);
		}
	} 
}

int checkWalls(cell* & currCell, const int & moveIndex){
	return(currCell->walls[moveIndex] - '0');
}

pair<int, int> coordPos(const int & row, const int & currCol, const int & currRow){
	return make_pair( row - currRow - 1, currCol);
} 

void writePathFile(ofstream & file, Stack<cell*> & currPath){
	Stack<cell*> temp;
	while (currPath.isEmpty() == false)
    {
        temp.push(currPath.top());
        currPath.pop();
    }  
 
    while (temp.isEmpty() == false)
    {
        cell* t = temp.top();
		file << t->x << " " << t->y << endl;
        temp.pop();
    }
}

void pathFinder(const vector<vector<cell>>* mazes, const int & mazeNum,  const int & row, const int & col){
	cout << "Enter a maze ID between 1 " << " to " << mazeNum << " inclusive to find a path: ";	
	int choice;		cin >> choice;
	vector<vector<cell>> maze = mazes[choice - 1];

	resetVisited(maze, row, col);
	
	int iXCord, iYCord, oXCord, oYCord;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> iYCord >> iXCord;
	
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> oYCord >> oXCord;

	int newRow, newCol;
	pair<int, int> currPos = coordPos(row, iYCord, iXCord);

	Stack<cell*> currPath;
	currPath.push(&maze[currPos.first][currPos.second]);	currPath.top()->isVisited = true;

	bool found = false;
	while(!found){
		bool hasMove = false;

		cell* currCell = currPath.top();
		currPos = make_pair(row - currCell->y - 1, currCell->x);

		for(int i = 0; i < 4; i++){
			newRow = currPos.first + directions[i].first;
			newCol = currPos.second + directions[i].second;

			if( checkBounds(row, col, newRow, newCol) || maze[newRow][newCol].isVisited || checkWalls(currCell, i)){
				currCell->canMove[i] = false;
			}

			else{
				hasMove = true;
			}
		}

		if(hasMove){
			int randMove = rand() % 4;
			while(!currCell->canMove[randMove]){
				randMove = rand() % 4;
			}

			newRow = currPos.first + directions[randMove].first;
			newCol = currPos.second + directions[randMove].second;

			cell* toMove = &maze[newRow][newCol];

			currPath.push(toMove);
			toMove->isVisited = true;

			if(toMove->x == oYCord && toMove->y == oXCord){ found = true;}
		}

		else{
			currPath.pop();
		}
	}	

	string fName = "maze_" + to_string(choice) + "_path_" + to_string(iYCord) + "_" + to_string(iXCord) + "_" + to_string(oYCord) + "_" + to_string(oXCord) + ".txt";

	ofstream myFile(fName);
	writePathFile( myFile,  currPath);

	myFile.close();
}

int main(){
	int mazeNum, rowNum, colNum;
	string fName;

	cout << "Enter the number of mazes: ";	cin >> mazeNum;
	cout << "Enter the number of rows and columns (M and N): "; cin >> rowNum >> colNum;
	
	vector<vector<cell>> maze;
	vector<vector<cell>>* mazes = new vector<vector<cell>>[mazeNum];
	

	for(int i = 0; i < mazeNum; i++){
		maze = createAMaze(rowNum, colNum);
		mazes[i] = maze;

		fName = "maze_" + to_string((i + 1)) + ".txt";
		ofstream myFile(fName);

		writeMazeFile(myFile, maze, rowNum, colNum);

		myFile.close();
	}

	cout << "All mazes are generated." << endl;

	pathFinder(mazes, mazeNum, rowNum, colNum);

	return 0;
}