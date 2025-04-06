# Automa  
Automa - A Graph-Based Programming Language  

Automa is a programming language where all computation revolves around graphs. The idea is to create a programming language where calculation at any point is in 3 distinct states: accepted, rejected, or pending. Automa does this by representing all computations as graph traversals combined with some action on memory, so given a particular graph and input memory, the memory will either be transformed by the computation(i.e., the calculation is accepted) or rejected. 

At its core, every program in Automa is a **graph** consisting of nodes and transitions. Transitions define paths between nodes and are represented as tuples of **conditions** and **operations**:  
- **Conditions**: Evaluate to `true` or `false` to determine if a transition is valid.
- **Operations**: Act on memory, modifying or interacting with stored data.  

Automa supports deterministic and (soon-to-be fully implemented) **nondeterministic automata**, allowing multiple paths to be traversed simultaneously in graphs with multiple valid transitions.  


## Philosophy 
At its core, Automa derives its foundations from three principles: strong isolation, decentralized execution, and the theory of finite state Automata.  

### Finite State Automata Theory

Every computation is described by a path traversing a graph. This path traverses a graph representing some finite state machine.
The idea is that a computation contains two key parts: the algorithm and storage. The algorithm is represented by the transitions between the states of the finite state machine, and 
these transitions can act on memory. The states represent discreet fixtures in that algorithm, division across execution representing where you are in your computation.

The path encapsulates that universe of computations, specifically the variables, state, time, etc., Very similar to the idea of a processor with the OS. In the long run, the idea is to model the programming language partly using OS principles. A centralized operator handles these paths but can run in a decentralized manner, each path for itself.  

### Isolation 
Paths are isolated from one another; they cannot access the same memory; in the case of nondeterministic exploration, a new sprouted path essentially represents an entirely new 'universe' of computation, an alternate path for how the calculation could have gone. A deep copy of the inputs and current graph state is required. While this might be slow at first, the goal is to make it more effective using copy-on-write techniques and developing methods of programming that utilize more lightweight nondeterministic paths that, after sprouting, take up more memory. This way, you can generate thousands of non-deterministic paths and run them efficiently without worrying about parallel programming. Additionally, paths can run on different machines quickly. 

### Decentralized execution
Each path executes separately if parallel. The operator serves as a coordinator between the paths. 

## Personal Motivations 
I have always wanted a graph-based programming language, but nothing existed for me to use, so I decided to create my own. Fitting such a general tool into a well-defined framework is challenging. The main reason is that graphs act as structures that can be traversed based on some underlying algorithm. This traversal is unclear initially, as you can traverse a graph in many ways. The idea with Automa is to create a language that can encapsulate graph-based programs using a simple and efficient fundamental axiom. I can make all of my programs with Automa, creating graphs at will and executing them to my desires. 

I am also an avid machine-learning enthusiast. For a long time, I have wanted to create my own language for machine-learning computation. I want to develop safe, robust, and efficient programs for machine learning research and industry production. 

Why not combine these two into one? A language that is graph-based and also optimized for machine learning! 

This is for me primarily, lol, my little world :)

## Key Features  
- **Graph-Based Computation**: Every computation is modeled as a graph traversal.  
- **Memory-Driven Logic**: Operations manipulate memory structures, which graphs process during execution.  
- **Deterministic and Nondeterministic Support**: Explore multiple parallel paths for nondeterministic computations.  
- **Immutable Graphs**: Graphs cannot be modified after creation, ensuring a consistent and predictable execution model.  
- **Minimal Constructs**: No loops, conditionals, or procedures—just transitions, nodes, and memory.  

## Graph States  
Each graph operates within one of the following states:  
1. **Execution State**: Actively traversing nodes and transitions.  
2. **Reject State**: The graph rejects the current computation.  
3. **Accept State**: The graph completes and accepts the computation.  
4. **Void State**: The graph is idle or inactive.  

Graphs may also be **non-halting**, enabling infinitely running computations where appropriate.  

## Road Map 

  ### Mile 1 (1 Year)
  These are the goals for version 1 
  1. **Traversal Modes Work with rollback** for both deterministic and non-deterministic
  2. **Num primitive functionality** arbitrary number primitive operational for use
  3. **IO operations functioning**
  4. **File operations functioning**
      
  ### Mile 2 ( 2 Years)
  1. **Modules library**
  2. **Add Type System** very important for the future
  3. **C++ API for development**
  4. **Tensor(Kind of ...) primitive**
  5. **Rigorous testing framework**
  
  ### Mile 3 ( 2 year) 
  1. **Meta Programming**
  2. **Graph polymorphism basic functionality**
  3. **Unified Environment interaction framework(Sockets, files, etc)**

**Version 1 Release**

## Future Goals 
I want Automa to be an accelerated programming language, so the most logical next step, once these sections are done, is 
1. **GPU Integration**
2. **FPGA Integration**
The future goal of the language is to have natural speedups from working with external accelerators, the goal being to have a language that is accelerated naturally by your hardware. You won't have to worry about anything!

After each version, I will release and announce the changes. The whole project should take about 5 years. I will gladly accept any contributors, it would be great help, I want to accelerate the process!
Now, for some honesty. It will be **difficult**, at times challenging, to the verge of defeat, but I hope the pseudo-deterministic universe will allow us the opportunity to persevere. 
***Contact at liyulg0@gamil.com***
   
