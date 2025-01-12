# Automa  
Automa - A Graph-Based Programming Language  

Automa is a programming language where all computation revolves around graphs. The idea is to create a programming language where calculation at any point is in 3 distinct states: accepted, rejected, or pending. Automa does this by representing all computations as graph traversals combined with some action on memory, so given a particular graph and input memory, the memory will either be transformed by the computation(i.e., the calculation is accepted) or rejected. 

At its core, every program in Automa is a **graph** consisting of nodes and transitions. Transitions define paths between nodes and are represented as tuples of **conditions** and **operations**:  
- **Conditions**: Evaluate to `true` or `false` to determine if a transition is valid. **Cannot** change the graph's memory, thus having no side effects.  
- **Operations**: Act on memory, modifying or interacting with stored data.  

Automa supports deterministic and (soon-to-be fully implemented) **nondeterministic automata**, allowing multiple paths to be traversed simultaneously in graphs with multiple valid transitions.  


## Philosophy 
The philosophy of Automa is to create a closed programming language that only interacts with the development environment and memory if the computation is accepted, the goal being 
to create a programming language where rollback is inherent and isolation is ensured. Hopefully, this will develop safe and robust programs that are transparent in the description.

Another crucial philosophical framework for Automa is representing computation using discreet steps, represented as a finite state machine. This way, computation becomes a first-class citizen much more granularly than traditional functions. Traditional programs are viewed as statements to be executed one after the other, performing some tasks. 
Automa, on the other hand, is a structure-based programming language; we are running the structure rather than statement-by-statement flows. This way, we can take and optimize the structure, make it faster, evolve it over time, and create new structures using previous structures.  

Finally, programming should be more intuitive. With a graph-based programming language, visual representations of code will be more straightforward. Hopefully, this will make it easier to debug code, teach code, and demonstrate workflows; in other words, I am so tired of reading Python errors :)

## Personal Motivations 
I have always wanted a graph-based programming language, but nothing existed for me to use, so I decided to create my own. Fitting such a general tool into a well-defined framework is challenging. The main reason is that graphs act as structures that can be traversed based on some underlying algorithm. This traversal is unclear initially, as you can traverse a graph in many ways. The idea with Automa is to create a language that can encapsulate graph-based programs using a simple and efficient fundamental axiom. I can make all of my programs with Automa, creating graphs at will and executing them to my desires. 

This is for me primarily, lol, my little world :)

## Key Features  
- **Graph-Based Computation**: Every computation is modeled as a graph traversal.  
- **Memory-Driven Logic**: Operations manipulate memory structures, which graphs process during execution.  
- **Deterministic and Nondeterministic Support**: Explore multiple parallel paths for nondeterministic computations.  
- **Immutable Graphs**: Graphs cannot be modified after creation, ensuring a consistent and predictable execution model.  
- **Minimal Constructs**: No loops, conditionals, or procedures—just transitions, nodes, and memory.  
- **Memory Rollback**: Memory is only set **after** an accept state has been reached and a path has been completed,
  ensuring that only Accepted computations make persistent changes to memory. 

## Graph States  
Each graph operates within one of the following states:  
1. **Execution State**: Actively traversing nodes and transitions.  
2. **Reject State**: The graph rejects the current computation.  
3. **Accept State**: The graph completes and accepts the computation.  
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
  - Core primitive types: num, characters.
  - Full IO setup
  - A working garbage collection(painful)

- **Future Endeavours**:  
  - Optimizations for memory and graph traversal.
  - Dynamic graph creation(very excited about this!!!!)
  - Graph inheritance(kinda cool)
  - Standard Library Creation
  - Robots Testing Frameworks
  - Garbage Collector

---

## Contributing  
Automa is an open-source project. Contributions are welcome! Feel free to submit a pull request if you have ideas or improvements.  

---

## License  
Automa is licensed under the [MIT License](LICENSE).  

Happy graphing! 🎉  

