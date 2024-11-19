# Automa
Automa - A Graph-Based Programming Language
Automa is a unique programming language where all computation revolves around graphs. It’s designed to be a fully graph-based programming language with no if statements, loops, procedures, etc. It is entirely based on graphs that act on memory. 

Fundamentally, each graph can be seen as a tuple of nodes and transitions where each transition defines a path from one Node to another. Each transition itself is a tuple of 
operations and conditions, where an operation acts on memory, a condition always returns a true or false, making a specific transition valid. 

Each graph has at least three nodes: the start node, the rejecting node, and the access node. Thus, a graph can only be in 4 states at any time: execution rejected state, accept state, and void state, where it is not running at all. There might be graphs that never halt. Thus, we might have infinitely running graphs, for example. 

Did I forget to mention that it supports nondeterministic automata as well :) Graphs with many different possible transitions can have multiple paths traverseed!



