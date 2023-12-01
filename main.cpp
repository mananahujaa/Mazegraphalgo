// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <set>
// #include <boost/graph/adjacency_list.hpp>
// using namespace std;
// using namespace boost;

// // Define the graph type
// typedef adjacency_list<vecS, vecS, directedS> Graph;
// typedef graph_traits<Graph>::vertex_descriptor Vertex;

// // A utility function to add an edge in the graph
// void add_edge_if_valid(Graph& g, int from, int to, int rows, int cols) {
//     // Add your logic here to add an edge if it's valid within the maze
// }

// // DFS function with backtracking
// bool dfs(Graph& g, Vertex v, Vertex target, set<Vertex>& visited, vector<Vertex>& path) {
//     if (v == target) {
//         path.push_back(v);
//         return true;
//     }
//     if (visited.find(v) != visited.end()) {
//         return false;
//     }
    
//     visited.insert(v);
//     graph_traits<Graph>::adjacency_iterator ai, ai_end;
//     for (tie(ai, ai_end) = adjacent_vertices(v, g); ai != ai_end; ++ai) {
//         if (dfs(g, *ai, target, visited, path)) {
//             path.push_back(v);
//             return true;
//         }
//     }
//     visited.erase(v);
//     return false;
// }


// int main() {
//     ifstream infile("input.txt");
//     if (!infile) {
//         cerr << "Error opening input file" << endl;
//         return 1;
//     }

//     int rows, cols;
//     infile >> rows >> cols;

//     // Create the graph
//     Graph g(rows * cols);

//     // Read the maze and construct the graph
//     for (int i = 0; i < rows; ++i) {
//         for (int j = 0; j < cols; ++j) {
//             // Read and process each cell to create edges
//             // Use add_edge_if_valid to add edges to the graph
//         }
//     }

//     // Define the start and target vertices
//     Vertex start = 0; // Assuming top-left corner is the start
//     Vertex target = rows * cols - 1; // Assuming bottom-right corner is the target

//     set<Vertex> visited;
//     vector<Vertex> path;
//     if (dfs(g, start, target, visited, path)) {
//         reverse(path.begin(), path.end());
//         // Output the path
//         ofstream outfile("output.txt");
//         for (Vertex v : path) {
//             outfile << /* format the output according to the problem's requirements */;
//         }
//     } else {
//         cout << "No solution found" << endl;
//     }

//     return 0;
//}







#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Define Move structure
struct Move {
    int row;
    int col;

    Move(int r, int c) : row(r), col(c) {}
};

enum Direction {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

string getDirectionString(int direction) {
    switch (direction) {
        case UP: return "S";
        case DOWN: return "N";
        case LEFT: return "W";
        case RIGHT: return "E";
        default: return "";
    }
}

// Define MazeSolver class
class MazeSolver {
public:
    MazeSolver(const vector<vector<string>>& mazeGraph) : graph(mazeGraph) {}

    vector<Move> solveMaze(const pair<int, int>& startNode, const pair<int, int>& targetNode) {
        path.clear();
        visited.clear();

        if (dfs(startNode, true, targetNode)) {
            reverse(path.begin(), path.end());
            return path;
        } else {
            cerr << "No solution found\n";
            return vector<Move>();
        }
    }

private:
    const vector<vector<string>>& graph;
    vector<Move> path;
    set<pair<int, int>> visited;

    bool dfs(const pair<int, int>& currentNode, bool isRedArrow, const pair<int, int>& targetNode) {
        if (currentNode == targetNode) {
            return true;
        }

        if (visited.count(currentNode) > 0) {
            return false;
        }

        visited.insert(currentNode);
        vector<pair<int, int>> neighbors = getNeighbors(currentNode);

        for (const auto& neighbor : neighbors) {
            if (dfs(neighbor, !isRedArrow, targetNode)) {
                Move moveInstance{neighbor.first, neighbor.second};
                path.push_back(moveInstance);
                return true;
            }
        }

        visited.erase(currentNode);
        return false;
    }

    vector<pair<int, int>> getNeighbors(const pair<int, int>& currentNode) {
        int row = currentNode.first;
        int col = currentNode.second;

        vector<pair<int, int>> neighbors;

        // Move up
        if (row > 0) {
            neighbors.push_back({row - 1, col});
        }

        // Move down
        if (row < graph.size() - 1) {
            neighbors.push_back({row + 1, col});
        }

        // Move left
        if (col > 0) {
            neighbors.push_back({row, col - 1});
        }

        // Move right
        if (col < graph[0].size() - 1) {
            neighbors.push_back({row, col + 1});
        }

        return neighbors;
    }
};

int main() {
    // Example maze graph
    vector<vector<string>> mazeGraph = {
        {"R-S", "R-S", "R-SE"},
        {"B-NE", "B-NW", "R-S"},
        {"B-NE", "B-E", "O"}
    };

    // Create MazeSolver instance
    MazeSolver mazeSolver(mazeGraph);

    // Set start and target nodes
    pair<int, int> startNode = {0, 0};
    pair<int, int> targetNode = {2, 2};

    // Solve the maze
    vector<Move> path = mazeSolver.solveMaze(startNode, targetNode);

    // Display the result
    for (size_t i = 0; i < path.size(); ++i) {
        string direction = getDirectionString(i % 4);
        int steps = (i / 4) + 1;
        cout << steps << direction << " ";
    }
    cout << endl;

    return 0;
}
























































































































































// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <queue>
// #include <set>
// #include <algorithm>
// #include <string>

// using namespace std;

// // Data structure to represent a move
// struct Move
// {
//     int spaces;
//     string direction;
// };

// // Function to construct the graph from the maze
// vector<vector<pair<int, string>>> constructGraph(const vector<vector<string>> &maze)
// {
//     int rows = maze.size();
//     int cols = maze[0].size();

//     vector<vector<pair<int, string>>> graph(rows, vector<pair<int, string>>(cols));
//     for (int i = 0; i < rows; ++i)
//     {
//         for (int j = 0; j < cols; ++j)
//         {
//             // Extract spaces and direction from the maze cell
//             int spaces = 0;
//             string direction;

//             // Iterate over characters in the maze cell
//             for (char c : maze[i][j])
//             {
//                 if (isdigit(c))
//                 {
//                     spaces = spaces * 10 + (c - '0');
//                 }
//                 else
//                 {
//                     direction.push_back(c);
//                 }
//             }

//             // Add the edge to the graph
//             graph[i][j] = make_pair(spaces, direction);
//         }
//     }

//     return graph;
// }

// // Function to find the path using BFS
// vector<Move> findPathBFS(const vector<vector<pair<int, string>>> &graph) {
//     int rows = graph.size();
//     int cols = graph[0].size();

//     set<pair<int, int>> visited;
//     vector<Move> path;

//     queue<pair<int, int>> q;
//     q.push({0, 0});
//     visited.insert({0, 0});

//     bool foundPath = false;

//     while (!q.empty()) {
//         int currentRow = q.front().first;
//         int currentCol = q.front().second;
//         q.pop();

//         int spaces = graph[currentRow][currentCol].first;
//         string direction = graph[currentRow][currentCol].second;

//         path.push_back({spaces, direction});

//         cout << "Current Position: (" << currentRow << ", " << currentCol << "), Spaces: " << spaces << ", Direction: " << direction << endl;

//         if (currentRow == rows - 1 && currentCol == cols - 1) {
//             foundPath = true;
//             break;
//         }

//         // Try moving in the chosen direction
//         if (direction == "R" && currentCol + spaces < cols && visited.count({currentRow, currentCol + spaces}) == 0) {
//             q.push({currentRow, currentCol + spaces});
//             visited.insert({currentRow, currentCol + spaces});
//         } else if (direction == "B" && currentRow + spaces < rows && visited.count({currentRow + spaces, currentCol}) == 0) {
//             q.push({currentRow + spaces, currentCol});
//             visited.insert({currentRow + spaces, currentCol});
//         } else if (direction == "NE" && currentRow - spaces >= 0 && currentCol + spaces < cols && visited.count({currentRow - spaces, currentCol + spaces}) == 0) {
//             q.push({currentRow - spaces, currentCol + spaces});
//             visited.insert({currentRow - spaces, currentCol + spaces});
//         } else if (direction == "SE" && currentRow + spaces < rows && currentCol + spaces < cols && visited.count({currentRow + spaces, currentCol + spaces}) == 0) {
//             q.push({currentRow + spaces, currentCol + spaces});
//             visited.insert({currentRow + spaces, currentCol + spaces});
//         } else if (direction == "SW" && currentRow + spaces < rows && currentCol - spaces >= 0 && visited.count({currentRow + spaces, currentCol - spaces}) == 0) {
//             q.push({currentRow + spaces, currentCol - spaces});
//             visited.insert({currentRow + spaces, currentCol - spaces});
//         } else if (direction == "NW" && currentRow - spaces >= 0 && currentCol - spaces >= 0 && visited.count({currentRow - spaces, currentCol - spaces}) == 0) {
//             q.push({currentRow - spaces, currentCol - spaces});
//             visited.insert({currentRow - spaces, currentCol - spaces});
//         }
//     }

//     if (!foundPath) {
//         cerr << "No path found\n";
//         return vector<Move>();  // Return an empty path to indicate failure
//     }

//     return path;
// }

// int main() {
//     // Read maze from file
//     ifstream inputFile("tiny.txt");
//     int rows, cols;
//     inputFile >> rows >> cols;

//     // Create and fill maze vector
//     vector<vector<string>> maze(rows, vector<string>(cols, ""));
//     for (int i = 0; i < rows; ++i) {
//         for (int j = 0; j < cols; ++j) {
//             inputFile >> maze[i][j];
//         }
//     }

//     // Print maze values
//     cout << "Maze Values:\n";
//     for (const auto& row : maze) {
//         for (const auto& cell : row) {
//             cout << cell << " ";
//         }
//         cout << endl;
//     }

//     // Construct graph from maze
//     vector<vector<pair<int, string>>> graph = constructGraph(maze);

//     // Print graph
//     cout << "Graph:\n";
//     for (const auto& row : graph) {
//         for (const auto& cell : row) {
//             cout << "(" << cell.first << "," << cell.second << ") ";
//         }
//         cout << endl;
//     }

//     // Find path using BFS
//     vector<Move> path = findPathBFS(graph);

//     if (path.empty()) {
//         return 1;  // Return error code for failure
//     }

//     return 0;
// }









































// #include <iostream>
// #include <vector>
// #include <set>
// #include <algorithm>

// using namespace std;

// // Define Move structure
// struct Move {
//     int row;
//     int col;

//     Move(int r, int c) : row(r), col(c) {}
// };

// // Define MazeSolver class
// class MazeSolver {
// public:
//     MazeSolver(const vector<vector<int>>& mazeGraph) : graph(mazeGraph) {}

//     vector<Move> solveMaze(const pair<int, int>& startNode, const pair<int, int>& targetNode) {
//         path.clear();
//         visited.clear();

//         if (dfs(startNode, targetNode)) {
//             // Print the path before reversing
//             cout << "Path before reversing: ";
//             for (const auto& move : path) {
//                 cout << "(" << move.row << "," << move.col << ") ";
//             }
//             cout << endl;

//             reverse(path.begin(), path.end());  // Reverse the path to get the correct order
//             return path;
//         } else {
//             cerr << "No solution found\n";
//             return vector<Move>();
//         }
//     }

// private:
//     const vector<vector<int>>& graph;
//     vector<Move> path;
//     set<pair<int, int>> visited;

//     bool dfs(const pair<int, int>& currentNode, const pair<int, int>& targetNode) {
//         if (currentNode == targetNode) {
//             return true;
//         }

//         if (visited.count(currentNode) > 0) {
//             return false;
//         }

//         visited.insert(currentNode);
//         vector<pair<int, int>> neighbors = getNeighbors(currentNode);

//         for (const auto& neighbor : neighbors) {
//             if (dfs(neighbor, targetNode)) {
//                 Move moveInstance{neighbor.first, neighbor.second};
//                 path.push_back(moveInstance);
//                 return true;
//             }
//         }

//         visited.erase(currentNode);
//         return false;
//     }

//     vector<pair<int, int>> getNeighbors(const pair<int, int>& currentNode) {
//         int row = currentNode.first;
//         int col = currentNode.second;

//         vector<pair<int, int>> neighbors;

//         // Move up
//         if (row > 0) {
//             neighbors.push_back({row - 1, col});
//         }

//         // Move down
//         if (row < graph.size() - 1) {
//             neighbors.push_back({row + 1, col});
//         }

//         // Move left
//         if (col > 0) {
//             neighbors.push_back({row, col - 1});
//         }

//         // Move right
//         if (col < graph[0].size() - 1) {
//             neighbors.push_back({row, col + 1});
//         }

//         return neighbors;
//     }
// };

// int main() {
//     // Example maze graph
//     vector<vector<int>> mazeGraph = {
//         {0, 0, 0},
//         {0, 0, 0},
//         {0, 0, 1}
//     };

//     // Create MazeSolver instance
//     MazeSolver mazeSolver(mazeGraph);

//     // Set start and target nodes
//     pair<int, int> startNode = {0, 0};
//     pair<int, int> targetNode = {2, 2};

//     // Solve the maze
//     vector<Move> path = mazeSolver.solveMaze(startNode, targetNode);

//     // Display the result
//     for (const auto& move : path) {
//         cout << "(" << move.row << "," << move.col << ") ";
//     }
//     cout << endl;

//     return 0;
// }
























    // vector<Move> solveMaze(const pair<int, int>& startNode, const pair<int, int>& targetNode) {
    //     path.clear();
    //     visited.clear();

    //     if (dfs(startNode, targetNode)) {
    //         reverse(path.begin(), path.end());  // Reverse the path to get the correct order
    //         return path;
    //     } else {
    //         cerr << "No solution found\n";
    //         return vector<Move>();
    //     }
    // }
