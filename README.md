# AI-A*-for-Romanian-cities-problem
Comparison between A* for Romanian cities problem, using f(n)=a*g(n) + b*h(n) for different values of a and b. Try a, b in {0.2 ,я 0.5 , 0.7 , 1 , 1.2 , 1.5 , 2}. You will thus have 49 combinations and we are interested in the number of nodes developed (you will count them and save them in a text file in CSV format).

**File Organization**
- romania_map.h contains all city and heuristic data.
- astar.cpp handle the algorithm, manages input, output, and the main program logic.

**Results and Analysis**
By analyzing a_star_results.csv, we can observe how varying the values of 
𝑎 and 𝑏 impacts the algorithm’s efficiency. For example:
- Higher values of 𝑏 emphasize the heuristic, which may decrease the nodes explored by prioritizing paths closer to Bucharest.
- Lower values of 𝑏 increase reliance on 𝑔(𝑛), resulting in more exhaustive exploration, potentially expanding more nodes.
The project showcases the trade-offs between heuristic-driven and path-cost-driven search strategies in the A* algorithm and offers insights into balancing efficiency with optimality.

**Bibliograpy**
Russel and Norvig - Artifficial Intelligence, A Modern Approach, 2nd Edition. 
Chapter 4. Informed Search and Exploration 

Course: Artificial Inteligence
Bachelor: Computer Science, Year 3
West University of Timisoara, Romania
