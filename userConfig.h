#ifndef USERCONFIG_H
#define USERCONFIG_H

enum class ModelType { OneDArray, ThreeDArray, BitBoard };
enum class SolveAlgorithm { BFS, DFS, IDDFS, KORF_IDA };

struct UserConfig {
  ModelType modelType;
  int shuffleMoves;
  SolveAlgorithm solveAlgorithm;
};

UserConfig getUserInputs();

#endif
