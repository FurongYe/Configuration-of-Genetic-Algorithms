#include <geneticAlgorithm.h>

///
///
/// Input: Dimension, evaluation budget, independent runs; integer_para (4), continuous_para (6), category_para (4).
int main (int argc, char *argv[]) {
  //std::shared_ptr<IOHprofiler_problem <int> > problem(new OneMax(1,100));
  //std::shared_ptr<IOHprofiler_problem <int> > problem(new Linear(1,100));
  GeneticAlgorithm ga;
  //std::shared_ptr<IOHprofiler_csv_logger> logger(new IOHprofiler_csv_logger("./","PBO","PBO-config","PBO-config") );
  //logger->activate_logger();
  //ga.AssignProblem(problem);
  //ga.AssignLogger(logger);
  // ga.set_evaluation_budget(50000);
  // ga.set_generation_budget(100000);
  // ga.set_independent_runs(10);
  //int n = 10;
  //while(n--){
  //  ga.run(integer_para, continuous_para, category_para);
  //}
  vector<int> problem_id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
  vector<int> instance_id ={1};
  vector<int> dimension;
  
  
  vector<double> targets = {100,100,5050,50,90,33,100,51,100,100,50,90,33,7,51,100,100,4.215852,98,180,260,42,9,17.196,-0.2965711};

  // vector<int> integer_para = {1, 10, 1, 6};
  // vector<double> continuous_para = {0.3, 0.3, 1, 0.01, 0.01, 1.0, 1.5};
  // vector<string> category_para = {"IND", "TWOPOINTCROSSOVER", "STATICSAMPLE","PROPORTIONALCOMMA"};
  // cout << ga.EstimateECDF(integer_para, continuous_para, category_para, pbo, targets) << endl;

  // vector<int> integer_para1 = {1, 1, 1, 6};
  // vector<double> continuous_para1 = {0, 0.3, 1, 0.01, 0.01, 1.0, 1.5};
  // vector<string> category_para1 = {"IND", "TWOPOINTCROSSOVER", "STATICSAMPLE","BESTPLUS"};
  // shared_ptr<IOHprofiler_suite<int> > pbo1(new PBO_suite(problem_id,instance_id,dimension));
  // cout << ga.EstimateECDF(integer_para1, continuous_para1, category_para1, pbo1, targets) << endl;

  if (argc != 18) {
    std::cout << "incorrect input numbers" << endl;
  }

  dimension.push_back(stoi(argv[1]));
  shared_ptr<IOHprofiler_suite<int> > pbo(new PBO_suite(problem_id,instance_id,dimension));

  ga.set_evaluation_budget(stoi(argv[2]));
  ga.set_generation_budget(100 * stoi(argv[2]));
  ga.set_independent_runs(stoi(argv[3]));

    vector<int> integer_para;
  integer_para.push_back(stoi(argv[4]));
  integer_para.push_back(stoi(argv[5]));
  integer_para.push_back(0);
  integer_para.push_back(0);

  vector<double> continuous_para;
  continuous_para.push_back(stod(argv[6]));
  continuous_para.push_back(0.5);
  continuous_para.push_back(stod(argv[7]));
  continuous_para.push_back(0);
  continuous_para.push_back(0);
  continuous_para.push_back(0);

  vector<string> category_para;
  category_para.push_back("OR");
  category_para.push_back("UNIFORMCROSSOVER");
  category_para.push_back("BINOMIALSAMPLE");
  category_para.push_back("BESTPLUS");

  cout << ga.EstimateLinearECDF(integer_para, continuous_para, category_para, pbo, targets) << endl;
  return 0;
}
