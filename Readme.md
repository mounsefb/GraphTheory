# Project Summary: Shortest Path Algorithms in Graphs

## Overview
This project focused on implementing and comparing three algorithms for calculating the shortest path in a network graph. The primary goal was to determine the most efficient route between two cities or metro stations while addressing memory constraints and computational complexity when dealing with large datasets.

## Project Objectives
- Calculate optimal routes between two points in a network
- Compare three shortest path algorithms (DFS, BFS, Dijkstra)
- Test code performance with large datasets
- Develop project management and communication skills
- Enhance development tool proficiency

## Implementation Details

### Data Structures
Several data structures were modified or created to support the algorithms:

1. **Graph Structure (`graph_t`)**
   - Added a boolean field "oriente" to determine if the graph is directed
   - Added "initialise" field to prevent recursive initialization issues

2. **Vertex Structure (`vertex_t`)**
   - Added "plusproche" field to track nearest neighbor during path finding
   - Added "visited" flag to track vertices in search lists
   - Added "indiceTas" to maintain vertex position in the heap

3. **Additional Structures**
   - `listedge_t`: Linked list for graph edges
   - `fifoindice_t`: Queue implementation for BFS algorithm
   - Standard heap structures for Dijkstra's algorithm
   - Dictionary structures for metro station name mapping

### Algorithm Analysis

**Theoretical Complexity**

| Algorithm | Worst Time (n) | Best Time (n) | Worst Time (m) | Best Time (m) |
|-----------|----------------|---------------|----------------|---------------|
| DFS       | O(m^n)         | O(1)          | O(m^n)         | O(1)          |
| BFS       | O(n²)          | O(n)          | O(m)           | O(m)          |
| Dijkstra  | O(n²)          | O(n)          | O(m)           | O(1)          |

**Implemented Complexity**

| Algorithm | Worst Time (n) | Best Time (n) | Worst Time (m) | Best Time (m) |
|-----------|----------------|---------------|----------------|---------------|
| DFS       | O(m^n)         | O(1)          | O(m^n)         | O(1)          |
| BFS       | O(n)           | O(n)          | O(m)           | O(m)          |
| Dijkstra  | O(n²)          | O(n log n)    | O(m²)          | O(1)          |

### Project Status
- **Functional Components**: All implemented algorithms pass 386/386 tests
- **Issues**: Dijkstra's algorithm shows higher than expected complexity, possibly due to implementation inefficiencies

## Team Organization
The team of two members (Mounsef Bouhar and Jean-Baptiste Blasselle) divided work as follows:

- **Initial Phase**: Both members worked individually on core data structures and functions for lists, queues, heaps, and dictionaries
- **Specialized Tasks**:
  - Mounsef: BFS implementation, file reading, result display, and Paris metro application
  - Jean-Baptiste: DFS and Dijkstra implementations
- **Collaborative Work**: Mutual code review, testing, and debugging

## Conclusion
The project successfully implemented and compared three different shortest path algorithms. The team gained deeper understanding of the C programming language and various data structures. Significant challenges in optimization, memory management, and complexity were addressed throughout development.

The project validated the importance of development tools like Git for version control and Valgrind for memory debugging, providing valuable experience in addressing real-world programming challenges.
