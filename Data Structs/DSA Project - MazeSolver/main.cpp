#include <iostream>
#include <stack>
#include <queue>
#include <set>
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

	//int* m_mazeSolve;

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
	bool shortestRouteFound;
	set<pair<int, int>> visited_neighbours;
	vector<pair<int, int>> fastest_route;

protected:
	// Called once at the start, so create things here
	virtual bool OnUserCreate()
	{
		//maze parameter
		m_nMazeWidth = 40;	//40
		m_nMazeHeight = 25;	//25
		//m_nMazeWidth = 10;
		//m_nMazeHeight = 10;

		m_maze = new int[m_nMazeWidth * m_nMazeHeight];
		memset(m_maze, 0x00, m_nMazeWidth * m_nMazeHeight * sizeof(int));
		m_nPathWidth = 3;


		//push the starting location of the maze generator 
		int x = rand() % m_nMazeWidth;
		int y = rand() % m_nMazeHeight;
		m_stack.push(make_pair(x, y));
		m_maze[y * m_nMazeWidth + x] = CELL_VISITED;
		m_nVisitedCells = 1;

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		// slow down the maze creation
		/*if (m_mazeCompleted) {
			this_thread::sleep_for(50ms);
		}*/
		//this_thread::sleep_for(100ms);

		auto offset = [&](int x, int y)
			{
				return (m_stack.top().second + y) * m_nMazeWidth + (m_stack.top().first + x);
			};


		if (!m_mazeCompleted)	// generate maze
		{
			if (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight) {
				if (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight)
				{
					vector<int> neighbours;

					// Search for neighbouring cells
					// North neighbour
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


					// If there are available neighbours
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
									Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, olc::WHITE);
								else
									Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, olc::BLUE);
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
							Draw(m_stack.top().first * (m_nPathWidth + 1) + px, m_stack.top().second * (m_nPathWidth + 1) + py, olc::BLACK);
				}

			}
			else	// maze creation is completed
			{
				m_solutionStack.push(make_pair(0, 0));	// start from top left corner, will change to random at some point
				visited_neighbours.insert(make_pair(0, 0));
				//cout << "Solution stack starts " << m_solutionStack.top().first << ", " << m_solutionStack.top().second << "\n";
				m_solutionSteps = 1;
				m_mazeCompleted = true;
			}
		}
		else if (!m_mazeSolved)		// maze solving algorithm
		{
			DrawCell(0, 0, olc::GREEN);
			DrawCell(m_nMazeWidth - 1, m_nMazeHeight - 1, olc::RED);
			SolveMaze();
		}
		else if (!shortestRouteFound){
			DrawShortestRoute();
		}

		return true;

	}

	void SolveMaze() {
		// Check if the maze solving is possible
		if (m_solutionStack.empty()) {
			//cout << "Stack is empty, maze cannot be solved!" << endl;
			return;
		}

		// Get the current cell
		int x = m_solutionStack.top().first;
		int y = m_solutionStack.top().second;

		//cout << "Current cell: (" << x << ", " << y << ")" << endl;

		auto neighbour = make_pair(x, y);
		visited_neighbours.insert(neighbour);

		//cout << "Visited cells: ";
		/*for (auto all : visited_neighbours) {
			cout << " (" << all.first << ", " << all.second << ") ";
		}*/

		// Check if the current cell is the end point
		if (x == m_nMazeWidth - 1 && y == m_nMazeHeight - 1) {
			//cout << "Maze solved!" << endl;
			//cout << "Solution stack size: " << m_solutionStack.size();
			m_mazeSolved = true;
			return;
		}

		// Store and explore neighbors
		vector<int> neighbours;

		//cout << "Steps taken: " << m_solutionSteps << endl;
		
		//cout << "Available directions:";
		//North neighbor
		if (y > 0 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_N)) {
			if (!ContainsPair(visited_neighbours, x, y - 1)) {
				//cout << " up ";
				neighbours.push_back(0);
			}
		}
		//East neighbor
		if (x < m_nMazeWidth - 1 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_E)) {
			if (!ContainsPair(visited_neighbours, x + 1, y)) {
				//cout << " right ";
				neighbours.push_back(1);
			}
		}
		//South neighbor
		if (y < m_nMazeHeight - 1 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_S)) {
			if (!ContainsPair(visited_neighbours, x, y + 1)) {
				//cout << " down ";
				neighbours.push_back(2);
			}
		}
		//West neighbor
		if (x > 0 && (m_maze[y * m_nMazeWidth + x] & CELL_PATH_W)) {
			if (!ContainsPair(visited_neighbours, x - 1, y)) {
				//cout << " left ";
				neighbours.push_back(3);
			}
		}

		// Check if any unvisited neighbour is available
		if (!neighbours.empty()) {
			// Choose a random direction
			int next_cell_dir = neighbours[rand() % neighbours.size()];
			//cout << "\nChosen direction:";
			// Move to the next cell based on the chosen direction
			switch (next_cell_dir) {
			case 0: // North
				m_solutionStack.push(make_pair(x, y - 1));
				//cout << "up" << endl;
				DrawVerticalCell(x, y, -1, olc::DARK_CYAN);
				break;
			case 1: // East
				m_solutionStack.push(make_pair(x + 1, y));
				//cout << "right" << endl;
				DrawHorizontalCell(x, y, 1, olc::DARK_CYAN);
				break;
			case 2: // South
				m_solutionStack.push(make_pair(x, y + 1));
				//cout << "down" << endl;
				DrawVerticalCell(x, y, 1, olc::DARK_CYAN);
				break;
			case 3: // West
				m_solutionStack.push(make_pair(x - 1, y));
				//cout << "left" << endl;
				DrawHorizontalCell(x, y, -1, olc::DARK_CYAN);
				break;
			}
			//cout << endl;
			auto neighbour = make_pair(x, y);
			m_solutionSteps++;
			visited_neighbours.insert(neighbour);
			fastest_route.push_back(neighbour);
		}
		else {
			// If no unvisited neighbour is available, backtrack
			if (ContainsPair(fastest_route, m_solutionStack.top().first, m_solutionStack.top().second)) {
				// if this != starting cell
				auto it = std::remove(fastest_route.begin(), fastest_route.end(), make_pair(m_solutionStack.top().first, m_solutionStack.top().second));

				// Erase the pair from the vector
				fastest_route.erase(it, fastest_route.end());
			}

			m_solutionStack.pop();
			//cout << "Backtracked" << endl;
		}

		// Drawing in all the visited cells
		for (auto v : visited_neighbours) {
			DrawCell(v.first, v.second, olc::DARK_CYAN);
		}

		// Drawing in the top of the stack for visibility 
		DrawCell(m_solutionStack.top().first, m_solutionStack.top().second, olc::GREEN);
		// Drawing the starting cell
		DrawCell(0, 0, olc::GREEN);
	}

	void DrawShortestRoute() {
		// 0, 0
		int counter = 0;
		auto prev = *fastest_route.begin();
		//cout << prev.first << " " << prev.second;

		//auto current = prev;
		for (auto current : fastest_route) {

			// 0, 0		1, 0	(moves to right)
			if (prev.first > current.first)
				DrawHorizontalCell(current.first, current.second, 1, olc::YELLOW);

			else if (prev.first < current.first)
				DrawHorizontalCell(current.first, current.second, -1, olc::YELLOW);

			// 0, 0		0, 1	(moves up)
			else if (prev.second > current.second)
				DrawVerticalCell(current.first, current.second, 1, olc::YELLOW);

			else if (prev.second < current.second)
				DrawVerticalCell(current.first, current.second, -1, olc::YELLOW);

			counter++;
			prev = current;
			//cout << endl << prev.first << ", " << prev.second;
		}
		cout << "Steps taken to find end: " << m_solutionSteps << endl;
		cout << "Shortest route: " << counter;
		shortestRouteFound = true;
	}


	void DrawHorizontalCell(int x, int y, int dir, olc::Pixel colour) {
		if (dir == -1) {	//left
			for (int py = 0; py < m_nPathWidth; py++)
			{
				for (int px = -1; px < m_nPathWidth; px++)
				{
					Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, colour); // Draw Cell
				}
			}
		}
		else if (dir == 1) {	//right
			for (int py = 0; py < m_nPathWidth; py++)
			{
				for (int px = 0; px < m_nPathWidth + 1; px++)
				{
					Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, colour); // Draw Cell
				}
			}
		}
	}

	void DrawVerticalCell(int x, int y, int dir, olc::Pixel colour) {
		if (dir == -1) {	//down
			for (int py = -1; py < m_nPathWidth; py++)
			{
				for (int px = 0; px < m_nPathWidth; px++)
				{
					Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, colour); // Draw Cell
				}
			}
		}
		else if (dir == 1) {	//up
			for (int py = 0; py < m_nPathWidth + 1; py++)
			{
				for (int px = 0; px < m_nPathWidth; px++)
				{
					Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, colour); // Draw Cell
				}
			}
		}
	}

	bool ContainsPair(set<pair<int, int>>& s, int x, int y) {
		return s.find(make_pair(x, y)) != s.end();
	}

	bool ContainsPair(stack<pair<int, int>>& s, int x, int y) {
		if (s.top().first == x && s.top().second == y) {
			return true;
		}
		return false;
	}

	bool ContainsPair(const vector<pair<int, int>>& v, int x, int y) {
		for (const auto& pair : v) {
			if (pair.first == x && pair.second == y) {
				return true;
			}
		}
		return false;
	}


	void DrawStartingPositionCell(int x, int y)
	{
		for (int py = 0; py < m_nPathWidth; py++)
		{
			for (int px = 0; px < m_nPathWidth; px++)
			{
				Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, olc::DARK_CYAN); // Draw Cell
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