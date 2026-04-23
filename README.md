# Gameplay AI Systems
A collection of gameplay AI systems developed during my studies at The Game Assembly.

---
## Grid Pathfinding (A* Implementation in C++)

A grid-based pathfinding system using the A* algorithm with Manhattan distance heuristics, implemented in C++.

### Features
- A* pathfinding algorithm using open and closed lists
- G-cost and H-cost path evaluation
- Heuristic cost function (Manhattan distance)
- Parent-based path reconstruction
- Grid-based node traversal system

### Technical Notes
- Uses Manhattan distance heuristic (10/14 cost system for diagonal costs)
- Linear search used for open list selection (priority queue not implemented for simplicity)
- shared_ptr used for safety in a school project context (raw pointers or indexed references would typically be used in production)

---
## AI Director (Dynamic Ecosystem System)

A real-time gameplay AI system that simulates and maintains balance between predator and prey populations using rule based decision making and trend analysis.

The system acts as a lightweight **AI Director**, adjusting the game world dynamically based on populations.

### Features
- Periodic world sampling (entity counting system)
- Population tracking for prey and predators
- Trend analysis (growth / decline detection over time)
- Rule-based state machine:
  - Balance
  - Increase Predator Pressure
  - Decrease Predator Pressure
- Dynamic prey respawn system with adaptive cooldown
- Real-time debug visualization using ImGui

### Technical Overview
- Uses time-based update loops (sampling + evaluation phases)
- Separates system into:
  - `CountUnits()` → gathers world state.
  - `EvaluateState()` → determines system behavior.
  - `Update()` → drives timing and execution.
- Simple state machine controlling ecosystem balance.

---
## Math Library

A lightweight template based math library written in C++ for development used. The goal was simplicity , readability and easy integration into the school engine code.

### Notes
- Header only template implementation
---
