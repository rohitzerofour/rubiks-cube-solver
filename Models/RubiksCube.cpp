#include "Models/RubiksCube.h"

char RubiksCube::getColorLetter(COLOR color) {
  switch (color) {
    case GREEN:
      return 'G';
    case RED:
      return 'R';
    case WHITE:
      return 'W';
    case ORANGE:
      return 'O';
    case YELLOW:
      return 'Y';
    case BLUE:
      return 'B';
    default:
      return '?';
  }
}

string RubiksCube::getMove(MOVE ind) {
  switch (ind) {
    case MOVE::L:
      return "L";
    case MOVE::LPRIME:
      return "L'";
    case MOVE::L2:
      return "L2";
    case MOVE::R:
      return "R";
    case MOVE::RPRIME:
      return "R'";
    case MOVE::R2:
      return "R2";
    case MOVE::U:
      return "U";
    case MOVE::UPRIME:
      return "U'";
    case MOVE::U2:
      return "U2";
    case MOVE::D:
      return "D";
    case MOVE::DPRIME:
      return "D'";
    case MOVE::D2:
      return "D2";
    case MOVE::F:
      return "F";
    case MOVE::FPRIME:
      return "F'";
    case MOVE::F2:
      return "F2";
    case MOVE::B:
      return "B";
    case MOVE::BPRIME:
      return "B'";
    case MOVE::B2:
      return "B2";
  }
  return "?";
}

RubiksCube &RubiksCube::move(MOVE ind) {
  switch (ind) {
    case MOVE::L:
      return this->l();
    case MOVE::LPRIME:
      return this->lPrime();
    case MOVE::L2:
      return this->l2();
    case MOVE::R:
      return this->r();
    case MOVE::RPRIME:
      return this->rPrime();
    case MOVE::R2:
      return this->r2();
    case MOVE::U:
      return this->u();
    case MOVE::UPRIME:
      return this->uPrime();
    case MOVE::U2:
      return this->u2();
    case MOVE::D:
      return this->d();
    case MOVE::DPRIME:
      return this->dPrime();
    case MOVE::D2:
      return this->d2();
    case MOVE::F:
      return this->f();
    case MOVE::FPRIME:
      return this->fPrime();
    case MOVE::F2:
      return this->f2();
    case MOVE::B:
      return this->b();
    case MOVE::BPRIME:
      return this->bPrime();
    case MOVE::B2:
      return this->b2();
  }
  return *this;
}

RubiksCube &RubiksCube::invert(MOVE ind) {
  switch (ind) {
    case MOVE::L:
      return this->lPrime();
    case MOVE::LPRIME:
      return this->l();
    case MOVE::L2:
      return this->l2();
    case MOVE::R:
      return this->rPrime();
    case MOVE::RPRIME:
      return this->r();
    case MOVE::R2:
      return this->r2();
    case MOVE::U:
      return this->uPrime();
    case MOVE::UPRIME:
      return this->u();
    case MOVE::U2:
      return this->u2();
    case MOVE::D:
      return this->dPrime();
    case MOVE::DPRIME:
      return this->d();
    case MOVE::D2:
      return this->d2();
    case MOVE::F:
      return this->fPrime();
    case MOVE::FPRIME:
      return this->f();
    case MOVE::F2:
      return this->f2();
    case MOVE::B:
      return this->bPrime();
    case MOVE::BPRIME:
      return this->b();
    case MOVE::B2:
      return this->b2();
  }
  return *this;
}

void RubiksCube::print() const {
  cout << endl << "Rubik's Cube:" << endl;
  cout << "-----------------" << endl;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 7; j++) cout << " ";
    for (int j = 0; j < 3; ++j) {
      cout << getColorLetter(getColor(FACE::UP, i, j)) << " ";
    }
    cout << endl;
  }
  cout << endl;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      cout << getColorLetter(getColor(FACE::LEFT, i, j)) << " ";
    }
    cout << " ";

    for (int j = 0; j < 3; ++j) {
      cout << getColorLetter(getColor(FACE::FRONT, i, j)) << " ";
    }
    cout << " ";

    for (int j = 0; j < 3; ++j) {
      cout << getColorLetter(getColor(FACE::RIGHT, i, j)) << " ";
    }
    cout << " ";

    for (int j = 0; j < 3; ++j) {
      cout << getColorLetter(getColor(FACE::BACK, i, j)) << " ";
    }
    cout << endl;
  }
  cout << endl;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 7; j++) cout << " ";
    for (int j = 0; j < 3; ++j) {
      cout << getColorLetter(getColor(FACE::DOWN, i, j)) << " ";
    }
    cout << endl;
  }
  cout << endl;
}

vector<RubiksCube::MOVE> RubiksCube::randomShuffleCube(unsigned int times) {
  vector<MOVE> moves;
  srand(time(0));
  for (unsigned int i = 0; i < times; ++i) {
    MOVE move = static_cast<MOVE>(rand() % 18);
    moves.push_back(move);
    this->move(move);
  }
  return moves;
}

string RubiksCube::getCornerColorString(uint8_t ind) const {
  string colorString = "";
  switch (ind) {
    case 0:
      colorString += getColorLetter(getColor(FACE::UP, 2, 2));
      colorString += getColorLetter(getColor(FACE::FRONT, 0, 2));
      colorString += getColorLetter(getColor(FACE::RIGHT, 0, 0));
      break;
    case 1:
      colorString += getColorLetter(getColor(FACE::UP, 2, 0));
      colorString += getColorLetter(getColor(FACE::FRONT, 0, 0));
      colorString += getColorLetter(getColor(FACE::LEFT, 0, 2));
      break;
    case 2:
      colorString += getColorLetter(getColor(FACE::UP, 0, 0));
      colorString += getColorLetter(getColor(FACE::BACK, 0, 2));
      colorString += getColorLetter(getColor(FACE::LEFT, 0, 0));
      break;
    case 3:
      colorString += getColorLetter(getColor(FACE::UP, 0, 2));
      colorString += getColorLetter(getColor(FACE::BACK, 0, 0));
      colorString += getColorLetter(getColor(FACE::RIGHT, 0, 2));
      break;
    case 4:
      colorString += getColorLetter(getColor(FACE::DOWN, 0, 2));
      colorString += getColorLetter(getColor(FACE::FRONT, 2, 2));
      colorString += getColorLetter(getColor(FACE::RIGHT, 2, 0));
      break;
    case 5:
      colorString += getColorLetter(getColor(FACE::DOWN, 0, 0));
      colorString += getColorLetter(getColor(FACE::FRONT, 2, 0));
      colorString += getColorLetter(getColor(FACE::LEFT, 2, 2));
      break;
    case 6:
      colorString += getColorLetter(getColor(FACE::DOWN, 2, 2));
      colorString += getColorLetter(getColor(FACE::BACK, 2, 0));
      colorString += getColorLetter(getColor(FACE::RIGHT, 2, 2));
      break;
    case 7:
      colorString += getColorLetter(getColor(FACE::DOWN, 2, 0));
      colorString += getColorLetter(getColor(FACE::BACK, 2, 2));
      colorString += getColorLetter(getColor(FACE::LEFT, 2, 0));
      break;
  }
  return colorString;
}

uint8_t RubiksCube::getCornerIndex(uint8_t ind) const {
  string corner = getCornerColorString(ind);

  uint8_t index = 0;
  for (auto c : corner) {
    if (c != 'W' && c != 'Y') continue;
    if (c == 'Y') {
      index |= (1 << 2);
    }
  }

  for (auto c : corner) {
    if (c != 'R' && c != 'O') continue;
    if (c == 'O') {
      index |= (1 << 1);
    }
  }

  for (auto c : corner) {
    if (c != 'G' && c != 'B') continue;
    if (c == 'G') {
      index |= (1 << 0);
    }
  }
  return index;
}

uint8_t RubiksCube::getCornerOrientation(uint8_t ind) const {
  string corner = getCornerColorString(ind);

  string actual_str = "";

  for (auto c : corner) {
    if (c != 'W' && c != 'Y') continue;
    actual_str += c;
  }

  if (corner[1] == actual_str[0]) {
    return 1;
  } else if (corner[2] == actual_str[0]) {
    return 2;
  } else {
    return 0;
  }
}