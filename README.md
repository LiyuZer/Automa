# Automa  
Automa - A Graph-Based Programming Language  

Automa is a programming language where all computation revolves around graphs. The idea is to create a programming language where calculation at any point is in 3 distinct states: accepted, rejected, or pending. Automa does this by representing all computations as graph traversals combined with some action of memory, so given a particular graph and input memory, the memory will either be transformed by the computation(i.e., the calculation is accepted) or rejected. 

Automa eliminates constructs like **if statements**, **loops**, and **procedures**, instead operating entirely on **graphs** that interact with memory.  

At its core, every program in Automa is a **graph** consisting of nodes and transitions. Transitions define paths between nodes and are represented as tuples of **conditions** and **operations**:  
- **Conditions**: Evaluate to `true` or `false` to determine if a transition is valid. **Cannot** change the graph's memory in any way, thus having no side effects.  
- **Operations**: Act on memory, modifying or interacting with stored data.  

Automa supports deterministic and (soon-to-be fully implemented) **nondeterministic automata**, allowing for multiple paths to be traversed simultaneously in graphs with multiple valid transitions.  

## Key Features  
- **Graph-Based Computation**: Every computation is modeled as a graph traversal.  
- **Memory-Driven Logic**: Operations manipulate memory structures, which graphs process during execution.  
- **Deterministic and Nondeterministic Support**: Explore multiple parallel paths for nondeterministic computations.  
- **Immutable Graphs**: Graphs cannot be modified after creation, ensuring a consistent and predictable execution model.  
- **Minimal Constructs**: No loops, conditionals, or procedures—just transitions, nodes, and memory.  
- **Minimal Rollback**: Memory is only set **after** an accept state has been reached and a path has been completed,
  ensuring that only Accepted computations make persistent changes to memory. 

## Graph States  
Each graph operates within one of the following states:  
1. **Execution State**: Actively traversing nodes and transitions.  
2. **Reject State**: The graph rejects the current computation.  
3. **Accept State**: The graph successfully completes and accepts the computation.  
4. **Void State**: The graph is idle or inactive.  

Graphs may also be **non-halting**, enabling infinitely running computations where appropriate.  

---

## Example: DFA for Regex `a*bc*d`  

Here is an example program in Automa that implements a DFA matching the regular expression `a*bc*d`.  

```automa
graph dfaRegex {
  memory {
      input: None,
      current_index: 0
  }

  nodeDef {
      start: StartNode,
      accept: AcceptNode,
      reject: RejectNode
  }

  transitions {
      // Start node transitions
      start reject => conditions(len(input) == 0), operations();
      start a => conditions(), operations();
      start b => conditions(), operations();

      // Node a transitions
      a a => conditions(input[current_index] == 'a'), operations(current_index = current_index + 1);
      a b => conditions(), operations();

      // Node b transitions
      b c => conditions(input[current_index] == 'b'), operations(current_index = current_index + 1);

      // Node c transitions
      c c => conditions(input[current_index] == 'c'), operations(current_index = current_index + 1);
      c d => conditions(), operations();

      // Node d transitions
      d accept => conditions(input[current_index] == 'd'), operations(current_index = current_index + 1);
  }
}
```

### Explanation:  
- **Memory**: Contains the `input` string and a `current_index` to track traversal.  
- **Nodes**:  
  - `start`: The starting point.  
  - `accept`: The accepting state for valid inputs.  
  - `reject`: The rejecting state for invalid inputs.  
- **Transitions**: Define conditions for moving between nodes and operations for modifying memory.  

---

## Getting Started  

### Prerequisites  
- **C++ Compiler**: Automa is implemented in C++, so a compiler is necessary.  
- **ANTLR**: Used for parsing and lexing Automa syntax.  

### Installation  
Clone the repository:  
```bash
git clone https://github.com/your-username/automa.git  
cd automa  
```

Compile the interpreter:  
```bash
make
```

Run an Automa program:  
```bash
./automa examples/dfaRegex.automa
```

---

## Roadmap  

- **Version 1 Goals**:  
  - Deterministic and nondeterministic graph traversal.  
  - Basic data structures: lists, dictionaries, and memory containers.  
  - Core primitive types: integers, strings, characters.  

- **Future Features**:  
  - Built-in support for advanced automata (e.g., Turing machines).  
  - Custom helper graphs for modular and reusable computations.  
  - Optimizations for memory and graph traversal.  

---

## Contributing  
Automa is an open-source project. Contributions are welcome! If you have ideas or improvements, feel free to submit a pull request.  

---

## License  
Automa is licensed under the [MIT License](LICENSE).  

Happy graphing! 🎉  

