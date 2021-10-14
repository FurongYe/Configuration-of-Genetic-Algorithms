/// \file crossover.hpp
/// \brief Header file for class Crossover.
///
/// It contains functions of crossover operators.
/// 
/// \author Furong Ye
/// \date 2020-07-02
#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

#include "common.h"

enum crossover_operator {
  UNIFORMCROSSOVER = 1,
  ONEPOINTCROSSOVER = 2,
  TWOPOINTCROSSOVER = 3
};

class Crossover {
public:
  Crossover(){}
  ~Crossover() {}
  Crossover (const Crossover&) = delete;
  Crossover &operator = (const Crossover&) = delete;

  void DoCrossover(vector<int> &y, const vector<int> &x1, const vector<int> &x2);

  void UniformCrossover(vector<int> &y, const vector<int> &x1, const vector<int> &x2);
  void OnePointCrossover(vector<int> &y, const vector<int> &x1, const vector<int> &x2);
  void TwoPointCrossover(vector<int> &y, const vector<int> &x1, const vector<int> &x2);

  void set_crossover_operator(const int c);
  void set_crossover_operator(string c);
  void set_p_u(const double p_u);

  int get_crossover_operator() const;
  double get_p_u() const;

  vector<int> c_flipped_index;

private:
  int crossover_operator_; /// < a flag for operator to be used for crossover
  double p_u_; /// < probability that a bit to be replaced by the bit of the other parent in uniform crossover
};

#endif // _CROSSOVER_H_
