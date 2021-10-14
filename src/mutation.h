/// \file crossover.hpp
/// \brief Header file for class Mutation.
///
/// It contains functions of mutation operators.
/// 
/// \author Furong Ye
/// \date 2020-07-02

#ifndef _MUTATION_H_
#define _MUTATION_H_

#include "common.h"

enum mutation_operator {
  STATICSAMPLE = 1,
  BINOMIALSAMPLE = 2,
  NORMALSAMPLE = 3,
  POWERLAWSAMPLE = 4
};

class Mutation {
public:
  Mutation(){}
  ~Mutation() {}
  Mutation(const Mutation&) = delete;
  Mutation &operator = (const Mutation&) = delete;

  void DoMutation(vector<int> &y);
  
  void Flip(vector<int> &y, const int l);
  int SampleL(const int N);
  int SampleBinomial(const double p, const int n);
  int SampleConditionalBinomial(const double p, const int n);
  int SampleNormal(double mu, double sigma);
  int SampleConditionalNormal(double mu, double sigma, int upperbound);
  int SampleLogNormal(double mu, double sigma);
  int SampleConditionalLogNormal(double mu, double sigma, int upperbound);
  int SampleFromDistribution(const std::vector<double> &distribution);
  void PowerLawDistribution(int N);

  void set_mutation_operator(const int m);
  void set_mutation_operator(string m);
  void set_l(const int l);
  void set_mutation_rate(const double mutation_rate);
  void set_r_n(const double r_n);
  void set_sigma_n(const double sigma_n);
  void set_beta_f(const double beta_f);

  int get_mutation_operator() const;
  int get_l() const;
  double get_mutation_rate() const;
  double get_r_n() const;
  double get_sigma_n() const;
  double get_beta_f() const;

  vector <int> m_flipped_index;

private:
  std::vector<double> power_law_distribution_;

  int mutation_operator_; /// < a flag for operator to be used for mutation
  int l_; /// < a static mutation strength
  double mutation_rate_; /// < mutation rate for standard bit mutation
  double r_n_; /// < mean value for normalized bit mutation
  double sigma_n_; /// < sd for normalized bit mutation
  double beta_f_; /// < beta for fast mutation
};

#endif // _MUTATION_H_
