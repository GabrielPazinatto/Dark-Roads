# Dark-Roads

###This is a small project I developed for my Graph Theory course. A part of it's definition can be found [here](https://www.beecrowd.com.br/repository/UOJ_1152_en.html).
	
## Basic explanation
* The challenge consisted on using _Prim's Algorithm_ to determine the minimum spanning tree of a graph (as a representation of a city), and calculating the difference between it's cost and the original graph's total cost.
* For a matter of efficiency, a priority queue had to be used. I had to code one myself, because of the next item:
* As an additional part of the challenge, the program should be able to print the MST's edges in the order they were found. For it to be possible, the heapify functions must consider an order of priorities.

## Prim's algorithm pseudo-code:

Given a connected wheighted graph = **G**:
```
0. Variables:

a ------- (edge)
v ------- (vertex)
n ------- (vertex)
visited - (list)
seen ---- (list)     //implemented as a priority queue
mst ----- (list)

1. Begin:
	- v <- any vertex of G (starting point)
	- visited[] <- list of visited vertexes
	- seen[] <- list of edges adjacent to v
	- mst[] <- set of mst edges

	2. while seen is not empty:
		- a <- "smallest" edge in seen (pop)
		- if both vertexes of a have been visited, skips iteration
		- nv <- only vertex on which a is adjacent to and hasn't been visited
		- visited[nv] <- true
		- seen <-+ edges adjacent to nv and to a vertex that's not been visited
		- mgt <-+ a
  ```
  
## Order of priorities for the algorithm:
Consider that seen[0] should always contain the "smallest" edge in seen. An edge can be represented as _(v1, v2, w)_, where:
* v1 is a vertex;
* v2 is a vertex;
* w is the cost of the edge between v1 and v2;

The "smallest" edge is:
1. The edge with the smallest weight.
2. The edge with the smallest v1.
3. The edge with the smallest v2.

## TODO:
- [ ] Add sample input and output files.
- [ ] Add test script.
