#ifndef CORNERDBMAKER_H
#define CORNERDBMAKER_H

#include "../Models/RubiksCubeBitBoard.cpp"
#include "CornerPatternDatabase.h"

using namespace std;

class CornerDbMaker {
 private:
  string fileName;
  CornerPatternDatabase cornerDb;

 public:
  CornerDbMaker(string _fileName);
  CornerDbMaker(string _fileName, uint8_t init_val);

  bool bfsAndStore();
};

#endif  // CORNERDBMAKER_H