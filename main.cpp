
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

// Data structure to represent a move
struct Move {
    int spaces;
    string direction;
};

// Function to construct the graph from the maze
vector<vector<pair<int, string> > > constructGraph(const vector<vector<string> > & maze) {
    int rows = maze.size();
    int cols = maze[0].size();

    vector<vector<pair<int, string > > > graph(rows, vector<pair<int, string> >(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Extract spaces and direction from the maze cell
            int spaces;
            string direction;

            // Using stringstream for string parsing
            stringstream ss(maze[i][j]);
            ss >> spaces >> direction;

            // Add the edge to the graph
            graph[i][j] = make_pair(spaces, direction);
        }
    }

    return graph;
}

// Function to find the path using DFS
bool findPathDFS(
    const vector<vector<pair<int, string> > >& graph,
    int currentRow,
    int currentCol,
    int endRow,
    int endCol,
    set<pair<int, int> >& visited,
    vector<Move>& path
) {
    if (currentRow < 0 || currentRow >= graph.size() || currentCol < 0 || currentCol >= graph[0].size()) {
        return false;  // Out of bounds
    }

    if (currentRow == endRow && currentCol == endCol) {
        return true;  // Destination reached
    }

    if (visited.count({currentRow, currentCol}) > 0) {
        return false; // Already visited
    }

    visited.insert({currentRow, currentCol});

    int spaces = graph[currentRow][currentCol].first;
    string direction = graph[currentRow][currentCol].second;


    path.push_back({spaces, direction});

    // Try moving in the chosen direction
    if (direction == "R") {
        if (findPathDFS(graph, currentRow, currentCol + spaces, endRow, endCol, visited, path)) {
            return true;
        }
    } else if (direction == "B") {
        if (findPathDFS(graph, currentRow + spaces, currentCol, endRow, endCol, visited, path)) {
            return true;
        }
    } else if (direction == "NE") {
        if (findPathDFS(graph, currentRow + spaces, currentCol + spaces, endRow, endCol, visited, path)) {
            return true;
        }
    } else if (direction == "SE") {
        if (findPathDFS(graph, currentRow - spaces, currentCol + spaces, endRow, endCol, visited, path)) {
            return true;
        }
    } else if (direction == "SW") {
        if (findPathDFS(graph, currentRow - spaces, currentCol - spaces, endRow, endCol, visited, path)) {
            return true;
        }
    } else if (direction == "NW") {
        if (findPathDFS(graph, currentRow + spaces, currentCol - spaces, endRow, endCol, visited, path)) {
            return true;
        }
    }

    // If no path is found in the chosen direction, backtrack
    path.pop_back();
    visited.erase({currentRow, currentCol});

    return false;
}

vector<Move> findPathDFSWrapper(const vector<vector<pair<int, string> > >& graph) {
    int rows = graph.size();
    int cols = graph[0].size();

    set<pair<int, int> > visited;
    vector<Move> path;

    if (findPathDFS(graph, 0, 0, rows - 1, cols - 1, visited, path)) {
        // Reverse the path to get it in the correct order
        reverse(path.begin(), path.end());
        return path;
    } else {
        cerr << "No path found\n";
        return vector<Move>();  // Return an empty path to indicate failure
    }
}

int main() {
    ifstream inputFile("input.txt");
    int rows, cols;
    inputFile >> rows >> cols;

    vector<vector<string> > maze(rows, vector<string>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            inputFile >> maze[i][j];
        }
    }

    vector<vector<pair<int, string > > > graph = constructGraph(maze);
    vector<Move> path = findPathDFSWrapper(graph);

    if (path.empty()) {
        return 1;  // Return an error code to indicate failure
    }

    ofstream outputFile("output.txt");
    for (const auto& move : path) {
        outputFile << move.spaces << move.direction << " ";
    }

    return 0;
}
