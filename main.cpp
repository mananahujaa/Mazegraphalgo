#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

// Data structure to represent a move
struct Move
{
    int spaces;
    string direction;
};

// Function to construct the graph from the maze
vector<vector<pair<int, string>>> constructGraph(const vector<vector<string>> &maze)
{
    int rows = maze.size();
    int cols = maze[0].size();

    vector<vector<pair<int, string>>> graph(rows, vector<pair<int, string>>(cols));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // Extract spaces and direction from the maze cell
            int spaces = 0;
            string direction;

            // Iterate over characters in the maze cell
            for (char c : maze[i][j])
            {
                if (isdigit(c))
                {
                    spaces = spaces * 10 + (c - '0');
                }
                else
                {
                    direction.push_back(c);
                }
            }

            // Add the edge to the graph
            graph[i][j] = make_pair(spaces, direction);
        }
    }

    return graph;
}

// Function to find the path using BFS
vector<Move> findPathBFS(const vector<vector<pair<int, string>>> &graph) {
    int rows = graph.size();
    int cols = graph[0].size();

    set<pair<int, int>> visited;
    vector<Move> path;

    queue<pair<int, int>> q;
    q.push({0, 0});
    visited.insert({0, 0});

    bool foundPath = false;

    while (!q.empty()) {
        int currentRow = q.front().first;
        int currentCol = q.front().second;
        q.pop();

        int spaces = graph[currentRow][currentCol].first;
        string direction = graph[currentRow][currentCol].second;

        path.push_back({spaces, direction});

        cout << "Current Position: (" << currentRow << ", " << currentCol << "), Spaces: " << spaces << ", Direction: " << direction << endl;

        if (currentRow == rows - 1 && currentCol == cols - 1) {
            foundPath = true;
            break;
        }

        // Try moving in the chosen direction
        if (direction == "R" && currentCol + spaces < cols && visited.count({currentRow, currentCol + spaces}) == 0) {
            q.push({currentRow, currentCol + spaces});
            visited.insert({currentRow, currentCol + spaces});
        } else if (direction == "B" && currentRow + spaces < rows && visited.count({currentRow + spaces, currentCol}) == 0) {
            q.push({currentRow + spaces, currentCol});
            visited.insert({currentRow + spaces, currentCol});
        } else if (direction == "NE" && currentRow - spaces >= 0 && currentCol + spaces < cols && visited.count({currentRow - spaces, currentCol + spaces}) == 0) {
            q.push({currentRow - spaces, currentCol + spaces});
            visited.insert({currentRow - spaces, currentCol + spaces});
        } else if (direction == "SE" && currentRow + spaces < rows && currentCol + spaces < cols && visited.count({currentRow + spaces, currentCol + spaces}) == 0) {
            q.push({currentRow + spaces, currentCol + spaces});
            visited.insert({currentRow + spaces, currentCol + spaces});
        } else if (direction == "SW" && currentRow + spaces < rows && currentCol - spaces >= 0 && visited.count({currentRow + spaces, currentCol - spaces}) == 0) {
            q.push({currentRow + spaces, currentCol - spaces});
            visited.insert({currentRow + spaces, currentCol - spaces});
        } else if (direction == "NW" && currentRow - spaces >= 0 && currentCol - spaces >= 0 && visited.count({currentRow - spaces, currentCol - spaces}) == 0) {
            q.push({currentRow - spaces, currentCol - spaces});
            visited.insert({currentRow - spaces, currentCol - spaces});
        }
    }

    if (!foundPath) {
        cerr << "No path found\n";
        return vector<Move>();  // Return an empty path to indicate failure
    }

    return path;
}

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

    // Find path using BFS
    vector<Move> path = findPathBFS(graph);

    if (path.empty()) {
        return 1;  // Return error code for failure
    }

    return 0;
}


































// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <set>
// #include <algorithm>

// using namespace std;

// struct Move {
//     int spaces;
//     int direction;
// };

// class MazeSolver {
// public:
//     MazeSolver(const vector<vector<pair<int, string>>>& mazeGraph) : graph(mazeGraph) {}

//     vector<Move> solveMaze(const pair<int, int>& startNode, const pair<int, int>& targetNode) {
//         path.clear();
//         visited.clear();

//         if (dfs(startNode, true, targetNode)) {
//             reverse(path.begin(), path.end());  // Reverse the path to get the correct order
//             return path;
//         } else {
//             cerr << "No solution found\n";
//             return vector<Move>();
//         }
//     }

// private:
//     const vector<vector<pair<int, string>>>& graph;
//     vector<Move> path;
//     set<pair<int, int>> visited;

//     bool dfs(const pair<int, int>& currentNode, bool isRedArrow, const pair<int, int>& targetNode) {
//         if (currentNode == targetNode) {
//             return true;
//         }

//         if (visited.count(currentNode) > 0) {
//             return false;
//         }

//         visited.insert(currentNode);
//         vector<pair<int, int>> neighbors = getNeighbors(currentNode, isRedArrow);

//         for (const auto& neighbor : neighbors) {
//             if (dfs(neighbor, !isRedArrow, targetNode)) {
//                 Move moveInstance{neighbor.first, neighbor.second};


//                 path.push_back(moveInstance);               
//                 return true;
//             }
//         }

//         visited.erase(currentNode);
//         return false;
//     }

//     vector<pair<int, int>> getNeighbors(const pair<int, int>& currentNode, bool isRedArrow) {
//         // Implement your logic to get neighbors based on the mazeGraph
//         // You'll need to adapt this part based on your graph representation.
//         // For now, I'm assuming mazeGraph is a 2D vector of pairs.
//         int row = currentNode.first;
//         int col = currentNode.second;

//         vector<pair<int, int>> neighbors;
//         // Add logic here to find neighbors based on isRedArrow and mazeGraph structure
//         // For example, add neighbors from the graph[row][col] cell.

//         return neighbors;
//     }
// };

// int main() {
//     // Read maze from file
//     ifstream inputFile("tiny.txt");
//     int rows, cols;
//     inputFile >> rows >> cols;

//     // Create and fill maze vector
//     vector<vector<pair<int, string>>> mazeGraph(rows, vector<pair<int, string>>(cols));
//     for (int i = 0; i < rows; ++i) {
//         for (int j = 0; j < cols; ++j) {
//             inputFile >> mazeGraph[i][j].first >> mazeGraph[i][j].second;
//         }
//     }

//     // Print maze values
//     cout << "Maze Values:\n";
//     for (const auto& row : mazeGraph) {
//         for (const auto& cell : row) {
//             cout << "(" << cell.first << "," << cell.second << ") ";
//         }
//         cout << endl;
//     }

//     MazeSolver mazeSolver(mazeGraph);

//     // Specify start and target nodes
//     pair<int, int> startNode = make_pair(0, 0);
//     pair<int, int> targetNode = make_pair(rows - 1, cols - 1);

//     // Solve maze
//     vector<Move> path = mazeSolver.solveMaze(startNode, targetNode);

//     if (path.empty()) {
//         return 1;  // Return error code for failure
//     }

//     // Write path to output file
//     ofstream outputFile("output.txt");
//     for (const auto& move : path) {
//         outputFile << move.spaces << move.direction << " ";
//     }

//     return 0;
// }










