#include <vector>
#include <iostream>

using std::vector;

class Edge{
public:
    int v1;      //vertex 1
    int v2;      //vertex 2
    int weight;  //cost to go from v1 to v2 or from v2 to v1

    Edge(int v1 = 0, int v2 = 0, int weight = 0){
        this->v1 = v1;
        this->v2 = v2;
        this->weight = weight;
    }

    /*Order of priorities:
        weight
        v1
        v2
    */
    bool bigger_than(Edge e){
        if(this->weight > e.weight) return true;
        if(this->weight < e.weight) return false;

        if(this->v1 > e.v1) return true;
        if(this->v1 < e.v1) return false;
        
        if(this->v2 > e.v2) return true;
        if(this->v2 < e.v2) return false;

        return false;
    }

    void print(){
        std::cout << "[" << this->v1 << ", " << this->v2 << ", " << this->weight << "]" << std::endl;
    }

};


class Min_heap{
public:
    std::vector<Edge> heap;

    //swaps an element of the list with it's parent
    void swap(int i){
        Edge tmp = this->heap[i];
        this->heap[i] = this->heap[(i-1)/2];
        this->heap[(i-1)/2] = tmp;}

    //takes an item that's been inserted at the beggining of the list to it's correct position
    void heapify_down(){
        int i = 0;
        int list_size = this->heap.size();

        Edge parent;  // i
        Edge child_1; // 2*i + 1
        Edge child_2; // 2*i + 2
        Edge smallest_child;
        int index;

        //special case for when the list only has 2 items (was having rounding errors)
        if(list_size == 2){
            if(this->heap[0].bigger_than(this->heap[1])){
                Edge tmp = this->heap[0];
                this->heap[0] = this->heap[1];
                this->heap[1] = tmp;
                return;
            }
            else return;
        }

        //general case -> if parent is bigger than one of it's children, they get swapped
        while(2*i + 2 < list_size){
            parent = this->heap[i];
            child_1 = this->heap[2*i + 1];
            child_2 = this->heap[2*i + 2];

            smallest_child = (child_1.bigger_than(child_2)) ? child_2 : child_1;
            index = (child_1.bigger_than(child_2)) ? 2 : 1;

            if(parent.bigger_than(smallest_child)){ 
                this->swap(2*i+index);}

            i++;}
    }

    //takes an item that's been inserted in the end of the list to it's correct position
    void heapify_up(){
        int heap_size = this->heap.size()-1;
        int i;

        Edge parent; // (i - 1)/2
        Edge child;  // i

        for(i = heap_size; i > 0; i-- ){
            parent = this->heap[(i-1)/2];
            child = this->heap[i];

            if(parent.bigger_than(child))
                this->swap(i);

        }
    }

    //adds a newd item to the list and takes it to it's correct place
    void push(Edge new_edge){
        this->heap.push_back(new_edge);
        this->heapify_up();}

    Edge pop(){

        Edge val = this->heap[0];

        //special case for when the list only has one item -> returns it and clears the list
        if(this->heap.size() == 1){
            vector<Edge> empty_vec = {};
            this->heap.swap(empty_vec); //had to use swap for an empty vector, for having problems with Vector::size not resetting after using Vector::clear
            return val;}

        //copies the last item to the beggining of the list, and returns the original item
        this->heap[0] = this->heap[this->heap.size()-1];
        this->heap.pop_back();//removes the last item

        this->heapify_down();//reorders the list (for last item is now at the top)

        return val;
    }

    void print(){
        int list_size = this->heap.size();
        int i;

        for(i = 0; i < list_size; i++)
            std::cout<< "[" << this->heap[i].v1 << ", " <<this->heap[i].v2 << ", " << this->heap[i].weight << "] ";

        std::cout << std::endl;
    }

    bool is_empty(){
        return this->heap.empty();
    }
};

class Graph{
public:
    int vertexes;
    int edges;
    vector<vector<Edge>> adj_list;
    vector<Edge> edge_list; //lazy solution to calculate the graph's cost

    Graph(int vertexes = 0, int edges = 0){
        this->vertexes = vertexes;
        this->edges = edges;

        vector<Edge> empty_vec = {};
        for(int i = 0; i< vertexes; i++) this->adj_list.push_back(empty_vec);
    }

    void reset(){//clears adjacency list and edge list
        vector<vector<Edge>> empty_vec = {};
        vector<Edge> empty_vec_ = {};

        this->adj_list.swap(empty_vec);
        this->edge_list.swap(empty_vec_);}

    void add_edge(Edge new_edge){
        int v1 = new_edge.v1;
        int v2 = new_edge.v2;
        Edge edge = new_edge;

        if(v1 > v2) edge = Edge(v2, v1, new_edge.weight);//makes it so that edge's "smallest" vertex is always v1

        this->adj_list[v1].push_back(edge);
        this->adj_list[v2].push_back(edge);
        this->edge_list.push_back(edge);
        }

    int cost(){//returns sum of the weight of all the edges of the graph
        int cost = 0;
        int i;

        for(i = 0; i< this->edge_list.size(); i++)
            cost += this->edge_list[i].weight;

        return (int) cost;

    }

    void print(){
        int inner_size;
        int i;
        int j;
        int cost;

        for(i = 0 ; i< this->vertexes; i++){
            std::cout << i << ": ";
            inner_size = this->adj_list[i].size();

            for(j = 0; j < inner_size; j++){
                std::cout << "[" << this->adj_list[i][j].v1 << ", ";
                std::cout << this->adj_list[i][j].v2 << ", ";
                std::cout << this->adj_list[i][j].weight << "] ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

};

// PRIM ALGORITHM BETTER DESCRIBED IN README FILE
// returns the minimum spanning tree of a Graph object
// prints MST edges in the order they're discovered
Graph prim(Graph graph, int v, int num_edges, int num_vertexes){
    Graph mst = Graph(num_vertexes, num_edges);
    vector<bool> visited;
    int i;
    vector<Edge> adj;
    Min_heap seen;
    Edge a;
    int nv;

    vector<Edge> TE;

    for(i = 0; i< num_vertexes + 1; i++) visited.push_back(false);

    adj = graph.adj_list[v];
    for(i = 0; i<graph.adj_list[v].size(); i++)
        seen.push(adj[i]);

    visited[v] = true;

    while(seen.is_empty() == false){
        a = seen.pop();

        if(visited[a.v1] && visited[a.v2]) continue;

        if(!visited[a.v1])
            nv = a.v1;
        else nv = a.v2;

        visited[nv] = true;

        adj = graph.adj_list[nv];

        for(i=0; i < adj.size(); i++)
            if  (!visited[adj[i].v1] || !visited[adj[i].v2]){
                seen.push(adj[i]);
            }
        std::cout << a.v1 << " " << a.v2 << " " << a.weight << std::endl;
        mst.add_edge(a);
    }
    return mst;
}

int main(void){

    int v1,v2,w;
    int original_cost = 0;
    int vertexes = 0;
    int edges = 0;
    int i;
    Graph mst;

    while(true){

        original_cost = 0;

        std::cin >> vertexes;
        std::cin >> edges;

        if(vertexes == 0 && edges == 0) break;

        Graph graph = Graph(vertexes, edges);

        for(i = 0; i<edges; i++){
            std::cin >> v1;
            std::cin >> v2;
            std::cin >> w;

            graph.add_edge(Edge(v1, v2, w));

            original_cost += w;}

        mst = prim(graph, int((vertexes-1)/2), edges, vertexes);
        int new_cost = mst.cost();

        std::cout << original_cost - new_cost << std::endl;
    }

return 0;}
