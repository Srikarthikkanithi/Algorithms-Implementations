#include <bits/stdc++.h>
using namespace std;
// genric priority_queue for djikstra-type algom
class Undirected_graph;
class Edge_weight_pair;
class State
{
private:
  string id;
  int weight;
  int parity;

public:
  State() = default;
  State(string id1, int w1, int p1)
  {
    id = id1;
    weight = w1;
    parity = p1;
  }
  bool operator<(const State &a)
  {
    return weight < a.weight;
  }
  bool operator>(const State &a)
  {
    return weight > a.weight;
  }
  friend class Undirected_graph;
};
template <typename T>
class Generic_pro_que
{
  vector<T> pq; // implementing the priority queue using a vector and adding,deleting etc. by percolations
  int pq_size;
  int max_size;

public:
  // constructors
  Generic_pro_que()
  {
    pq_size = 0;
    max_size = 1;
    pq.resize(max_size);
  }
  const size_t size() const; // func for calculating the size of the priority queue
  void push(T t1);           // func for pushing an element into a priority_queue
  void pop();                // func for popping an element into a priority_queue
  const T &top() const;      // func for calculating the top element of my priority_queue
  const bool empty() const;  // checking whether my priority queue is empty or not
  void percolate_up(int i)
  {
    T e = pq[i];
    while (i > 0 && pq[(i - 1) / 2] > e)
    {
      pq[i] = pq[(i - 1) / 2];
      i = (i - 1) / 2;
    }
    pq[i] = e;
    return;
  }
  void percolate_down(int i)
  {
    T e = pq[i];
    while (2 * i + 1 < pq_size)
    {
      int child1 = 2 * i + 1, child2 = 2 * i + 2, childmax = child1;
      if (child2 < pq_size && pq[child2] < pq[child1])
      {
        childmax = child2;
      }
      if (pq[childmax] > e)
      {
        break;
      }
      pq[i] = pq[childmax];
      i = childmax;
    }
    pq[i] = e;
  }
  friend class Undirected_graph;
};
template <typename T>
const size_t Generic_pro_que<T>::size() const
{
  return pq_size;
}
template <typename T>
void Generic_pro_que<T>::push(T t1)
{
  if (pq_size == max_size)
  {
    max_size *= 2;
    pq.resize(max_size);
  }
  pq[pq_size] = t1;
  int prev_size = pq_size;
  pq_size++;
  percolate_up(prev_size);
}
template <typename T>
void Generic_pro_que<T>::pop()
{
  if (pq_size == 0)
  {
    return;
  }
  if (pq_size == 1)
  {
    pq_size--;
    return;
  }
  pq[0] = pq[pq_size - 1];
  pq_size--;
  percolate_down(0);
}
template <typename T>
const T &Generic_pro_que<T>::top() const
{
  return pq[0];
}
template <typename T>
const bool Generic_pro_que<T>::empty() const
{
  return pq_size == 0;
}
// class Node to store the info of the room such as roomid,pointers to the nxt node
class Node
{
private:
  string Room_id;
  pair<int, int> weight;
  vector<pair<string, int>> nxtroom_ptrs; // nxtroomptrs point to the nxt room node and the weight of the corresponding edge
public:
  // constructors for node class
  Node() = default;
  Node(string roomid)
  {
    Room_id = roomid;
    weight = {INT_MAX, INT_MAX};
  }
  // getter and setter for node class's id
  string get_id()
  {
    return Room_id;
  }
  void set_id(string id1)
  {
    Room_id = id1;
  }
  // comparison operators of Node class for the use in priority_queue;
  bool operator<(const Node &id1) const
  {
    return min(weight.first, weight.second) < min(id1.weight.first, id1.weight.second);
  }
  bool operator>(const Node &id1) const
  {
    // return weight>id1.weight;
    return min(weight.first, weight.second) > min(id1.weight.first, id1.weight.second);
  }
  bool operator>=(const Node &id1) const
  {
    // return weight>=id1.weight;
    return min(weight.first, weight.second) >= min(id1.weight.first, id1.weight.second);
  }
  Node &operator=(const Node &id1)
  {
    weight = id1.weight;
    Room_id = id1.Room_id;
    nxtroom_ptrs = id1.nxtroom_ptrs;
    return *this;
  }
  bool operator==(const Node &id1)
  {
    return weight == id1.weight;
  }
  void print()
  {
    cout << Room_id << " : " << weight.first << " : " << weight.second << " : nxtrooms " << endl;
    for (auto &i : nxtroom_ptrs)
    {
      cout << (i.first) << " : " << i.second << endl;
    }
  }
  friend class Undirected_graph;
};
// creating an undirected graph to store the nodes info,weights info
class Undirected_graph
{
private:
  unordered_map<string, Node> node_info; // storing the id:info of the node of that id ;
public:
  // constructor for Undirected_graph class
  Undirected_graph() = default;
  // mintime func for implementing the req time for harrypotter
  void min_time(string id1, string id2)
  {
    node_info[id1].weight.first = 0;

    Generic_pro_que<State> distance_pq;
    State s1(id1, 0, 0);
    distance_pq.push(s1);
    while (!distance_pq.empty())
    {
      State current = distance_pq.top();
      distance_pq.pop();

      if (current.parity == 0 && current.weight > node_info[current.id].weight.first)
        continue;
      if (current.parity == 1 && current.weight > node_info[current.id].weight.second)
        continue;

      for (auto &edge : node_info[current.id].nxtroom_ptrs)
      {
        string nxt = edge.first;
        int w = edge.second;
        int new_dist = current.weight + w;
        int new_parity = 1 - current.parity;

        if (new_parity == 0 && new_dist < node_info[nxt].weight.first)
        {
          node_info[nxt].weight.first = new_dist;
          State t1(nxt, new_dist, new_parity);
          distance_pq.push(t1);
        }
        if (new_parity == 1 && new_dist < node_info[nxt].weight.second)
        {
          node_info[nxt].weight.second = new_dist;
          State t1(nxt, new_dist, new_parity);
          distance_pq.push(t1);
        }
      }
    }

    int ans = node_info[id2].weight.first;
    if (ans == INT_MAX)
    {
      cout << -1 << endl;
    }
    else
    {
      cout << ans << endl;
    }
  }
  // instating a new node:used in first for loop in main
  void insert_new_Node(string id1)
  {
    node_info[id1].Room_id = id1;
    node_info[id1].weight = {INT_MAX, INT_MAX};
  }
  // modifying the node after knowing edges and edge weights
  void modify_node(string id1, string id2, int wi)
  {
    (node_info[id1].nxtroom_ptrs).push_back({id2, wi});
    (node_info[id2].nxtroom_ptrs).push_back({id1, wi});
  }
  void print_graph()
  {
    for (auto &i : node_info)
    {
      cout << i.first << " info  : " << endl;
      cout << i.second.Room_id << " : " << i.second.weight.first << " : " << i.second.weight.second << " : " << endl;
      for (auto &j : i.second.nxtroom_ptrs)
      {
        cout << j.first << " : " << j.second << endl;
      }
      cout << endl;
    }
  }
};
int main()
{
  int n, m;
  cin >> n >> m;
  Undirected_graph ug;
  for (int i = 0; i < n; i++)
  {
    string id;
    cin >> id;
    ug.insert_new_Node(id);
  }
  for (int i = 0; i < m; i++)
  {
    string id1, id2;
    int wi;
    cin >> id1 >> id2 >> wi;
    ug.modify_node(id1, id2, wi);
  }
  // ug.print_graph();
  string s_id, d_id;
  cin >> s_id >> d_id;
  ug.min_time(s_id, d_id);
}
