#include <chrono>

#include "Models/RubiksCube1dArray.cpp"
#include "Models/RubiksCube3dArray.cpp"
#include "Models/RubiksCubeBitBoard.cpp"
#include "PatternDatabases/CornerPatternDatabase.h"
#include "Solvers/BFSSolver.h"
#include "Solvers/DFSSolver.h"
#include "Solvers/IDDFSSolver.h"
#include "Solvers/KorfIDASolver.h"
#include "iostream"
#include "userConfig.h"
#include "vector"

using namespace std;

// Simple hash for vectors
struct VectorHash {
  size_t operator()(const vector<int>& v) const {
    size_t hash = v.size();
    for (auto i : v) {
      hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
  }
};

int main() {
  UserConfig userConfig = getUserInputs();

  cout << "\n--- Your Selection ---\n";
  cout << "Model Type: ";
  switch (userConfig.modelType) {
    case ModelType::OneDArray:
      cout << "RubiksCube1DArray\n";
      break;
    case ModelType::ThreeDArray:
      cout << "RubiksCube3DArray\n";
      break;
    case ModelType::BitBoard:
      cout << "RubiksCubeBitBoard\n";
      break;
  }

  cout << "Shuffle Moves: " << userConfig.shuffleMoves << "\n";

  cout << "Solving Algorithm: ";
  switch (userConfig.solveAlgorithm) {
    case SolveAlgorithm::BFS:
      cout << "BFS\n";
      break;
    case SolveAlgorithm::DFS:
      cout << "DFS\n";
      break;
    case SolveAlgorithm::IDDFS:
      cout << "IDDFS\n";
      break;
    case SolveAlgorithm::KORF_IDA:
      cout << "Korf IDA* (with Pattern Database)\n";
      break;
  }

  switch (userConfig.modelType) {
    case ModelType::OneDArray: {
      RubiksCube1dArray cube;
      cube.print();

      vector<RubiksCube::MOVE> movesToShuffle =
          cube.randomShuffleCube(userConfig.shuffleMoves);
      cout << "Moves to shuffle: ";
      for (auto move : movesToShuffle) {
        cout << cube.getMove(move) << " ";
      }
      cout << endl;
      cube.print();

      cout << "Moves to solve: ";
      switch (userConfig.solveAlgorithm) {
        case SolveAlgorithm::BFS: {
          BFSSolver<RubiksCube1dArray, Hash1d> bfsSolver(cube);
          vector<RubiksCube::MOVE> movesToSolve = bfsSolver.solve();
          for (auto move : movesToSolve) {
            cout << cube.getMove(move) << " ";
          }
          cout << endl;
        } break;
        case SolveAlgorithm::DFS: {
          DFSSolver<RubiksCube1dArray, Hash1d> dfsSolver(cube);
          vector<RubiksCube::MOVE> movesToSolve = dfsSolver.solve();
          for (auto move : movesToSolve) {
            cout << cube.getMove(move) << " ";
          }
          cout << endl;
        } break;
        case SolveAlgorithm::IDDFS: {
          IDDFSSolver<RubiksCube1dArray, Hash1d> iddfsSolver(cube);
          vector<RubiksCube::MOVE> movesToSolve = iddfsSolver.solve();
          for (auto move : movesToSolve) {
            cout << cube.getMove(move) << " ";
          }
          cout << endl;
        } break;
        case SolveAlgorithm::KORF_IDA: {
          auto start = chrono::high_resolution_clock::now();

          // Load the corner pattern database
          cout << "Loading corner pattern database..." << endl;
          CornerPatternDatabase cornerDb;
          if (cornerDb.fromFile("corner_pattern_database.bin")) {
            cout << "Corner database loaded successfully." << endl;
          } else {
            cout << "Failed to load corner database. Make sure it's been "
                    "created."
                 << endl;
            cout << "Run the CreateDatabase executable first." << endl;
            return 1;
          }

          // Initialize the Korf IDA* solver with our cube
          KorfIDASolver<RubiksCube1dArray, VectorHash> korfSolver(cube);

          // Add the pattern database to the solver
          korfSolver.addPatternDatabase(&cornerDb);

          // Solve the cube
          vector<RubiksCube::MOVE> movesToSolve = korfSolver.solve();

          auto end = chrono::high_resolution_clock::now();
          chrono::duration<double> duration = end - start;

          // Output the solution
          cout << "Solution found in " << duration.count() << " seconds."
               << endl;
          cout << "Solution length: " << movesToSolve.size() << " moves"
               << endl;
          for (auto move : movesToSolve) {
            cout << cube.getMove(move) << " ";
          }
          cout << endl;
        } break;
      }
      break;
    }
    case ModelType::ThreeDArray: {
      RubiksCube3dArray cube;
      cube.print();

      vector<RubiksCube::MOVE> movesToShuffle =
          cube.randomShuffleCube(userConfig.shuffleMoves);
      cout << "Moves to shuffle: ";
      for (auto move : movesToShuffle) {
        cout << cube.getMove(move) << " ";
      }
      cout << endl;
      cube.print();

      cout << "Moves to solve: ";
      switch (userConfig.solveAlgorithm) {
        case SolveAlgorithm::BFS: {
          BFSSolver<RubiksCube3dArray, Hash3d> bfsSolver(cube);
          vector<RubiksCube::MOVE> movesToSolve = bfsSolver.solve();
          for (auto move : movesToSolve) {
            cout << cube.getMove(move) << " ";
          }
          cout << endl;
        } break;
        case SolveAlgorithm::DFS: {
          DFSSolver<RubiksCube3dArray, Hash3d> dfsSolver(cube);
          vector<RubiksCube::MOVE> movesToSolve = dfsSolver.solve();
          for (auto move : movesToSolve) {
            cout << cube.getMove(move) << " ";
          }
          cout << endl;
        } break;
        case SolveAlgorithm::IDDFS: {
          IDDFSSolver<RubiksCube3dArray, Hash3d> iddfsSolver(cube);
          vector<RubiksCube::MOVE> movesToSolve = iddfsSolver.solve();
          for (auto move : movesToSolve) {
            cout << cube.getMove(move) << " ";
          }
          cout << endl;
        } break;
        case SolveAlgorithm::KORF_IDA: {
          auto start = chrono::high_resolution_clock::now();

          // Load the corner pattern database
          cout << "Loading corner pattern database..." << endl;
          CornerPatternDatabase cornerDb;
          if (cornerDb.fromFile("corner_pattern_database.bin")) {
            cout << "Corner database loaded successfully." << endl;
          } else {
            cout << "Failed to load corner database. Make sure it's been "
                    "created."
                 << endl;
            cout << "Run the CreateDatabase executable first." << endl;
            return 1;
          }

          // Initialize the Korf IDA* solver with our cube
          KorfIDASolver<RubiksCube3dArray, VectorHash> korfSolver(cube);

          // Add the pattern database to the solver
          korfSolver.addPatternDatabase(&cornerDb);

          // Solve the cube
          vector<RubiksCube::MOVE> movesToSolve = korfSolver.solve();

          auto end = chrono::high_resolution_clock::now();
          chrono::duration<double> duration = end - start;

          // Output the solution
          cout << "Solution found in " << duration.count() << " seconds."
               << endl;
          cout << "Solution length: " << movesToSolve.size() << " moves"
               << endl;
          for (auto move : movesToSolve) {
            cout << cube.getMove(move) << " ";
          }
          cout << endl;
        } break;
      }
      break;
    }
    case ModelType::BitBoard: {
      RubiksCubeBitBoard cube;
      cube.print();

      vector<RubiksCube::MOVE> movesToShuffle =
          cube.randomShuffleCube(userConfig.shuffleMoves);
      cout << "Moves to shuffle: ";
      for (auto move : movesToShuffle) {
        cout << cube.getMove(move) << " ";
      }
      cout << endl;
      cube.print();

      cout << "Moves to solve: ";
      switch (userConfig.solveAlgorithm) {
        case SolveAlgorithm::BFS: {
          BFSSolver<RubiksCubeBitBoard, HashBitBoard> bfsSolver(cube);
          vector<RubiksCube::MOVE> movesToSolve = bfsSolver.solve();
          for (auto move : movesToSolve) {
            cout << cube.getMove(move) << " ";
          }
          cout << endl;
        } break;
        case SolveAlgorithm::DFS: {
          DFSSolver<RubiksCubeBitBoard, HashBitBoard> dfsSolver(cube);
          vector<RubiksCube::MOVE> movesToSolve = dfsSolver.solve();
          for (auto move : movesToSolve) {
            cout << cube.getMove(move) << " ";
          }
          cout << endl;
        } break;
        case SolveAlgorithm::IDDFS: {
          IDDFSSolver<RubiksCubeBitBoard, HashBitBoard> iddfsSolver(cube);
          vector<RubiksCube::MOVE> movesToSolve = iddfsSolver.solve();
          for (auto move : movesToSolve) {
            cout << cube.getMove(move) << " ";
          }
          cout << endl;
        } break;
        case SolveAlgorithm::KORF_IDA: {
          auto start = chrono::high_resolution_clock::now();

          // Load the corner pattern database
          cout << "Loading corner pattern database..." << endl;
          CornerPatternDatabase cornerDb;
          if (cornerDb.fromFile("corner_pattern_database.bin")) {
            cout << "Corner database loaded successfully." << endl;
          } else {
            cout << "Failed to load corner database. Make sure it's been "
                    "created."
                 << endl;
            cout << "Run the CreateDatabase executable first." << endl;
            return 1;
          }

          // Initialize the Korf IDA* solver with our cube
          KorfIDASolver<RubiksCubeBitBoard, VectorHash> korfSolver(cube);

          // Add the pattern database to the solver
          korfSolver.addPatternDatabase(&cornerDb);

          // Solve the cube
          vector<RubiksCube::MOVE> movesToSolve = korfSolver.solve();

          auto end = chrono::high_resolution_clock::now();
          chrono::duration<double> duration = end - start;

          // Output the solution
          cout << "Solution found in " << duration.count() << " seconds."
               << endl;
          cout << "Solution length: " << movesToSolve.size() << " moves"
               << endl;
          for (auto move : movesToSolve) {
            cout << cube.getMove(move) << " ";
          }
          cout << endl;
        } break;
      }
      break;
    }
  }
}
