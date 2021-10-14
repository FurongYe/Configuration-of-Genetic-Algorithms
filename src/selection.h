/// \file selection.hpp
/// \brief Header file for class Selection.
///
/// It contains functions of selection operators.
/// 
/// \author Furong Ye
/// \date 2020-07-02

#ifndef _SELECTION_H_
#define _SELECTION_H_

#include "common.h"

enum selection_operator {
  BESTPLUS = 1,
  BESTCOMMA = 2,
  TOURNAMENTPLUS = 3,
  TOURNAMENTCOMMA = 4,
  PROPORTIONALPLUS = 5,
  PROPORTIONALCOMMA = 6
};

class Selection {
public:
  Selection(){}
  ~Selection() {}
  Selection(const Selection&) = delete;
  Selection &operator = (const Selection&) = delete;

  void DoSelection(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness);
  
  void BestMuCommaStrategy(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness);
  void BestMuPlusStrategy(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness);
  void TournamentCommaStrategy(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness);
  void TournamentPlusStrategy(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness);
  void ProportionalCommaStrategy(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness);
  void ProportionalPlusStrategy(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness);

  void set_selection_operator(const int s);
  void set_selection_operator(string s);
  void set_tournament_k(const int k);

  int get_selection_operator() const;
  int get_tournament_k() const;

private:
  int selection_operator_;
  int tournament_k_;
};

#endif // _SELECTION_H_
