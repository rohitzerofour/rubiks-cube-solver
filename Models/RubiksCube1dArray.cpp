#include "RubiksCube.h"

class RubiksCube1dArray : public RubiksCube {
 private:
  static inline int getIndex(int ind, int row, int col) {
    return (ind * 9) + (row * 3) + col;
  }

  void rotateFace(int ind) {
    static const int rotateClockwise[9] = {6, 3, 0, 7, 4, 1, 8, 5, 2};

    char temp[9] = {};

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        temp[i * 3 + j] = cube[getIndex(ind, i, j)];
      }
    }

    for (int i = 0; i < 9; i++) {
      int oldPos = rotateClockwise[i];
      int row = i / 3;
      int col = i % 3;
      cube[getIndex(ind, row, col)] = temp[oldPos];
    }
  }

 public:
  char cube[54] = {};

  RubiksCube1dArray() {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          cube[getIndex(i, j, k)] = getColorLetter(static_cast<COLOR>(i));
        }
      }
    }
  }

  COLOR getColor(FACE face, unsigned int row, unsigned int col) const override {
    char color = cube[getIndex(face, row, col)];
    switch (color) {
      case 'G':
        return GREEN;
      case 'R':
        return RED;
      case 'W':
        return WHITE;
      case 'O':
        return ORANGE;
      case 'Y':
        return YELLOW;
      case 'B':
        return BLUE;
    }
    return WHITE;  // Default case, should not happen
  }

  bool isSolved() const override {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          if (cube[getIndex(i, j, k)] != getColorLetter(static_cast<COLOR>(i)))
            return false;
        }
      }
    }
    return true;
  }

  RubiksCube &u() override {
    this->rotateFace(0);

    char temp[3] = {};
    for (int i = 0; i < 3; i++) {
      temp[i] = cube[getIndex(4, 0, 2 - i)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(4, 0, 2 - i)] = cube[getIndex(1, 0, 2 - i)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(1, 0, 2 - i)] = cube[getIndex(2, 0, 2 - i)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(2, 0, 2 - i)] = cube[getIndex(3, 0, 2 - i)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(3, 0, 2 - i)] = temp[i];
    }
    return *this;
  }

  RubiksCube &uPrime() override { return this->u().u().u(); }

  RubiksCube &u2() override { return this->u().u(); }

  RubiksCube &l() override {
    this->rotateFace(1);

    char temp[3] = {};
    for (int i = 0; i < 3; i++) {
      temp[i] = cube[getIndex(0, i, 0)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(0, i, 0)] = cube[getIndex(4, 2 - i, 2)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(4, 2 - i, 2)] = cube[getIndex(5, i, 0)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(5, i, 0)] = cube[getIndex(2, i, 0)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(2, i, 0)] = temp[i];
    }
    return *this;
  }

  RubiksCube &lPrime() override { return this->l().l().l(); }

  RubiksCube &l2() override { return this->l().l(); }

  RubiksCube &f() override {
    this->rotateFace(2);

    char temp[3] = {};
    for (int i = 0; i < 3; i++) {
      temp[i] = cube[getIndex(0, 2, i)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(0, 2, i)] = cube[getIndex(1, 2 - i, 2)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(1, 2 - i, 2)] = cube[getIndex(5, 0, 2 - i)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(5, 0, 2 - i)] = cube[getIndex(3, i, 0)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(3, i, 0)] = temp[i];
    }
    return *this;
  }

  RubiksCube &fPrime() override { return this->f().f().f(); }

  RubiksCube &f2() override { return this->f().f(); }

  RubiksCube &r() override {
    this->rotateFace(3);

    char temp[3] = {};
    for (int i = 0; i < 3; i++) {
      temp[i] = cube[getIndex(0, 2 - i, 2)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(0, 2 - i, 2)] = cube[getIndex(2, 2 - i, 2)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(2, 2 - i, 2)] = cube[getIndex(5, 2 - i, 2)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(5, 2 - i, 2)] = cube[getIndex(4, i, 0)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(4, i, 0)] = temp[i];
    }
    return *this;
  }

  RubiksCube &rPrime() override { return this->r().r().r(); }

  RubiksCube &r2() override { return this->r().r(); }

  RubiksCube &b() override {
    this->rotateFace(4);

    char temp[3] = {};
    for (int i = 0; i < 3; i++) {
      temp[i] = cube[getIndex(0, 0, 2 - i)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(0, 0, 2 - i)] = cube[getIndex(3, 2 - i, 2)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(3, 2 - i, 2)] = cube[getIndex(5, 2, i)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(5, 2, i)] = cube[getIndex(1, i, 0)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(1, i, 0)] = temp[i];
    }
    return *this;
  }

  RubiksCube &bPrime() override { return this->b().b().b(); }

  RubiksCube &b2() override { return this->b().b(); }

  RubiksCube &d() override {
    this->rotateFace(5);

    char temp[3] = {};
    for (int i = 0; i < 3; i++) {
      temp[i] = cube[getIndex(2, 2, i)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(2, 2, i)] = cube[getIndex(1, 2, i)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(1, 2, i)] = cube[getIndex(4, 2, i)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(4, 2, i)] = cube[getIndex(3, 2, i)];
    }
    for (int i = 0; i < 3; i++) {
      cube[getIndex(3, 2, i)] = temp[i];
    }
    return *this;
  }

  RubiksCube &dPrime() override { return this->d().d().d(); }

  RubiksCube &d2() override { return this->d().d(); }

  bool operator==(const RubiksCube1dArray &other) const {
    for (int i = 0; i < 54; i++) {
      if (cube[i] != other.cube[i]) return false;
    }
    return true;
  }

  RubiksCube1dArray &operator=(const RubiksCube1dArray &other) {
    for (int i = 0; i < 54; i++) {
      this->cube[i] = other.cube[i];
    }
    return *this;
  }
};

struct Hash1d {
  size_t operator()(const RubiksCube1dArray &r1) const {
    size_t hash = 0;
    for (int i = 0; i < 54; i++) {
      hash = hash * 31 + r1.cube[i];
    }
    return hash;
  }
};