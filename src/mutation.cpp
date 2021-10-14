#include "mutation.h"

void Mutation::DoMutation(vector<int> &y) {
  int mutation_strength;
  mutation_strength = this->SampleL(y.size());
  this->Flip(y,mutation_strength);
}

void Mutation::Flip(vector<int> &y, const int l) {
  int n = y.size();
  sampleNFromM(this->m_flipped_index,l,n);
  for(int i = 0; i != l; ++i) {
    y[this->m_flipped_index[i]] = (y[this->m_flipped_index[i]] + 1) % 2;
  }
}

int Mutation::SampleConditionalBinomial(const double p, const int n) {
  int l = 0;
  while(l == 0) {
    for(int i = 0; i != n; ++i) {
      if (uniform_random() < p) {
        ++l;
      }
    }
  }
  return l;
}

int Mutation::SampleBinomial(const double p, const int n) {
  int l = 0;
  for(int i = 0; i != n; ++i) {
    if (uniform_random() < p) {
      ++l;
    }
  }
  return l;
}

int Mutation::SampleNormal(double mu, double sigma) {
  int l;
  l = normal_random() * sigma + mu;
  return (int)(l + 0.5);
}

int Mutation::SampleConditionalNormal(double mu, double sigma, int upperbound) {
  int l;
  do {
    l = normal_random() * sigma + mu;
  } while((int)(l + 0.5) <= 0 || (int)(l + 0.5) >= upperbound);
  return (int)(l + 0.5);
}

int Mutation::SampleLogNormal(double mu, double sigma) {
  int l;
  l = normal_random() * sigma + mu;
  return (int)(exp(l) + 0.5);
}

int Mutation::SampleConditionalLogNormal(double mu, double sigma, int upperbound) {
  int l;
  do {
    l = normal_random() * sigma + mu;
  } while((int)(exp(l) + 0.5) <= 0 || (int)(exp(l) + 0.5) >= upperbound);
  return (int)(exp(l) + 0.5);
}

int Mutation::SampleFromDistribution(const std::vector<double> &distribution) {
  double p = 0.0;
  double r = uniform_random();
  int j = 0;
  while (j < distribution.size()) {
    if (r > p && r < p + distribution[j]) {
      break;
    }
    p +=  distribution[j];
    ++j;
  }
  return j;
}

void Mutation::PowerLawDistribution(int N) {
  this->power_law_distribution_ = std::vector<double>(N+1);
  double C;
  size_t i;

  C = 0.0;
  for(i = 0; i < N; ++i){
    C += pow(i+1,-this->beta_f_);
  }
  for(i = 0; i < N; ++i){
    this->power_law_distribution_[i+1] = 1/C * pow(i+1,-this->beta_f_);
  }

  this->power_law_distribution_[0] = 0.0;
}

int Mutation::SampleL(const int N) {
  int mutation_strength = 0;
  switch (this->mutation_operator_) {
    case 1:
      mutation_strength = this->l_;
      break;
    case 2:
      mutation_strength = this->SampleConditionalBinomial(this->mutation_rate_,N);
      break;
    case 3:
      mutation_strength = this->SampleConditionalNormal(this->r_n_, this->sigma_n_, floor(N/2.0));
      break;
    case 4:
      mutation_strength = this->SampleFromDistribution(this->power_law_distribution_);
      break;
    default:
      break;
  }
  return mutation_strength;
}

void Mutation::set_mutation_operator(const int m) {
  this->mutation_operator_ = m;
}

void Mutation::set_mutation_operator(string m) {
  transform(m.begin(), m.end(), m.begin(), ::toupper);
  if (m == "STATICSAMPLE") {
    this->set_mutation_operator(STATICSAMPLE);
  } else if (m == "BINOMIALSAMPLE") {
    this->set_mutation_operator(BINOMIALSAMPLE);
  } else if (m == "NORMALSAMPLE") {
    this->set_mutation_operator(NORMALSAMPLE);
  } else if (m == "POWERLAWSAMPLE") {
    this->set_mutation_operator(POWERLAWSAMPLE);
  } else {
    cerr << "invalid value for mutation operator";
  }
}

void Mutation::set_l(const int l) {
  this->l_ = l;
}

void Mutation::set_mutation_rate(const double mutation_rate) {
  this->mutation_rate_ = mutation_rate;
}

void Mutation::set_r_n(const double r_n) {
  this->r_n_ = r_n;
}

void Mutation::set_sigma_n(const double sigma_n) {
  this->sigma_n_ = sigma_n;
}

void Mutation::set_beta_f(const double beta_f) {
  this->beta_f_ = beta_f;
}

int Mutation::get_mutation_operator() const {
  return this->mutation_operator_;
}

int Mutation::get_l() const {
  return this->l_;
}

double Mutation::get_mutation_rate() const {
  return this->mutation_rate_;
}

double Mutation::get_r_n() const {
  return this->r_n_;
}

double Mutation::get_sigma_n() const {
  return this->sigma_n_;
}
double Mutation::get_beta_f() const {
  return this->beta_f_;
}
