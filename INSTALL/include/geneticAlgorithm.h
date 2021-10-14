/// \file geneticAlgorithm.hpp
/// \brief Header file for class GeneticAlgorithm.
///
/// A configurable genetic algorithm.
/// 
/// \author Furong Ye
/// \date 2020-07-02

#ifndef _GENETICALGORITHM_H_
#define _GENETICALGORITHM_H_

#include "common.h"
#include "crossover.h"
#include "mutation.h"
#include "selection.h"


enum crossover_mutation_relation {
  IND = 1,
  OR = 0
};

class GeneticAlgorithm : public Crossover, public Mutation, public Selection {
public:
  GeneticAlgorithm() :
    mu_(1), 
    lambda_(1), 
    crossover_probability_(0),
    crossover_mutation_r_(0),
    evaluation_(0),
    generation_(0),
    evluation_budget_(10000),
    generation_budget_(10000),
    optimum_(numeric_limits<double>::max()),
    optimum_found_flag_(false) {}
  
  ~GeneticAlgorithm() {}
  GeneticAlgorithm(const GeneticAlgorithm&) = delete;
  GeneticAlgorithm &operator = (const GeneticAlgorithm&) = delete;

  /// \fn virtual AdaptiveStrategy()
  /// \brief A virtual function for adaptive methods.
  ///
  /// If you are about to implement a GA with adaptive paramters, you should implement the adaptive method in this function. This function will be revoked at the end of each iteration/generation.
  virtual void AdaptiveStrategy() {};
  
  /// \fn virtual Terminate()
  /// \brief Terminate condition of the genetic algorithm.
  ///
  /// You can set up terminate condition in this function. By default, the GA terminates when the best fitness value is found or the budget is used out.
  virtual bool Terminate();

  /// \fn DoGeneticAlgorithm()
  /// \brief Do function of the genetic algorithm.
  ///
  /// The order of processing functions is: Initialization() ->
  /// Loop{ Crossover() -> Mutation() -> Selection() -> ~AdaptiveStrategy() } -> Terminate().
  void DoGeneticAlgorithm();

  void run(const vector<int> &integer_para, const vector<double> &continuous_para, const vector<string> &category_para);
  void run_N(const vector<int> &integer_para, const vector<double> &continuous_para, const vector<string> &category_para);

  void run(const vector<int> &integer_para, const vector<double> &continuous_para, const vector<string> &category_para, shared_ptr<IOHprofiler_suite<int> > suite);
  void run_N(const vector<int> &integer_para, const vector<double> &continuous_para, const vector<string> &category_para, shared_ptr<IOHprofiler_suite<int> > suite);

  double EstimateLinearECDF(const vector<int> &integer_para, const vector<double> &continuous_para, const vector<string> &category_para, shared_ptr<IOHprofiler_suite<int> > suite, vector<double> targets);
  double EstimateLogECDF(const vector<int> &integer_para, const vector<double> &continuous_para, const vector<string> &category_para, shared_ptr<IOHprofiler_suite<int> > suite, vector<double> targets);

  vector<double> EstimateERT(const vector<int> &integer_para, const vector<double> &continuous_para, const vector<string> &category_para, shared_ptr<IOHprofiler_suite<int> > suite, const vector<double> &targets, const vector<size_t> &budgets);

  void Initialization();

  void Preparation();

  void SelectTwoParents();

  void AssignProblem(shared_ptr<IOHprofiler_problem<int> > problem_ptr);

  void AssignLogger(shared_ptr<IOHprofiler_csv_logger<int> > logger_ptr);

  double Evaluate(vector<int> &x);

  void SetSeed(unsigned seed);
  // void Encode();
  
  // void Decode();
  
  void set_mu(const int mu);
  void set_lambda(const int lambda);
  void set_crossover_probability(const double crossover_probablity);
  void set_crossover_mutation_r(const int crossover_mutation_r);
  void set_crossover_mutation_r(string crossover_mutation_r);
  void set_evaluation_budget(const size_t evaluation_budget);
  void set_generation_budget(const size_t generation_budget);
  void set_independent_runs(const size_t independent_runs);

  int get_mu() const;
  int get_lambda() const;
  double get_crossover_probability() const;
  int get_crossover_mutation_r() const;

private:
  int mu_; /// < parents population size
  int lambda_; /// < offspring population size
  double crossover_probability_; /// < probability to do crossover
  //double mutation_probability_; /// < probablity to do mutation
  int crossover_mutation_r_; /// < a flag for correlation between crossover and mutation

  /// Crossover Parameters
  // int crossover_operator_; /// < a flag for operator to be used for crossover
  // double p_u_; /// < probability that a bit to be replaced by the bit of the other parent in uniform crossover

  /// Mutation Parameters
  // int mutation_operator_; /// < a flag for operator to be used for mutation
  // int l_; /// < a static mutation strength
  // double mutation_rate_; /// < mutation rate for standard bit mutation
  // double r_n_; /// < mean value for normalized bit mutation
  // double sigma_n_; /// < sd for normalized bit mutation
  // double beta_f_; /// < beta for fast mutation
  // int adpative_method_; /// < a flag for adaptive method. Default by 0.

  /// Selection Parameters.
  // int s_; /// < a flag for operator to be used for selection.

  vector< vector < int > > parents_population_;
  vector< double > parents_fitness_;
  vector< vector < int > > offspring_population_;
  vector< double > offspring_fitness_;
  double best_found_fitness_;
  vector <int> best_individual_;

  size_t evaluation_; /// < evaluation times
  size_t generation_; /// < number of iterations/generations
  size_t evluation_budget_; /// < budget for evaluations
  size_t generation_budget_; /// < budget for generations

  size_t independent_runs_; /// < number of independent runs.

  double optimum_;
  bool optimum_found_flag_; /// < a flag if the optimum is found.

  vector< int > selected_parents_;

  shared_ptr<IOHprofiler_problem<int> > problem_;
  shared_ptr<IOHprofiler_csv_logger<int> > csv_logger_;
  shared_ptr<IOHprofiler_ecdf_logger<int> > ecdf_logger_;
  
  /// For calculating ECDF
  size_t ecdf_sum_;
  double ecdf_ratio_;
  size_t ecdf_budget_width_;
  size_t ecdf_target_width_;


  /// For calculating ERT
  vector <double> hitting_time_;
  double hiting_target_;
  bool hitting_flag_;
  bool ERT_flag_;
};

#endif // _GENETICALGORITHM_H_
