#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
// Data structure to represent a move
struct Move {
    int spaces;
    std::string direction;
};

// Function to construct the graph from the maze
std::vector<std::vector<std::pair<int, std::string>>> constructGraph(const std::vector<std::vector<std::string>>& maze) {
    int rows = maze.size();
    int cols = maze[0].size();

    std::vector<std::vector<std::pair<int, std::string>>> graph(rows, std::vector<std::pair<int, std::string>>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Extract spaces and direction from the maze cell
            int spaces;
            std::string direction;
            sscanf(maze[i][j].c_str(), "%d%s", &spaces, &direction[0]);

            // Add the edge to the graph
            graph[i][j] = std::make_pair(spaces, direction);
        }
    }

    return graph;
}

// Function to find the path using BFS
std::vector<Move> findPath(const std::vector<std::vector<std::pair<int, std::string>>>& graph) {
    int rows = graph.size();
    int cols = graph[0].size();

    std::vector<Move> path;

    // Starting point
    std::pair<int, int> start = std::make_pair(0, 0);

    // Bull's-eye
    std::pair<int, int> end = std::make_pair(rows - 1, cols - 1);

    // Initialize BFS
    std::queue<std::pair<int, int>> bfsQueue;
    std::set<std::pair<int, int>> visited;
    bfsQueue.push(start);
    visited.insert(start);

    while (!bfsQueue.empty()) {
        std::pair<int, int> currentVertex = bfsQueue.front();
        bfsQueue.pop();

        // Check if the current vertex is the destination
        if (currentVertex == end) {
            // Reconstruct the path
            while (currentVertex != start) {
                // Extract the direction and spaces from the graph
                int spaces = graph[currentVertex.first][currentVertex.second].first;
                std::string direction = graph[currentVertex.first][currentVertex.second].second;

                // Add the move to the path
                path.push_back({spaces, direction});

                // Move to the previous vertex
                if (direction == "N") currentVertex.first += spaces;
                else if (direction == "S") currentVertex.first -= spaces;
                else if (direction == "E") currentVertex.second += spaces;
                else if (direction == "W") currentVertex.second -= spaces;
                else if (direction == "NE") { currentVertex.first += spaces; currentVertex.second += spaces; }
                else if (direction == "SE") { currentVertex.first -= spaces; currentVertex.second += spaces; }
                else if (direction == "SW") { currentVertex.first -= spaces; currentVertex.second -= spaces; }
                else if (direction == "NW") { currentVertex.first += spaces; currentVertex.second -= spaces; }
            }

            // Reverse the path to get it in the correct order
            std::reverse(path.begin(), path.end());
            
            return path;
        }

        // Explore neighbors
        int currentRow = currentVertex.first;
        int currentCol = currentVertex.second;
        int spaces = graph[currentRow][currentCol].first;

        if (graph[currentRow][currentCol].second == "R") {
            // Move to the right
            int newCol = currentCol + spaces;
            if (newCol < cols && visited.find({currentRow, newCol}) == visited.end()) {
                bfsQueue.push({currentRow, newCol});
                visited.insert({currentRow, newCol});
            }
        } else if (graph[currentRow][currentCol].second == "B") {
            // Move down
            int newRow = currentRow + spaces;
            if (newRow < rows && visited.find({newRow, currentCol}) == visited.end()) {
                bfsQueue.push({newRow, currentCol});
                visited.insert({newRow, currentCol});
            }
        }
            else if (graph[currentRow][currentCol].second == "NE") {
                // Move to the northeast
                int newRow = currentRow + spaces;
                int newCol = currentCol + spaces;
                if (newRow < rows && newCol < cols && visited.find({newRow, newCol}) == visited.end()) {
                    bfsQueue.push({newRow, newCol});
                    visited.insert({newRow, newCol});
                }
            } else if (graph[currentRow][currentCol].second == "SE") {
                // Move to the southeast
                int newRow = currentRow - spaces;
                int newCol = currentCol + spaces;
                if (newRow >= 0 && newCol < cols && visited.find({newRow, newCol}) == visited.end()) {
                    bfsQueue.push({newRow, newCol});
                    visited.insert({newRow, newCol});
                }
            } else if (graph[currentRow][currentCol].second == "SW") {
                // Move to the southwest
                int newRow = currentRow - spaces;
                int newCol = currentCol - spaces;
                if (newRow >= 0 && newCol >= 0 && visited.find({newRow, newCol}) == visited.end()) {
                    bfsQueue.push({newRow, newCol});
                    visited.insert({newRow, newCol});
                }
            } else if (graph[currentRow][currentCol].second == "NW") {
                // Move to the northwest
                int newRow = currentRow + spaces;
                int newCol = currentCol - spaces;
                if (newRow < rows && newCol >= 0 && visited.find({newRow, newCol}) == visited.end()) {
                    bfsQueue.push({newRow, newCol});
                    visited.insert({newRow, newCol});
                }
}

    }

    // If the loop completes, no path is found
    std::cerr << "No path found\n";
    return path;
}

int main() {
    std::ifstream inputFile("input.txt");
    int rows, cols;
    inputFile >> rows >> cols;

    std::vector<std::vector<std::string>> maze(rows, std::vector<std::string>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            inputFile >> maze[i][j];
        }
    }

    std::vector<std::vector<std::pair<int, std::string>>> graph = constructGraph(maze);
    std::vector<Move> path = findPath(graph);

    std::ofstream outputFile("output.txt");
    for (const auto& move : path) {
        outputFile << move.spaces << move.direction << " ";
    }

    return 0;
}
