/*
* Description: Misc. network flow theorems and tricks
* Demo: Hall's marriage thm, Konig's thm, disconnecting defective nodes, edge/vertex disjoint path, suboptimal global min-cut
*/

Hall's marriage theorem for bipartite graphs:
  Let there be bipartite sets X and Y s.t. G = (X + Y, E). There is a matching that entirely covers X iff
  for every subset W of X, we have |W| <= |N(W)| where N(W) denotes set of neighbors of W
  
Konig's theorem for bipartite graphs:
  (# of edges in maximum matching of G) = (# of vertices in a minimum vertex cover)
                                        = |V| -  (# of vertices in maximum independent set)
                                        
  Minimum vertex cover: [nodes in left set of bipartite graph (connected to source) that are in T portion of ST cut] + 
                        [nodes in right set of bipartite graph (connected to sink) that are in S portion of ST cut]
                        
  Maximum independent set: [nodes in left set of bipartite graph (connected to source) that are in S portion of ST cut] + 
                           [nodes in right set of bipartite graph (connected to sink) that are in T portion of ST cut]
                                        
  Constructive proof: Kőnig's theorem can be proven in a way that provides additional useful information beyond just its truth: 
    the proof provides a way of constructing a minimum vertex cover from a maximum matching. 
    Let G=(V,E) be a bipartite graph, and let the vertex set V be partitioned into left set L and right set R.
    Suppose that M is a maximum matching for G. No vertex in a vertex cover can cover more than one edge of M 
    because the edge half-overlap would prevent M from being a matching in the first place, so if a vertex cover with |M| vertices
    can be constructed, it must be a minimum cover 
    
    To construct such a cover, let U be the set of unmatched vertices in L, and let Z be the set of vertices that are either in U
    or are connected to U by alternating paths (paths that alternate between edges that are in the matching and edges that are not
    in the matching). Let K = (L - Z) U (R - Z). Every edge e in E either belongs to an alternating path 
    (and has a right endpoint in K), or it has a left endpoint in K. For, if e is matched but not in an alternating path, 
    then its left endpoint cannot be in an alternating path (such a path would have had to have included e) and thus belongs to (L - Z)
    Alternatively, if e is unmatched but not in an alternating path, then its left endpoint cannot be in an alternating path, 
    for such a path could be extended by adding e to it. Thus, K forms a vertex cover.
    (Copy-pasted from wikipedia for reference during contest)
  
 Tutte's theorem (generalization of Hall's theorem): 
  Graph G = (V, E) has a perfect matching iff for every subset U of V, the subgraph induced by V − U 
  has at most |U| connected components with an odd number of vertices
  
  
Tricks: 
  1) To disconnect "defective" nodes from rest of graph, connect all defective nodes directly to a new sink node w/ INF capacity and
     connect source node to all nodes w/ INF capacity => min cut (aka max flow) will be cheapest way to disconnect the nodes
     
  2) Avoid antiparallel edges (not a problem for dinics, might need for ffa) by changing all antiparallel pairs (u, v)/(v, u) as follows:
     Replace (u, v) with (u, w), (w, v) where both new edges have capacity c(u, v)
     
  3a) # of edge disjoint paths from s to t is equivalent to max flow from s to t: you can recover solution by finding any path
     from s to t (with flow > 0 on all edges), removing these edges (set flow to 0) and repeat till all paths exhausted
     
  3b) # of vertex-disjoint paths can be done w/ same construction except we need i_in, i_out nodes for each original node i s.t.
      c(i_in, i_out) = 1, to recover solutions, only keep track of i_in to i_out edges
  
  4) global min cut can be suboptimally found in O(n) flow executions, by fixing source and looping over all other vertices
     as sink nodes (taking the min of all min-cuts to be global min-cut). global min cut = k iff graph is k-connected
     
