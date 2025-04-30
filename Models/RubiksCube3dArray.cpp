#include "RubiksCube.h"

class RubiksCube3dArray : public RubiksCube {
 private:
  void rotateFace(int ind) {
    for (int layer = 0; layer < 1; layer++) {
      for (int i = layer; i < 2 - layer; i++) {
        char temp = cube[ind][layer][i];
        cube[ind][layer][i] = cube[ind][2 - i][layer];
        cube[ind][2 - i][layer] = cube[ind][2 - layer][2 - i];
        cube[ind][2 - layer][2 - i] = cube[ind][i][2 - layer];
        cube[ind][i][2 - layer] = temp;
      }
    }
  }

 public:
  char cube[6][3][3] = {};

  RubiksCube3dArray() {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          cube[i][j][k] = getColorLetter(COLOR(i));
        }
      }
    }
  }

  COLOR getColor(FACE face, unsigned int row, unsigned int col) const override {
    char color = cube[face][row][col];
    switch (color) {
      case 'B':
        return COLOR::BLUE;
      case 'R':
        return COLOR::RED;
      case 'G':
        return COLOR::GREEN;
      case 'O':
        return COLOR::ORANGE;
      case 'Y':
        return COLOR::YELLOW;
      default:
        return COLOR::WHITE;
    }
  }

  bool isSolved() const override {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          if (this->cube[i][j][k] != getColorLetter(COLOR(i))) return false;
        }
      }
    }
    return true;
  }

  RubiksCube &u() override {
    this->rotateFace(0);
    char temp[3];
    for (int i = 0; i < 3; i++) temp[i] = cube[1][0][i];
    for (int i = 1; i < 4; i++) {
      for (int j = 0; j < 3; j++) {
        cube[i][0][j] = cube[i + 1][0][j];
      }
    }
    for (int i = 0; i < 3; i++) cube[4][0][i] = temp[i];
    return *this;
  }

  RubiksCube &uPrime() override { return this->u().u().u(); }

  RubiksCube &u2() override { return this->u().u(); }

  RubiksCube &l() override {
    this->rotateFace(1);
    char temp[3];
    for (int i = 0; i < 3; i++) temp[i] = cube[4][2 - i][2];
    for (int i = 0; i < 3; i++) cube[4][i][2] = cube[5][i][0];
    for (int i = 0; i < 3; i++) cube[5][i][0] = cube[2][i][0];
    for (int i = 0; i < 3; i++) cube[2][i][0] = cube[0][i][0];
    for (int i = 0; i < 3; i++) cube[0][i][0] = temp[i];
    return *this;
  }

  RubiksCube &lPrime() override { return this->l().l().l(); }

  RubiksCube &l2() override { return this->l().l(); }

  RubiksCube &f() override {
    this->rotateFace(2);
    char temp[3];
    for (int i = 0; i < 3; i++) temp[i] = cube[1][2 - i][2];
    for (int i = 0; i < 3; i++) cube[1][i][2] = cube[5][0][2 - i];
    for (int i = 0; i < 3; i++) cube[5][0][i] = cube[3][2 - i][0];
    for (int i = 0; i < 3; i++) cube[3][i][0] = cube[0][2][i];
    for (int i = 0; i < 3; i++) cube[0][2][i] = temp[i];
    return *this;
  }

  RubiksCube &fPrime() override { return this->f().f().f(); }

  RubiksCube &f2() override { return this->f().f(); }

  RubiksCube &r() override {
    this->rotateFace(3);
    char temp[3];
    for (int i = 0; i < 3; i++) temp[i] = cube[0][i][2];
    for (int i = 0; i < 3; i++) cube[0][i][2] = cube[2][i][2];
    for (int i = 0; i < 3; i++) cube[2][i][2] = cube[5][i][2];
    for (int i = 0; i < 3; i++) cube[5][i][2] = cube[4][2 - i][0];
    for (int i = 0; i < 3; i++) cube[4][2 - i][0] = temp[i];
    return *this;
  }

  RubiksCube &rPrime() override { return this->r().r().r(); }

  RubiksCube &r2() override { return this->r().r(); }

  RubiksCube &b() override {
    this->rotateFace(4);
    char temp[3];
    for (int i = 0; i < 3; i++) temp[i] = cube[3][i][2];
    for (int i = 0; i < 3; i++) cube[3][i][2] = cube[5][0][i];
    for (int i = 0; i < 3; i++) cube[5][0][i] = cube[1][2 - i][0];
    for (int i = 0; i < 3; i++) cube[1][2 - i][0] = cube[0][0][i];
    for (int i = 0; i < 3; i++) cube[0][0][i] = temp[i];
    return *this;
  }

  RubiksCube &bPrime() override { return this->b().b().b(); }

  RubiksCube &b2() override { return this->b().b(); }

  RubiksCube &d() override {
    this->rotateFace(5);
    char temp[3];
    for (int i = 0; i < 3; i++) temp[i] = cube[4][2][i];
    for (int i = 0; i < 3; i++) cube[4][2][i] = cube[3][2][i];
    for (int i = 0; i < 3; i++) cube[3][2][i] = cube[2][2][i];
    for (int i = 0; i < 3; i++) cube[2][2][i] = cube[1][2][i];
    for (int i = 0; i < 3; i++) cube[1][2][i] = temp[i];
    return *this;
  }

  RubiksCube &dPrime() override { return this->d().d().d(); }

  RubiksCube &d2() override { return this->d().d(); }

  bool operator==(const RubiksCube3dArray &other) const {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          if (this->cube[i][j][k] != other.cube[i][j][k]) return false;
        }
      }
    }
    return true;
  }

  RubiksCube3dArray &operator=(const RubiksCube3dArray &other) {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          this->cube[i][j][k] = other.cube[i][j][k];
        }
      }
    }
    return *this;
  }
};

struct Hash3d {
  size_t operator()(const RubiksCube3dArray &r1) const {
    size_t hashValue = 0;
    size_t prime = 31;

    for (int i = 0; i < 6; ++i) {
      for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 3; ++k) {
          hashValue = hashValue * prime + r1.cube[i][j][k];
        }
      }
    }

    return hashValue;
  }
};
