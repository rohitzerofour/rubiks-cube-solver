#include "CornerDbMaker.h"

using namespace std;

CornerDbMaker::CornerDbMaker(string _fileName) { fileName = _fileName; }

CornerDbMaker::CornerDbMaker(string _fileName, uint8_t init_val) {
  fileName = _fileName;
  cornerDb = CornerPatternDatabase(init_val);
}

bool CornerDbMaker::bfsAndStore() {
  RubiksCubeBitBoard cube;
  queue<RubiksCubeBitBoard> q;
  q.push(cube);
  cornerDb.setNumMoves(cube, 0);
  int curr_depth = 0;
  while (!q.empty()) {
    int n = q.size();
    curr_depth++;
    if (curr_depth == 9) break;
    for (int counter = 0; counter < 9; counter++) {
      RubiksCubeBitBoard node = q.front();
      q.pop();
      for (int i = 0; i < 18; i++) {
        auto curr_move = RubiksCube::MOVE(i);
        node.move(curr_move);
        if ((int)cornerDb.getNumMoves(node) > curr_depth) {
          cornerDb.setNumMoves(node, curr_depth);
          q.push(node);
        }
        node.invert(curr_move);
      }
    }
  }
  cornerDb.toFile(fileName);

  return true;
}