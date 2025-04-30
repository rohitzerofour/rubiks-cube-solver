#include "userConfig.h"

#include <iostream>

UserConfig getUserInputs() {
  UserConfig config;
  int modelChoice, algoChoice;

  std::cout << "Select Model Type:\n"
            << "1. RubiksCube1DArray\n"
            << "2. RubiksCube3DArray\n"
            << "3. RubiksCubeBitBoard\n"
            << "Enter choice (1-3): ";
  std::cin >> modelChoice;

  switch (modelChoice) {
    case 1:
      config.modelType = ModelType::OneDArray;
      break;
    case 2:
      config.modelType = ModelType::ThreeDArray;
      break;
    case 3:
      config.modelType = ModelType::BitBoard;
      break;
    default:
      std::cout << "Invalid choice. Defaulting to RubiksCube3dArray.\n";
      config.modelType = ModelType::ThreeDArray;
  }

  std::cout << "\nEnter number of shuffle moves (e.g., 8): ";
  std::cin >> config.shuffleMoves;

  std::cout << "\nSelect Solving Algorithm:\n"
            << "1. BFS\n"
            << "2. DFS\n"
            << "3. IDDFS\n"
            << "4. Korf IDA* (with Pattern Database)\n"
            << "Enter choice (1-4): ";
  std::cin >> algoChoice;

  switch (algoChoice) {
    case 1:
      config.solveAlgorithm = SolveAlgorithm::BFS;
      break;
    case 2:
      config.solveAlgorithm = SolveAlgorithm::DFS;
      break;
    case 3:
      config.solveAlgorithm = SolveAlgorithm::IDDFS;
      break;
    case 4:
      config.solveAlgorithm = SolveAlgorithm::KORF_IDA;
      break;
    default:
      std::cout << "Invalid choice. Defaulting to BFS.\n";
      config.solveAlgorithm = SolveAlgorithm::BFS;
  }

  return config;
}
