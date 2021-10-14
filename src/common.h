
#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
#include <memory>
#include <random>
#include <cmath>
#include <limits>
#include <algorithm>
#include <IOHprofiler_all_suites.hpp>
#include <IOHprofiler_csv_logger.h>
#include <IOHprofiler_ecdf_logger.h>

using namespace std;

static default_random_engine random_gen(1);
static normal_distribution<double> normal_dis(0,1);
static uniform_real_distribution<double> uniform_dis(0.0,1.0);

enum optimizationType {
  MINIMIZATION = 0,
  MAXIMIZATION = 1
};

static optimizationType Opt = MAXIMIZATION;

static double normal_random() {
  return normal_dis(random_gen);
}

static double uniform_random() {
  return uniform_dis(random_gen);
}

static void sampleNFromM(vector<int> &sampled_number, int n, int m) {
  if (sampled_number.size() != 0) {
    sampled_number.clear();
  }

  if (n == 0) {
    std::cout <<  "sampled zero number" << std::endl;
  }

  vector<int> population;
  population.reserve(m);
  for (int i = 0; i < m; ++i) {
    population.push_back(i);
  }

  int temp,randPos;
  sampled_number.reserve(n);

  if (n > m/2) {
    for (int i = m-1; i > 0; --i) {
      randPos = (int)floor(uniform_random() * (i+1));
      temp = population[i];
      population[i] = population[randPos];
      population[randPos] = temp;
      sampled_number.push_back(population[i]);
      if(m-i-1 == n-1) {
        break;
      }
    }
    if(n == m) {
      sampled_number.push_back(population[0]);
    }
  } else {
    bool resample = false;
    for (int i = 0; i != n; ++i) {
      do {
        resample = false;
        randPos = (int)floor(uniform_random() * m);
        for (int j = 0; j != i; ++j) {
          if(randPos == sampled_number[j]) {
            resample = true;
            break;
          }
        }
      } while (resample);
      sampled_number.push_back(randPos);
    }
  }
};

#endif // _COMMON_H_
