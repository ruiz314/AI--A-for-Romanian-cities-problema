#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cmath>
#include <fstream>
#include "romania_map.h"

using namespace std;

/** @author Inés Ruiz Sánchez
 * @brief Assignment 25.
 * Comparison between A* for Romanian cities problem, using f(n)= a*g(n) + b*h(n) for different values of a and b. 
 * Try a, b in {0.2 ,я 0.5 , 0.7 , 1 , 1.2 , 1.5 , 2}. 
 * You will thus have 49 combinations and we are interested in the number of nodes developed (you will count them 
 * and save them in a text file in CSV format). 
 * E.g "0.2 ; 0.7 ; number_of_nodes_developed" and so on, 49 lines in total
 * 
 * Bibliograpy:
 *      1) Russel and Norvig - Artifficial Intelligence, A Modern Approach, 2nd Edition
 */


// Node structure for A* search
// Each node in the priority queue represents a city with its associated g (path cost) and f (evaluation function) values.
struct Node {
    string city;
    int g; // Path cost
    int f; // f(n) = a * g(n) + b * h(n)

    // Operator overloading for comparing nodes in the priority queue
    // (to prioritize nodes with lower f values).
    bool operator>(const Node &other) const {
        return f > other.f;
    }
};

/** @brief A* search algorithm
 * For each explored node, its neighbors are evaluated, and if a better path is found, it is added to the queue.
 * The algorithm terminates when the goal (Bucharest) is reached.
 * We also track the number of nodes developed (expanded) during the search.
 * */ 
int a_star(string start, string goal, double a, double b) {
    priority_queue<Node, vector<Node>, greater<Node>> open_list; // To explore nodes with the lowest f(n) values first.
    unordered_map<string, int> g_cost;
    unordered_map<string, bool> visited;
    int nodes_developed = 0;

    // Initialize
    g_cost[start] = 0;
    open_list.push({start, 0, static_cast<int>(a * 0 + b * heuristic[start])}); //open_list.push({start, 0, a * 0 + b * heuristic[start]});
    //We need to cast to int because the f field in the Node structure is defined as an int.

    while (!open_list.empty()) {
        Node current = open_list.top();
        open_list.pop();

        // If we reached the goal, return the number of nodes developed
        if (current.city == goal) {
            return nodes_developed;
        }

        if (visited[current.city]) continue;
        visited[current.city] = true;
        nodes_developed++;

        // Explore neighbors
        for (const auto &neighbor : romania_map[current.city]) {
            string next_city = neighbor.first;
            int edge_cost = neighbor.second;
            int tentative_g = g_cost[current.city] + edge_cost;

            if (!visited[next_city] || tentative_g < g_cost[next_city]) {
                g_cost[next_city] = tentative_g;
                int f = static_cast<int>(a * tentative_g + b * heuristic[next_city]); //int f = a * tentative_g + b * heuristic[next_city];
                open_list.push({next_city, tentative_g, f});
            }
        }
    }

    return nodes_developed; // If goal is not reached (should not happen with valid data)
}

// Main function
int main() {
    // Combinations of a and b
    vector<double> factors = {0.2, 0.5, 0.7, 1.0, 1.2, 1.5, 2.0};
    
    // Output CSV file
    ofstream csv_file("a_star_results.csv"); //Itd has the number of nodes developed for each combination of a and b.
    csv_file << "a;b;nodes_developed\n";

    // Run A* for all combinations of a and b
    for (double a : factors) {
        for (double b : factors) {
            int nodes_developed = a_star("Arad", "Bucharest", a, b);
            csv_file << a << ";" << b << ";" << nodes_developed << "\n";
        }
    }

    csv_file.close();
    cout << "Results saved to a_star_results.csv" << endl;

    return 0;
}