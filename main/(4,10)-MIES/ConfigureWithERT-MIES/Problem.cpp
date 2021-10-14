#include <geneticAlgorithm.h>

///
///
/// Input: Problem, Dimension, evaluation budget, independent runs; integer_para (4), continuous_para (6), category_para (4).
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
  vector<int> problem_id;
  vector<int> instance_id ={1};
  vector<int> dimension;
  
  
  //vector<double> targets = {100,100,5050,50,90,33,100,51,100,100,50,90,33,7,51,100,100,4.74,100,200,300,50,10,20,-0.2965711};
  
  if (argc != 10) {
    std::cout << "incorrect input numbers" << endl;
  }

  problem_id.push_back(stoi(argv[1]));
  dimension.push_back(stoi(argv[2]));
  shared_ptr<IOHprofiler_suite<int> > pbo(new PBO_suite(problem_id,instance_id,dimension));

  ga.set_evaluation_budget(stoi(argv[3]));
  ga.set_generation_budget(stoi(argv[3]) * 100);
  ga.set_independent_runs(stoi(argv[4]));

  vector<double> t_targets;
  t_targets.push_back(stod(argv[5]));
  
  vector<int> integer_para;
  integer_para.push_back(stoi(argv[6]));
  integer_para.push_back(stoi(argv[7]));
  integer_para.push_back(0);
  integer_para.push_back(0);

  vector<double> continuous_para;
  continuous_para.push_back(stod(argv[8]));
  continuous_para.push_back(0.5);
  continuous_para.push_back(stod(argv[9]));
  continuous_para.push_back(0);
  continuous_para.push_back(0);
  continuous_para.push_back(0);

  vector<string> category_para;
  category_para.push_back("OR");
  category_para.push_back("UNIFORMCROSSOVER");
  category_para.push_back("BINOMIALSAMPLE");
  category_para.push_back("BESTPLUS");

  vector<size_t> t_budgets;
  t_budgets.push_back((size_t) stoi(argv[3]));
  cout << ga.EstimateERT(integer_para, continuous_para, category_para, pbo, t_targets, t_budgets)[0] << endl;
  return 0;
}
