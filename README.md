# Automa  
Automa - A Graph-Based Programming Language  

Automa is a programming language where all computation revolves around graphs. The idea is to create a programming language where calculation at any point is in 3 distinct states: accepted, rejected, or pending. Automa does this by representing all computations as graph traversals combined with some action on memory, so given a particular graph and input memory, the memory will either be transformed by the computation(i.e., the calculation is accepted) or rejected. 

At its core, every program in Automa is a **graph** consisting of nodes and transitions. Transitions define paths between nodes and are represented as tuples of **conditions** and **operations**:  
- **Conditions**: Evaluate to `true` or `false` to determine if a transition is valid. **Cannot** change the graph's memory, thus having no side effects.  
- **Operations**: Act on memory, modifying or interacting with stored data.  

Automa supports deterministic and (soon-to-be fully implemented) **nondeterministic automata**, allowing multiple paths to be traversed simultaneously in graphs with multiple valid transitions.  


## Philosophy 
The essential philosophy of Automa is a graph-based programming language focused on efficiency, speed, and certain computational guarantees. 
These guarantees are rollback and isolation.

What is Rollback in Automa? 
Given a graph G and input set S, and a path P that represents a traversal of G with input S, S is immutable, so it will never change within the graph execution. However, the program might still interact with the environment, leading to cases where rejected computations need to be rolled back. One of these cases is file IO when a file is written to, but the underlying computation is rejected, it is not sensical for the original write to remain persistent. Automa rolls back these changes, creating a system where, in failure, the states of the program are effectively rolled back.


Rollback implies another interesting outcome: environment interactions, i.e., file IO, etc., are committed, not automatically executed. Ensuring that the system is closed to an extent from the environment. 

What is Isolation in Automa? 
Each graph has two modes of possible traversal: deterministic and non-deterministic. In the case of non-deterministic travel, all paths, P, will maintain separate copies of the computation state; essentially, each path represents an alternate world of computation. Maintaining concurrency while keeping the memory safe.  

These two guarantees allow programs to be written with safety and robustness built into the programming language. These safety mechanisms are built-in, so the developer does not worry about them.

The targetted areas are order, machine learning, and distributed systems. The goal is to create a swift and efficient language for these purposes.

These are the priorities in order :
  All computation is graph-based
  Speed
  Simplicity
  Efficiency 


## Personal Motivations 
I have always wanted a graph-based programming language, but nothing existed for me to use, so I decided to create my own. Fitting such a general tool into a well-defined framework is challenging. The main reason is that graphs act as structures that can be traversed based on some underlying algorithm. This traversal is unclear initially, as you can traverse a graph in many ways. The idea with Automa is to create a language that can encapsulate graph-based programs using a simple and efficient fundamental axiom. I can make all of my programs with Automa, creating graphs at will and executing them to my desires. 

I am also an avid machine-learning enthusiast and have wanted to create my own language for machine-learning computation for a long time. I want to develop safe, robust, efficient programs for machine learning research and industry production. 

Why not combine these two into one? A language that is graph-based and also optimized for machine learning! 

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

**The first-ever hardware-accelerated programming language**

After each version, I will release and announce the changes. The whole project should take about 5 years. I will gladly accept any contributors, it would be great help, I want to accelerate the process!
Now, for some honesty. It will be **difficult**, at times challenging, to the verge of defeat, but I hope the pseudo-deterministic universe will allow us the opportunity to persevere. 
   
