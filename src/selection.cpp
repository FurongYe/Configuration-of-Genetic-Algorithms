#include "selection.h"

void Selection::DoSelection(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness) {
  switch (this->selection_operator_) {
    case 1:
      this->BestMuPlusStrategy(parents, parents_fitness, offspring, offspring_fitness);
      break;
    case 2:
      this->BestMuCommaStrategy(parents, parents_fitness, offspring, offspring_fitness);
      break;
    case 3:
      this->TournamentPlusStrategy(parents, parents_fitness, offspring, offspring_fitness);
      break;
    case 4:
      this->TournamentCommaStrategy(parents, parents_fitness, offspring, offspring_fitness);
      break;
    case 5:
      this->ProportionalPlusStrategy(parents, parents_fitness, offspring, offspring_fitness);
      break;
    case 6:
      this->ProportionalCommaStrategy(parents, parents_fitness, offspring, offspring_fitness);
      break;
    default:
      break;
  }
}

void Selection::BestMuCommaStrategy(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness) {
  int mu = parents_fitness.size();
  int lambda = offspring_fitness.size();
  
  if (mu > lambda) {
    cout << "the size of offspring is smaller than the size of parents" << std::endl;
    exit(1);
  }
  
  int n = offspring[0].size();
  vector<int> index(lambda);
  for (int i = 0; i != lambda; ++i) {
    index[i] = i;
  }

  if (Opt == optimizationType::MAXIMIZATION) {
    partial_sort(index.begin(), index.begin() + mu, index.end(), 
      [&](const int a, const int b) {return offspring_fitness[a] >= offspring_fitness[b];});
  } else if (Opt == optimizationType::MINIMIZATION) {
    partial_sort(index.begin(), index.begin() + mu, index.end(), 
      [&](const int a, const int b) {return offspring_fitness[a] <= offspring_fitness[b];});
  }

  for (int i = 0; i != mu; ++i) {
    parents[i] = offspring[index[i]];
    parents_fitness[i] = offspring_fitness[index[i]];
  }
}

void Selection::BestMuPlusStrategy(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness) {
  int mu = parents_fitness.size();
  int lambda = offspring_fitness.size();
  int n = parents[0].size();

  vector<int> index_parents(mu);
  vector<int> index_offspring(lambda);
  for (int i = 0; i != mu; ++i) {
    index_parents[i] = i;
  }
  for (int i = 0; i != lambda; ++i) {
    index_offspring[i] = i;
  }

  if (Opt == optimizationType::MAXIMIZATION) {
    sort(index_parents.begin(), index_parents.end(), 
      [&](const int a, const int b) {return parents_fitness[a] < parents_fitness[b];});
    sort(index_offspring.begin(),index_offspring.end(),
      [&](const int a, const int b) {return offspring_fitness[a] > offspring_fitness[b];});

    int j = mu - 1, i = 0, replace_flag = 0, pick_count = 0;
    while (pick_count < mu && i < lambda)
    {
      if (offspring_fitness[index_offspring[i]] >= parents_fitness[index_parents[j]]) {
        replace_flag++;
        i++;
      } else {
        j--;
      }
      pick_count++;
    }
    for (int i = 0; i != replace_flag; ++i) {
      parents[index_parents[i]] = offspring[index_offspring[i]];
      parents_fitness[index_parents[i]] = offspring_fitness[index_offspring[i]];
    }
  } else if (Opt == optimizationType::MINIMIZATION) {
    std::sort(index_parents.begin(), index_parents.end(), 
      [&](const int a, const int b) {return parents_fitness[a] > parents_fitness[b];});
    std::sort(index_offspring.begin(),index_offspring.end(),
      [&](const int a, const int b) {return offspring_fitness[a] < offspring_fitness[b];});

    int j = mu - 1, i = 0, replace_flag = 0, pick_count = 0;
    while (pick_count < mu && i < lambda) {
      if (offspring_fitness[index_offspring[i]] <= parents_fitness[index_parents[j]]) {
        replace_flag++;
        i++;
      } else {
        j--;
      }
      pick_count++;
    }

    for (int i = 0; i != replace_flag; ++i) {
      parents[index_parents[i]] = offspring[index_offspring[i]];
      parents_fitness[index_parents[i]] = offspring_fitness[index_offspring[i]];
    }
  }
}

void Selection::TournamentCommaStrategy(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness) {
  int mu = parents_fitness.size();
  int lambda = offspring_fitness.size();

  if (this->tournament_k_ > lambda) {
    cout << "the size of tournament is larger than the population size" << endl;
    exit(1);
  }

  int count_k, tmp_index;
  double tmp_best;
  vector<int> sample_k;
  vector<int> select_index(mu);
  for (int i = 0; i != mu; ++i) {
    sampleNFromM(sample_k, this->tournament_k_, lambda);
    if (Opt == optimizationType::MAXIMIZATION) {
      tmp_best = numeric_limits<double>::lowest();
      for (int j = 0; j != this->tournament_k_; ++j) {
        if (offspring_fitness[sample_k[j]] > tmp_best) {
          tmp_best = offspring_fitness[sample_k[j]];
          select_index[i] = sample_k[j];
        }
      }
    } else {
      tmp_best = numeric_limits<double>::max();
      for (int j = 0; j != this->tournament_k_; ++j) {
        if (offspring_fitness[sample_k[j]] < tmp_best) {
          tmp_best = offspring_fitness[sample_k[j]];
          select_index[i] = sample_k[j];
        }
      }
    }
  }

  for (int i = 0; i != mu; ++i) {
    parents[i] = offspring[select_index[i]];
    parents_fitness[i] = offspring_fitness[select_index[i]];
  }
}

void Selection::TournamentPlusStrategy(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness) {
  vector< vector<int> > backup_parents = parents;
  vector <double> backup_parents_fitness = parents_fitness;
  int mu = parents_fitness.size();
  int lambda = offspring_fitness.size();

  if (this->tournament_k_ > lambda + mu) {
    cout << "the size of tournament is larger than the population size" << endl;
    exit(1);
  }

  int count_k, tmp_index;
  double tmp_best;
  vector<int> sample_k;
  vector<int> select_index(mu);
  for (int i = 0; i != mu; ++i) {
    sampleNFromM(sample_k, this->tournament_k_, mu + lambda);
    if (Opt == optimizationType::MAXIMIZATION) {
      tmp_best = numeric_limits<double>::lowest();
      for (int j = 0; j != this->tournament_k_; ++j) {
        if (sample_k[j] >= mu) {
          if (offspring_fitness[sample_k[j] - mu] > tmp_best) {
            tmp_best = offspring_fitness[sample_k[j] - mu];
            select_index[i] = sample_k[j];
          }
        } else {
          if (parents_fitness[sample_k[j]] > tmp_best) {
            tmp_best = parents_fitness[sample_k[j]];
            select_index[i] = sample_k[j];
          }
        }
      }
    } else {
      tmp_best = numeric_limits<double>::max();
      for (int j = 0; j != this->tournament_k_; ++j) {
        if (sample_k[j] >= mu) {
          if (offspring_fitness[sample_k[j] - mu] < tmp_best) {
            tmp_best = offspring_fitness[sample_k[j] - mu];
            select_index[i] = sample_k[j];
          }
        } else {
          if (parents_fitness[sample_k[j]] < tmp_best) {
            tmp_best = parents_fitness[sample_k[j]];
            select_index[i] = sample_k[j];
          }
        }
      }
    }
  }

  for (int i = 0; i != mu; ++i) {
    if (select_index[i] >= mu) {
      parents[i] = offspring[select_index[i] - mu];
      parents_fitness[i] = offspring_fitness[select_index[i] - mu]; 
    } else {
      parents[i] = backup_parents[select_index[i]];
      parents_fitness[i] = backup_parents_fitness[select_index[i]];
    }
  }
}

void Selection::ProportionalCommaStrategy(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness) {
  int mu = parents_fitness.size();
  int lambda = offspring_fitness.size();

  vector<double> proportional_f(lambda);
  double fitness_sum = 0;
  
  for (int i = 0; i != lambda; ++i) {
    fitness_sum += offspring_fitness[i];
  }

  if (Opt == optimizationType::MAXIMIZATION) {
    for (int i = 0; i != lambda; ++i) {
      proportional_f[i] = offspring_fitness[i] / fitness_sum;
    }
  } else {
    double max_fitness = numeric_limits<double>::lowest();
    for (int i = 0; i != lambda; ++i) {
      if (offspring_fitness[i] > max_fitness) {
        max_fitness = offspring_fitness[i];
      }
    }
    fitness_sum = max_fitness * lambda - fitness_sum;
    for (int i = 0; i != lambda; ++i) {
      proportional_f[i] = (max_fitness - offspring_fitness[i]) / fitness_sum;
    }
  }

  for (int i = 1; i != lambda; ++i) {
    proportional_f[i] += proportional_f[i-1];
  }

  double r;
  vector<int> select_index(mu);
  for (int i = 0; i != mu; ++i) {
    r = uniform_random();
    int j = 0;
    while (r > proportional_f[j] && r < mu) {
      ++j;
    }
    select_index[i] = j;
  }

  for (int i = 0; i != mu; ++i) {
    parents[i] = offspring[select_index[i]];
    parents_fitness[i] = offspring_fitness[select_index[i]]; 
  }
}

void Selection::ProportionalPlusStrategy(vector< vector<int> > &parents, vector <double> &parents_fitness, const vector< vector<int> > &offspring, const vector<double> &offspring_fitness) {
  vector< vector<int> > backup_parents = parents;
  vector <double> backup_parents_fitness = parents_fitness;
  int mu = parents_fitness.size();
  int lambda = offspring_fitness.size();

  vector<double> proportional_f(mu + lambda);
  double fitness_sum = 0;
  
  for (int i = 0; i != mu; ++i) {
    fitness_sum += parents_fitness[i];
  }
  for (int i = 0; i != lambda; ++i) {
    fitness_sum += offspring_fitness[i];
  }

  if (Opt == optimizationType::MAXIMIZATION) {
    for (int i = 0; i != mu; ++i) {
      proportional_f[i] = parents_fitness[i] / fitness_sum;
    }
    for (int i = mu; i != mu + lambda; ++i) {
      proportional_f[i] = offspring_fitness[i - mu] / fitness_sum;
    }
  } else {
    double max_fitness = numeric_limits<double>::lowest();
    for (int i = 0; i != mu; ++i) {
      if (parents_fitness[i] > max_fitness) {
        max_fitness = parents_fitness[i];
      }
    }
    for (int i = 0; i != lambda; ++i) {
      if (offspring_fitness[i] > max_fitness) {
        max_fitness = offspring_fitness[i];
      }
    }
    fitness_sum = max_fitness * (mu + lambda) - fitness_sum;
    for (int i = 0; i != mu; ++i) {
      proportional_f[i] = (max_fitness - parents_fitness[i]) / fitness_sum;
    }
    for (int i = mu; i != mu + lambda; ++i) {
      proportional_f[i] = (max_fitness - offspring_fitness[i - mu]) / fitness_sum;
    }
  }

  for (int i = 1; i != mu + lambda; ++i) {
    proportional_f[i] += proportional_f[i-1];
  }

  double r;
  vector<int> select_index(mu);
  for (int i = 0; i != mu; ++i) {
    r = uniform_random();
    int j = 0;
    while (r > proportional_f[j] && j < mu + lambda) {
      ++j;
    }
    select_index[i] = j;
  }

  for (int i = 0; i != mu; ++i) {
    if (select_index[i] >= mu) {
      parents[i] = offspring[select_index[i] - mu];
      parents_fitness[i] = offspring_fitness[select_index[i] - mu]; 
    } else {
      parents[i] = backup_parents[select_index[i]];
      parents_fitness[i] = backup_parents_fitness[select_index[i]];
    }
  }
}

void Selection::set_selection_operator(const int s) {
  this->selection_operator_ = s;
}

void Selection::set_selection_operator(string s) {
  transform(s.begin(), s.end(), s.begin(), ::toupper);
  if (s == "BESTPLUS") {
    this->set_selection_operator(BESTPLUS);
  } else if (s == "BESTCOMMA") {
    this->set_selection_operator(BESTCOMMA);    
  } else if (s == "TOURNAMENTPLUS") {
    this->set_selection_operator(TOURNAMENTPLUS);    
  } else if (s == "TOURNAMENTCOMMA") {
    this->set_selection_operator(TOURNAMENTCOMMA);    
  } else if (s == "PROPORTIONALPLUS") {
    this->set_selection_operator(PROPORTIONALPLUS);    
  } else if (s == "PROPORTIONALCOMMA") {
    this->set_selection_operator(PROPORTIONALCOMMA);    
  } else {
    cerr << "invalid value for selection operator";
  }
}

void Selection::set_tournament_k(const int k) {
  this->tournament_k_ = k;
}

int Selection::get_selection_operator() const {
  return this->selection_operator_;
}

int Selection::get_tournament_k() const {
  return this->tournament_k_;
}
