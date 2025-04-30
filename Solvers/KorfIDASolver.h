#ifndef KORFIDASOLVER_H
#define KORFIDASOLVER_H

#include <bits/stdc++.h>

#include "../Models/RubiksCube.h"
#include "../PatternDatabases/CornerPatternDatabase.h"
#include "../PatternDatabases/PatternDatabase.h"

template <typename T, typename H>
class KorfIDASolver {
 private:
  vector<PatternDatabase*> patternDatabases;
  T cube;

  // Method to compute the heuristic value using pattern databases
  uint8_t computeHeuristic(const RubiksCube& cube) const {
    uint8_t maxH = 0;
    // Use the maximum value from all pattern databases as our heuristic
    for (const auto& patternDb : patternDatabases) {
      uint8_t h = patternDb->getNumMoves(cube);
      maxH = std::max(maxH, h);
    }
    return maxH;
  }

  // Helper to get a unique state representation for a cube
  vector<int> getStateVector(const RubiksCube& cube) const {
    vector<int> state;
    for (int face = 0; face < 6; face++) {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          state.push_back(static_cast<int>(
              cube.getColor(static_cast<RubiksCube::FACE>(face), i, j)));
        }
      }
    }
    return state;
  }

  // IDA* search: returns solution if found within bound, otherwise returns cost
  // for next iteration
  vector<RubiksCube::MOVE> search(const T& cube, uint8_t bound, uint8_t g,
                                  vector<RubiksCube::MOVE>& moves,
                                  unordered_set<vector<int>, H>& visited) {
    // Create a unique representation for visited check
    vector<int> state = getStateVector(cube);

    // If we've visited this state before, skip it
    if (visited.find(state) != visited.end()) {
      return {};
    }
    visited.insert(state);

    // Compute the heuristic value
    uint8_t h = computeHeuristic(cube);
    uint8_t f = g + h;

    // If the estimated cost exceeds the bound, return a special move to
    // indicate the cost Use a special value (e.g., 100 + f) to ensure it
    // doesn't conflict with actual moves
    if (f > bound) {
      // Create a special move with a value that won't be confused with regular
      // moves The actual moves are 0-17, so 100+f is safely outside that range
      return {static_cast<RubiksCube::MOVE>(100 + f)};
    }

    // If we found the solution, return the moves
    if (cube.isSolved()) {
      return moves;
    }

    uint8_t minCost = 255;  // Initialize to a large value

    // Try each possible move
    for (int moveInt = 0; moveInt < 18; ++moveInt) {
      RubiksCube::MOVE move = static_cast<RubiksCube::MOVE>(moveInt);

      // Skip redundant moves (e.g., applying F then F' is useless)
      if (!moves.empty()) {
        RubiksCube::MOVE lastMove = moves.back();
        int lastMoveInt = static_cast<int>(lastMove);

        // Skip if it's the inverse of the last move
        if (moveInt / 3 == lastMoveInt / 3) {
          // Same face as previous move
          if ((moveInt % 3) + (lastMoveInt % 3) == 2) {
            // One is clockwise, the other is counterclockwise
            continue;
          }
        }
      }

      // Create a copy of the cube for this move
      T nextCube = cube;

      // Apply the move
      nextCube.move(move);

      // Add the move to the sequence
      moves.push_back(move);

      // Recursively search
      auto result = search(nextCube, bound, g + 1, moves, visited);

      // If the result is a solution, return it
      if (!result.empty()) {
        int moveValue = static_cast<int>(result[0]);
        if (moveValue < 100) {
          // It's a real move sequence (solution)
          return result;
        }
        // Otherwise, update the minimum cost (subtracting 100 to get the actual
        // cost)
        minCost = std::min(minCost, static_cast<uint8_t>(moveValue - 100));
      }

      // Remove the move from the sequence
      moves.pop_back();
    }

    // Remove from visited to allow exploration in later iterations with higher
    // bounds
    visited.erase(state);

    // Return the minimum cost as a sentinel with our special encoding
    return {static_cast<RubiksCube::MOVE>(100 + minCost)};
  }

 public:
  // Constructor
  KorfIDASolver(const T& _cube) : cube(_cube) {}

  // Method to add a pattern database
  void addPatternDatabase(PatternDatabase* patternDb) {
    patternDatabases.push_back(patternDb);
  }

  // Method to solve the cube
  vector<RubiksCube::MOVE> solve() {
    if (cube.isSolved()) {
      return {};
    }

    // Start with the heuristic value as the initial bound
    uint8_t bound = computeHeuristic(cube);
    cout << "Initial bound: " << (int)bound << endl;

    while (bound < 30) {  // Set a reasonable upper limit
      cout << "Searching with bound: " << (int)bound << endl;
      vector<RubiksCube::MOVE> moves;
      unordered_set<vector<int>, H> visited;

      auto result = search(cube, bound, 0, moves, visited);

      // If solution found, return the moves
      if (!result.empty()) {
        int moveValue = static_cast<int>(result[0]);
        // Check if this is a solution or a cost indicator (values >= 100 are
        // costs)
        if (moveValue < 100) {
          return result;
        }

        // Extract the actual bound from the special move value (subtract 100)
        bound = moveValue - 100;
      } else {
        // No solution exists (should not happen for valid Rubik's cube)
        return {};
      }
    }

    // If the bound exceeded the upper limit, return an empty vector
    return {};
  }
};

// Specializations for hash functions to work with vectors of ints
template <>
struct std::hash<vector<int>> {
  size_t operator()(const vector<int>& v) const {
    size_t hash = v.size();
    for (auto i : v) {
      hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
  }
};

#endif  // KORFIDASOLVER_H