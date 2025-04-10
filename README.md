# Automa  
**Automa - A Graph-Based Programming Language**  

Automa is a programming language where all computation revolves around graphs. The language represents calculations in one of three distinct states: **accepted**, **rejected**, or **pending**. Automa achieves this by representing all computations as graph traversals combined with memory operations. Given a particular graph and input memory, the memory will either be transformed by the computation (i.e., the calculation is accepted) or rejected. 

At its core, every program in Automa is a **graph** consisting of nodes and transitions. Transitions define paths between nodes and are represented as tuples of **conditions** and **operations**:  
- **Conditions**: Evaluate to `true` or `false` to determine if a transition is valid.  
- **Operations**: Act on memory, modifying or interacting with stored data.  

Automa supports deterministic and (soon-to-be fully implemented) **nondeterministic automata**, allowing multiple paths to be traversed simultaneously in graphs with multiple valid transitions.  

---

## Philosophy  

Automa derives its foundation from four principles: strong isolated and decentralized execution, the theory of finite state automata, and computation as structure.

### Finite State Automata Theory  

Every computation is described by a path traversing a graph that represents a finite state machine. A computation contains two key parts: the algorithm and storage. The algorithm is represented by transitions between the states of the finite state machine, and these transitions can act on memory. The states represent discrete fixtures in that algorithm, and division across execution represents where you are in your computation. Additionally, like in finite state automata theory, only accepted paths are important—in other words, ***the effects of a computation are not persistent until we accept the computation***.  

The path encapsulates the universe of computations—specifically the variables, state, time, etc. A centralized operator handles these paths but can run in a decentralized manner, each path executing independently.  

### Strong Isolated and Decentralized Execution

Paths are isolated from one another; they cannot access the same memory. In the case of nondeterministic exploration, a new sprouted path represents an entirely new "universe" of computation—an alternate path for how the calculation could have gone. A deep copy of the inputs and current graph state is required. While this might be computationally expensive initially, future optimizations will include copy-on-write techniques and methods to utilize more lightweight nondeterministic paths. This approach enables thousands of nondeterministic paths to run efficiently without concerns about parallel programming issues. Additionally, paths can execute on different machines in parallel, with the operator coordinating between them.  

### Computation as Structure  

Automa views algorithms structurally rather than as a set of instructions. Computation is treated not as a series of commands, but as a structure that is traversed. This perspective enables different optimization strategies and analysis techniques that may not be apparent in traditional programming paradigms.

---

## Personal Note

I've always wanted a graph-based programming language, but finding nothing suitable, I decided to create Automa. Creating a language that can properly represent graph-based programs with simple and efficient fundamentals has been challenging but rewarding. 

As a machine learning enthusiast, I also wanted to develop a language optimized for ML computation—one that enables safe, robust, and efficient programs for both research and production environments.

---

## Key Features  
- **Graph-Based Computation**: Every computation is modeled as a graph traversal.  
- **Memory-Driven Logic**: Operations manipulate memory structures, which graphs process during execution.  
- **Deterministic and Nondeterministic Support**: Explore multiple parallel paths for nondeterministic computations.  
- **Immutable Graphs**: Graphs cannot be modified after creation, ensuring a consistent and predictable execution model.  
- **Minimal Constructs**: No loops, conditionals, or procedures—just transitions, nodes, and memory.  

---

## Graph States  

Each graph operates within one of the following states:  
1. **Execution State**: Actively traversing nodes and transitions.  
2. **Reject State**: The graph rejects the current computation.  
3. **Accept State**: The graph completes and accepts the computation.  
4. **Void State**: The graph is idle or inactive.  

Graphs may also be **non-halting**, enabling infinitely running computations where appropriate.  

---

## Roadmap  

### Mile 1 (1 Year) – Version 1 Goals  
1. **Traversal Modes with Rollback** (for both deterministic and nondeterministic execution)  
2. **Num Primitive Functionality** – Implementation of arbitrary number primitives  
3. **IO Operations**  
4. **File Operations**  

### Mile 2 (2 Years)  
1. **Modules Library**  
2. **Type System Implementation**
3. **C++ API for Development**  
4. **Tensor Primitive**  
5. **Rigorous Testing Framework**  

### Mile 3 (2–3 Years)  
1. **Meta-Programming**  
2. **Graph Polymorphism Functionality**  
3. **Unified Environment Interaction Framework** (Sockets, files, etc.)  

---

## Future Goals  

For Automa to function as an accelerated programming language, the logical next steps following the roadmap will be:  
1. **GPU Integration**  
2. **FPGA Integration**  

The ultimate goal is to create a language that is accelerated naturally by available hardware, abstracting away the complexity of hardware acceleration from the developer.

This project is estimated to take approximately 5 years to complete. Contributors are welcome and would significantly help accelerate development.

**Contact:** liyulg0@gamil.com
