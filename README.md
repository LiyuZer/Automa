# Automa
Automa - A Graph-Based Programming Language
Automa is a unique programming language where all computation revolves around graphs. It’s designed to be a fully graph-based programming language with no if statements, loops, procedures, etc. It is entirely based on graphs that act on memory. 

Fundamentally, each graph can be seen as a tuple of nodes and transitions where each transition defines a path from one Node to another. Each transition itself is a tuple of 
operations and conditions, where an operation acts on memory, a condition always returns a true or false, making a specific transition valid. 

Each graph has at least three nodes: the start node, the rejecting node, and the access node. Thus, a graph can only be in 4 states at any time: execution rejected state, accept state, and void state, where it is not running at all. There might be graphs that never halt. Thus, we might have infinitely running graphs, for example. 

Did I forget to mention that it supports nondeterministic(in the works lol) automata as well :) Graphs with many different possible transitions can have multiple paths traversed!


Some example programs are written in automatic.

Take the Regex expression a*bc*d 

graph dfaRegex{
  memory{
      input : None,
      current_index : 0
      }

  nodeDef {
  start :: StartNode,
  accept :: AcceptNode,
  reject :: RejectNode,
  }

  transitions{
  start reject => conditions(len(input) == 0), operations();
  start a => conditions(), operations();
  start b => conditions(), operations();
  // node a conditions
  a a => conditions(input[current_index] == 'a'), operations(current_index = current_index + 1);
  a b => conditions(), operations();

  // node b conditions 
  b c => conditions(input[current_index] == 'b), operations(current_index = current_index + 1);

  // node c conditions
  c c => conditions(input[current_index] == 'c'), operations(current_index = current_index + 1);
  c d => conditions(), operations();

  // node d conditions
  d accept => conditions(input[current_index] == 'b), operations(current_index = current_index + 1);

  }
}






