#include <iostream>
#include <stack>
using namespace std;

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
class Maze : public olc::PixelGameEngine
{
public:
	Maze()
	{
		// Name your application
		sAppName = "Maze";
		m_mazeCompleted = false;
		m_mazeSolved = false;
	}

private:
	int m_nMazeWidth;
	int m_nMazeHeight;
	int* m_maze;

	int m_nScreenWidth;
	int m_nScreenHeight;

	enum
	{
		CELL_PATH_N = 0x01,
		CELL_PATH_E = 0x02,
		CELL_PATH_S = 0x04,
		CELL_PATH_W = 0x08,
		CELL_VISITED = 0x10,
	};

	int m_nVisitedCells;
	int m_nPathWidth;

	stack<pair<int, int>> m_stack;

	// For completing the maze
	stack<pair<int, int>> m_solutionStack;
	int m_solutionSteps;
	bool m_mazeCompleted;
	bool m_mazeSolved;


protected:
	// Called once at the start, so create things here
	virtual bool OnUserCreate()
	{
		//maze parameter
		m_nMazeWidth = 10;	//40
		m_nMazeHeight = 5;	//25
		//m_nMazeWidth = 15;
		//m_nMazeHeight = 7;
		m_maze = new int[m_nMazeWidth * m_nMazeHeight];
		memset(m_maze, 0x00, m_nMazeWidth * m_nMazeHeight * sizeof(int));
		m_nPathWidth = 3;


		//push the starting location of the maze generator 
		//m_stack.push(make_pair(0, 0));
		int x = rand() % m_nMazeWidth;
		int y = rand() % m_nMazeHeight;
		m_stack.push(make_pair(x, y));
		m_maze[y * m_nMazeWidth + x] = CELL_VISITED;
		m_nVisitedCells = 1;


		//for solving the maze
		m_solutionStack.push(make_pair(0, 0));
		m_solutionSteps = 0;

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		// slow down the maze creation
		this_thread::sleep_for(10ms);

		//lambda function
		auto offset = [&](int x, int y)
		{
			return (m_stack.top().second + y) * m_nMazeWidth + (m_stack.top().first + x);
		};


		if (!m_mazeCompleted)	// generate maze
		{
			if (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight) {
				if (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight)
				{
					// Step 1: Create a set of the unvisited neighbours

					vector<int> neighbours;

					//// North neighbour
					if (m_stack.top().second > 0 && (m_maze[offset(0, -1)] & CELL_VISITED) == 0)	// if it isn't looking along the top row
						neighbours.push_back(0);

					// East neighbour
					if (m_stack.top().first < m_nMazeWidth - 1 && (m_maze[offset(1, 0)] & CELL_VISITED) == 0)	// if it isn't looking along the top row
						neighbours.push_back(1);

					// South neighbour
					if (m_stack.top().second < m_nMazeHeight - 1 && (m_maze[offset(0, 1)] & CELL_VISITED) == 0)	// if it isn't looking along the top row
						neighbours.push_back(2);

					// West neighbour
					if (m_stack.top().first > 0 && (m_maze[offset(-1, 0)] & CELL_VISITED) == 0)	// if it isn't looking along the top row
						neighbours.push_back(3);



					// Are neighbours available?
					if (!neighbours.empty())
					{
						int next_cell_dir = neighbours[rand() % neighbours.size()];		// choose random direction to go

						// Create path between neighbour and current cell
						switch (next_cell_dir)
						{
						case 0: // North
							m_maze[offset(0, -1)] |= CELL_VISITED | CELL_PATH_S;
							m_maze[offset(0, 0)] |= CELL_PATH_N;
							m_stack.push(make_pair((m_stack.top().first + 0), (m_stack.top().second - 1)));
							break;

						case 1: // East
							m_maze[offset(1, 0)] |= CELL_VISITED | CELL_PATH_W;
							m_maze[offset(0, 0)] |= CELL_PATH_E;
							m_stack.push(make_pair((m_stack.top().first + 1), (m_stack.top().second + 0)));
							break;

						case 2: // South
							m_maze[offset(0, 1)] |= CELL_VISITED | CELL_PATH_N;
							m_maze[offset(0, 0)] |= CELL_PATH_S;
							m_stack.push(make_pair((m_stack.top().first + 0), (m_stack.top().second + 1)));
							break;

						case 3: // West
							m_maze[offset(-1, 0)] |= CELL_VISITED | CELL_PATH_E;
							m_maze[offset(0, 0)] |= CELL_PATH_W;
							m_stack.push(make_pair((m_stack.top().first - 1), (m_stack.top().second + 0)));
							break;
						}

						//new cell
						m_maze[offset(0, 0)] |= CELL_VISITED;
						m_nVisitedCells++;

					}
					else {
						m_stack.pop();	// backtrack
					}
				}

				for (int x = 0; x < m_nMazeWidth; x++)
				{
					for (int y = 0; y < m_nMazeHeight; y++)
					{
						for (int py = 0; py < m_nPathWidth; py++)		//this draws in each cell to make the walls
							for (int px = 0; px < m_nPathWidth; px++)
							{
								if (m_maze[y * m_nMazeWidth + x] & CELL_VISITED) 
									Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, olc::WHITE); // Draw Cell
								else
									Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, olc::BLUE); // Draw Cell
							}

						// for drawing the path ways (through walls)
						for (int p = 0; p < m_nPathWidth; p++)
						{
							if (m_maze[y * m_nMazeWidth + x] & CELL_PATH_S)
								Draw(x * (m_nPathWidth + 1) + p, y * (m_nPathWidth + 1) + m_nPathWidth, olc::WHITE); // Draw South Passage
							if (m_maze[y * m_nMazeWidth + x] & CELL_PATH_E)
								Draw(x * (m_nPathWidth + 1) + m_nPathWidth, y * (m_nPathWidth + 1) + p, olc::WHITE); // Draw East Passage
						}

					}
				}

				// for colouring the cell at the top of the stack 
				if (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight) {
					for (int py = 0; py < m_nPathWidth; py++)
						for (int px = 0; px < m_nPathWidth; px++)
							Draw(m_stack.top().first * (m_nPathWidth + 1) + px, m_stack.top().second * (m_nPathWidth + 1) + py, olc::BLACK); // Draw Cell
				}

			}
			else	// maze is completed
			{
				cout << "maze compeleted 196" << endl;
				
				//start solving maze
				m_solutionStack.push(make_pair(0, 0));	// start from top left corner, will change to random at some point
				m_solutionSteps = 0;
				m_mazeCompleted = true;
			}
		}
		else if (!m_mazeSolved)		// maze solving algorithm
		{
			SolveMaze();
			//displayMaze();
		}

		return true;

	}

	void displayMaze() {
		for (int y = 0; y < m_nMazeHeight; y++) {
			for (int x = 0; x < m_nMazeWidth; x++) {
				cout << m_maze[y * m_nMazeWidth + x] << " ";
			}
			cout << endl;
		}
		cout << "done";
	}
	//void SolveMaze() {
	//	// Check if the maze solving is complete
	//	if (m_solutionStack.empty()) {
	//		cout << "Stack is empty, maze cannot be solved!" << endl;
	//		return;
	//	}

	//	// Get the current cell
	//	int x = m_solutionStack.top().first;
	//	int y = m_solutionStack.top().second;

	//	cout << "Current cell: (" << x << ", " << y << ")" << endl;

	//	// Mark the current cell as visited
	//	m_maze[y * m_nMazeWidth + x] |= CELL_VISITED;

	//	// Draw cell path
	//	DrawStartingPositionCell(x, y);
	//	DrawEndPositionCell(m_nMazeWidth - 1, m_nMazeHeight - 1);

	//	// Check if the current cell is the end point
	//	if (x == m_nMazeWidth - 1 && y == m_nMazeHeight - 1) {
	//		cout << "Maze solved!" << endl;
	//		m_mazeSolved = true;
	//		return;
	//	}

	//	// Explore neighbors
	//	vector<pair<int, int>> neighbours;

	//	// North neighbor
	//	if (y > 0 && (m_maze[(y - 1) * m_nMazeWidth + x] & CELL_VISITED) == 0 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_N)) {
	//		neighbours.push_back(make_pair(x, y - 1));
	//	}
	//	// East neighbor
	//	if (x < m_nMazeWidth - 1 && (m_maze[y * m_nMazeWidth + (x + 1)] & CELL_VISITED) == 0 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_E)) {
	//		neighbours.push_back(make_pair(x + 1, y));
	//	}
	//	// South neighbor
	//	if (y < m_nMazeHeight - 1 && (m_maze[(y + 1) * m_nMazeWidth + x] & CELL_VISITED) == 0 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_S)) {
	//		neighbours.push_back(make_pair(x, y + 1));
	//	}
	//	// West neighbor
	//	if (x > 0 && (m_maze[y * m_nMazeWidth + (x - 1)] & CELL_VISITED) == 0 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_W)) {
	//		neighbours.push_back(make_pair(x - 1, y));
	//	}

	//	// Check if any unvisited neighbor is available
	//	if (!neighbours.empty()) {
	//		// Choose a random neighbor to move to
	//		int next_neighbor_index = rand() % neighbours.size();
	//		pair<int, int> next_neighbor = neighbours[next_neighbor_index];

	//		// Move to the next cell
	//		m_solutionStack.push(next_neighbor);
	//		cout << "Moving to next cell: (" << next_neighbor.first << ", " << next_neighbor.second << ")" << endl;
	//	}
	//	else {
	//		// If no unvisited neighbor is available, backtrack
	//		m_solutionStack.pop();
	//		cout << "Backtracked" << endl;
	//	}
	//}


	void SolveMaze() {
		// Check if the maze solving is complete
		if (m_solutionStack.empty()) {
			cout << "Stack is empty, maze cannot be solved!" << endl;
			return;
		}

		// Get the current cell
		int x = m_solutionStack.top().first;
		int y = m_solutionStack.top().second;

		cout << "Current cell: (" << x << ", " << y << ")" << endl;
		// Draw cell path
		DrawCell(x, y, olc::GREEN);
		DrawCell(m_stack.top().first * (m_nPathWidth + 1), m_stack.top().second * (m_nPathWidth + 1), olc::BLACK);
		// Draw current moving cell
		//if (!m_mazeSolved) {
		//	for (int py = 0; py < m_nPathWidth; py++)
		//		for (int px = 0; px < m_nPathWidth; px++)
		//			Draw(m_stack.top().first * (m_nPathWidth + 1) + px, m_stack.top().second * (m_nPathWidth + 1) + py, olc::BLACK); // Draw Cell
		//}

		DrawCell(m_nMazeWidth - 1, m_nMazeHeight - 1, olc::RED);

		// Check if the current cell is the end point
		if (x == m_nMazeWidth - 1 && y == m_nMazeHeight - 1) {
			cout << "Maze solved!" << endl;
			m_mazeSolved = true;
			return;
		}

		// Explore neighbors
		vector<int> neighbours;

		// North neighbor
		/*if (y > 0 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_N)) {
			neighbours.push_back(0);
		}*/
		if (y > 0 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_N)) {
			neighbours.push_back(0);
		}
		// East neighbor
		if (x < m_nMazeWidth - 1 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_E)) {
			neighbours.push_back(1);
		}
		// South neighbor
		if (y < m_nMazeHeight - 1 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_S)) {
			neighbours.push_back(2);
		}
		// West neighbor
		if (x > 0 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_W)) {
			neighbours.push_back(3);
		}

		// Check if any unvisited neighbor is available
		if (!neighbours.empty()) {
			// Choose a random direction
			int next_cell_dir = neighbours[rand() % neighbours.size()];

			// Move to the next cell based on the chosen direction
			switch (next_cell_dir) {
			case 0: // North
				m_solutionStack.push(make_pair(x, y - 1));
				cout << "Moving north" << endl;
				break;
			case 1: // East
				m_solutionStack.push(make_pair(x + 1, y));
				cout << "Moving east" << endl;
				break;
			case 2: // South
				m_solutionStack.push(make_pair(x, y + 1));
				cout << "Moving south" << endl;
				break;
			case 3: // West
				m_solutionStack.push(make_pair(x - 1, y));
				cout << "Moving west" << endl;
				break;
			}
		}
		else {
			// If no unvisited neighbor is available, backtrack
			m_solutionStack.pop();
			cout << "Backtracked" << endl;
		}
	}

	void DrawStartingPositionCell(int x, int y)
	{
		for (int py = 0; py < m_nPathWidth; py++)
		{
			for (int px = 0; px < m_nPathWidth; px++)
			{
				Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, olc::GREEN); // Draw Cell
			}
		}
	}
	void DrawEndPositionCell(int x, int y)
	{
		for (int py = 0; py < m_nPathWidth; py++)
		{
			for (int px = 0; px < m_nPathWidth; px++)
			{
				Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, olc::RED); // Draw Cell
			}
		}
	}
	void DrawCell(int x, int y, olc::Pixel colour) {
		for (int py = 0; py < m_nPathWidth; py++)
		{
			for (int px = 0; px < m_nPathWidth; px++)
			{
				Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, colour); // Draw Cell
			}
		}
	}
};




int main()
{
	srand(time(nullptr));

	Maze maze;
	maze.Construct(160, 100, 8, 8);		//160x100 chars, 8x8 pixels
	maze.Start();

	return 0;
}
