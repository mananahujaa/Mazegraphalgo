#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>
#include <sstream>
#include <algorithm>
#include <vector>
#include <memory>

using namespace std;

// Data structure to represent a move
struct Move {
    int spaces;
    string direction;
};





// Function to construct the graph from the maze
// Function to construct the graph from the maze
vector<vector<pair<int, string>> > constructGraph(const vector<vector<string> > &maze) {
    int rows = maze.size();
    int cols = maze[0].size();

    vector<vector<pair<int, string>> > graph(rows, vector<pair<int, string>> (cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Extract spaces and direction from the maze cell
            int spaces = 0;
            string direction;

            // Iterate over characters in the maze cell
            for (char c : maze[i][j]) {
                if (isdigit(c)) {
                    spaces = spaces * 10 + (c - '0');
                } else {
                    direction.push_back(c);
                }
            }

            // Add the edge to the graph
            graph[i][j] = make_pair(spaces, direction);
        }
    }

    // Print values for debugging
    cout << "Graph:\n";
    for (const auto &row : graph) {
        for (const auto &cell : row) {
            cout << "(" << cell.first << "," << cell.second << ") ";
        }
        cout << endl;
    }

    return graph;
}










bool findPathDFS(
    const vector<vector<pair<int, string>>>& graph,
    int currentRow,
    int currentCol,
    int endRow,
    int endCol,
    set<pair<int, int>>& visited,
    vector<Move>& path
) {
    if (currentRow < 0 || currentRow >= graph.size() || currentCol < 0 || currentCol >= graph[0].size()) {
        return false;  // Out of bounds
    }

    if (currentRow == endRow && currentCol == endCol) {
        return true;  // Destination reached
    }

    // Check if the current position has already been visited
    pair<int, int> currentPosition = {currentRow, currentCol};
    if (visited.count(currentPosition) > 0) {
        // Position has already been visited, but only mark it as visited if it was discovered during forward exploration
        if (path.size() == 0) {
            cerr << "Nowhere\n";
            return false;  // Nowhere to backtrack
        }

        // Position has already been visited during forward exploration, continue backtracking
    } else {
        visited.insert(currentPosition);  // Add the current position to visited
    }

    int spaces = graph[currentRow][currentCol].first;
    string direction = graph[currentRow][currentCol].second;

    path.push_back({spaces, direction});

    cout << "Current Position: (" << currentRow << ", " << currentCol << "), Spaces: " << spaces << ", Direction: " << direction << endl;

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

    return false;
}




vector<Move> findPathDFSWrapper(const vector<vector<pair<int, string>>>& graph) {
    int rows = graph.size();
    int cols = graph[0].size();

    set<pair<int, int>> visited;
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

class VectorGuard {
public:
    explicit VectorGuard(std::vector<int> &vector) : vector_(vector) {}
    ~VectorGuard() {}

    std::vector<int> &vector() { return vector_; }

private:
    std::vector<int> &vector_;
};

int main() {
    // Read maze from file
    ifstream inputFile("tiny.txt");
    int rows, cols;
    inputFile >> rows >> cols;

    // Create and fill maze vector
    vector<vector<string>> maze(rows, vector<string>(cols, ""));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            inputFile >> maze[i][j];
        }
    }

    // Print maze values
    cout << "Maze Values:\n";
    for (const auto& row : maze) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }

    // Construct graph from maze
    vector<vector<pair<int, string>>> graph = constructGraph(maze);

    // Print graph
    cout << "Graph:\n";
    for (const auto& row : graph) {
        for (const auto& cell : row) {
            cout << "(" << cell.first << "," << cell.second << ") ";
        }
        cout << endl;
    }

    // Mark the initial position as visited
    set<pair<int, int>> visited;
    visited.insert({0, 0});

    // Find path using DFS
    vector<Move> path = findPathDFSWrapper(graph);

    if (path.empty()) {
        return 1;  // Return error code for failure
    }

    // Write path to output file
    ofstream outputFile("output.txt");
    for (const auto& move : path) {
        outputFile << move.spaces << move.direction << " ";
    }

    return 0;
}






























// Function to find the path using DFS
// bool findPathDFS(
//     const vector<vector<pair<int, string> > > &graph,
//     int currentRow,
//     int currentCol,
//     int endRow,
//     int endCol,
//     set<pair<int, int> > &visited,
//     vector<Move> &path
// ) {
//     if (currentRow < 0 || currentRow >= graph.size() || currentCol < 0 || currentCol >= graph[0].size()) {
//         return false;  // Out of bounds
//     }

//     if (currentRow == endRow && currentCol == endCol) {
//         return true;  // Destination reached
//     }

//     if (visited.count({currentRow, currentCol}) > 0) {
//         return false; // Already visited
//     }

//     visited.insert({currentRow, currentCol});

//     int spaces = graph[currentRow][currentCol].first;
//     string direction = graph[currentRow][currentCol].second;


//     path.push_back({spaces, direction});

//     // Try moving in the chosen direction
//     if (direction == "R") {
//         if (findPathDFS(graph, currentRow, currentCol + spaces, endRow, endCol, visited, path)) {
//             return true;
//         }
//     } else if (direction == "B") {
//         if (findPathDFS(graph, currentRow + spaces, currentCol, endRow, endCol, visited, path)) {
//             return true;
//         }
//     } else if (direction == "NE") {
//         if (findPathDFS(graph, currentRow + spaces, currentCol + spaces, endRow, endCol, visited, path)) {
//             return true;
//         }
//     } else if (direction == "SE") {
//         if (findPathDFS(graph, currentRow - spaces, currentCol + spaces, endRow, endCol, visited, path)) {
//             return true;
//         }
//     } else if (direction == "SW") {
//         if (findPathDFS(graph, currentRow - spaces, currentCol - spaces, endRow, endCol, visited, path)) {
//             return true;
//         }
//     } else if (direction == "NW") {
//         if (findPathDFS(graph, currentRow + spaces, currentCol - spaces, endRow, endCol, visited, path)) {
//             return true;
//         }
//     }

//     // If no path is found in the chosen direction, backtrack
//     path.pop_back();
//     visited.erase({currentRow, currentCol});

//     return false;
// }
