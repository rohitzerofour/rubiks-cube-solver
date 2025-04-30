cmake_minimum_required(VERSION 3.10)

project(RubiksCubeSolver VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCE_FILES
  main.cpp
  userConfig.h
  userConfig.cpp
  Models/RubiksCube.h
  Models/RubiksCube.cpp
  Models/RubiksCube3dArray.cpp
  Models/RubiksCube1dArray.cpp
  Models/RubiksCubeBitBoard.cpp
  Solvers/BFSSolver.h
  Solvers/DFSSolver.h
  Solvers/IDDFSSolver.h
  Solvers/KorfIDASolver.h
  PatternDatabases/math.h
  PatternDatabases/math.cpp
  PatternDatabases/NibbleArray.h
  PatternDatabases/NibbleArray.cpp
  PatternDatabases/PermutationIndexer.h
  PatternDatabases/PatternDatabase.h
  PatternDatabases/PatternDatabase.cpp
  PatternDatabases/CornerPatternDatabase.h
  PatternDatabases/CornerPatternDatabase.cpp
  PatternDatabases/CornerDbMaker.h
  PatternDatabases/CornerDbMaker.cpp
)

add_executable(RubiksCubeSolver ${SOURCE_FILES})

# Add the database creator as a separate executable
set(DB_CREATOR_SOURCES
  create_database.cpp
  Models/RubiksCube.h
  Models/RubiksCube.cpp
  Models/RubiksCubeBitBoard.cpp
  PatternDatabases/math.h
  PatternDatabases/math.cpp
  PatternDatabases/NibbleArray.h
  PatternDatabases/NibbleArray.cpp
  PatternDatabases/PermutationIndexer.h
  PatternDatabases/PatternDatabase.h
  PatternDatabases/PatternDatabase.cpp
  PatternDatabases/CornerPatternDatabase.h
  PatternDatabases/CornerPatternDatabase.cpp
  PatternDatabases/CornerDbMaker.h
  PatternDatabases/CornerDbMaker.cpp
)

add_executable(CreateDatabase ${DB_CREATOR_SOURCES})