# Problem 92: Vector Search (HNSW)

## Description
Implement the graph traversal layer of HNSW for nearest neighbors.

## Learning Objectives
- **Concepts**: Graph Navigation, Distance Metrics (Cosine/L2), Greedy Search

## Implementation Guide
1. **Understand Layout**: Review how this component works in a real system.
2. **Define Structures**: Create the `struct` needed.
3. **Core Logic**: Implement the algorithm.
4. **Edge Cases**: Handle memory boundaries, overflows, or concurrency.

## Testing Strategy
- Verify fundamental correctness.
- Test boundary conditions.
- (If applicable) Performance benchmark.

## Pseudocode Hint
```text
// Add high-level logic here
```

## Solution Summary
The vector search engine implements approximate nearest neighbor search using algorithms like HNSW or IVF. It indexes high-dimensional embeddings, performs efficient similarity search (cosine/L2), prunes search space through hierarchical navigation or clustering, and enables semantic search for RAG systems, recommendation engines, and image retrieval.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/92_vector_search/solution.c)**
