# Parallel-implementation-of-Floyd-Warshall-algorithm
The Floyd-Warshall algorithm is an algorithm for finding the shortest paths in a weighted graph with positive or negative edge weights (but with no negative cycles). A single execution of the algorithm will find the lengths (summed weights) of the shortest paths between all pairs of vertices.

The algorithm is based on the observation that the shortest path between two vertices in a graph may be obtained by traversing through intermediate vertices. The algorithm iteratively increases the number of intermediate vertices that are considered, until it has considered all possible paths.

The algorithm has a running time of O(n^3), where n is the number of vertices in the graph. It is not suitable for large graphs with millions of vertices, but it can be useful for small to medium-sized graphs.

The Floyd-Warshall algorithm is often used as a subroutine in other algorithms, such as the Johnson algorithm for finding the shortest paths in a graph with negative edge weights.
One of the main advantages of parallelizing the Floyd-Warshall algorithm is the ability to significantly reduce the running time of the algorithm on large graphs. This is because the algorithm has a high degree of parallelism, which can be exploited by using multiple processors to perform the calculations concurrently.

There are several approaches to parallelizing the Floyd-Warshall algorithm, including the use of 2-D block mapping and pipelined 2-D block mapping.

floydRowAndColumnImplementation.cpp: 2-D block mapping involves dividing the graph into blocks, and assigning each block to a different processor. The blocks are then processed in a sequence, with each processor updating the distances between the vertices within its block and the vertices in the blocks that have already been processed. This approach allows for good load balancing and efficient use of the processors, however the performance suffers from a synchronization step.

floydPipelineImplementation.cpp: Pipelined 2-D block mapping is a variant of 2-D block mapping that reduces the communication overhead by overlapping the communication and computation phases. In this approach, the blocks are processed in a pipeline, with each processor working on the next block in the pipeline while the previous block is being communicated to the next processor. 

