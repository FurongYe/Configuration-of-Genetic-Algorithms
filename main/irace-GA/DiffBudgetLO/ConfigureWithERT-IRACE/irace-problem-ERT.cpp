#include <geneticAlgorithm.h>

// the arguements:
// instance (problem_id-instance_id-dimension-random_seed-evaluation_budget-generation_budget-independent_runs-target) --parameters
int main(int argc, char**argv) {
  
  char *program_name = argv[0];
    
  // if (argc < 6) {
  //     error("Not enough parameters");
  // }
  string instance(argv[1]);
  size_t found = instance.find("Instances");
  if (found!=string::npos) {
    instance = instance.substr(found+10);
  }
  string delimiter = "-";
  vector<string> instance_vec;
  size_t pos = 0;
  string token;
  while ((pos = instance.find(delimiter)) != std::string::npos) {
      token = instance.substr(0, pos);
      instance_vec.push_back(token);
      instance.erase(0, pos + delimiter.length());
  }
  instance_vec.push_back(instance);


  vector<int> integer_para = {-1, -1, 0, 0};
  vector<double> continuous_para = {-1, 0.5, -1, 0, 0, 0};
  vector<string> category_para = {"OR", "UNIFORMCROSSOVER", "BINOMIALSAMPLE","BESTPLUS"};
  for (int i = 2; i < argc; i += 2) {
      std::string param(argv[i]);
      std::string value(argv[i+1]);
      if (param == "--mu") {
        integer_para[0] = stoi(value.c_str());
      } else if (param == "--lambda") {
        integer_para[1] = stoi(value.c_str());
      } else if (param == "--l") {
        integer_para[2] = stoi(value.c_str());
      } else if (param == "--tournament_k") {
        integer_para[3] = stoi(value.c_str());
      } else if (param == "--pc") {
        continuous_para[0] = stof(value.c_str());
      } else if (param == "--pu") {
        continuous_para[1] = stof(value.c_str());
      } else if (param == "--p") {
        continuous_para[2] = stof(value.c_str());
      } else if (param == "--r") {
        continuous_para[3] = stof(value.c_str());
      } else if (param == "--sigma") {
        continuous_para[4] = stof(value.c_str());
      } else if (param == "--beta") {
        continuous_para[5] = stof(value.c_str());
      } else if (param == "--mutation_crossover_r") {
        category_para[0] = value.c_str();
      } else if (param == "--crossover") {
        category_para[1] = value.c_str();
      } else if (param == "--mutation") {
        category_para[2] = value.c_str();
      } else if (param == "--selection") {
        category_para[3] = value.c_str();
      } else {
          cout << "Unrecognized parameter：" << param << ":" << value << endl;
      }
  }
  //std::shared_ptr<IOHprofiler_problem <int> > problem(new OneMax(1,100));
  //std::shared_ptr<IOHprofiler_problem <int> > problem(new Linear(1,100));
  GeneticAlgorithm ga;
  //std::shared_ptr<IOHprofiler_csv_logger> logger(new IOHprofiler_csv_logger("./","OM","GA","GA") );
  //logger->activate_logger();
  //ga.AssignProblem(problem);
  //ga.AssignLogger(logger);
  //int n = 10;
  //while(n--){
  //  ga.run(integer_para, continuous_para, category_para);
  //}
  vector<int> problem_id;
  problem_id.push_back(stoi(instance_vec[0]));
  vector<int> instance_id;
  instance_id.push_back(stoi(instance_vec[1]));
  vector<int> dimension;
  dimension.push_back(stoi(instance_vec[2]));
  shared_ptr<IOHprofiler_suite<int> > pbo(new PBO_suite(problem_id,instance_id,dimension));

  ga.SetSeed((unsigned)stoi(instance_vec[3]));
  ga.set_evaluation_budget((size_t)stoi(instance_vec[4]));
  ga.set_generation_budget(stoi(instance_vec[5]));
  ga.set_independent_runs(stoi(instance_vec[6]));

  
  vector<double> targets;
  targets.push_back(stoi(instance_vec[7]));
  vector<size_t> budgets; 
  budgets.push_back((size_t)stoi(instance_vec[4]));

  if(problem_id[0] == 25) {targets[0] = -targets[0];}
  //cout << ga.EstimateECDF(integer_para, continuous_para, category_para, pbo, targets) << endl;
  // if (find(integer_para.begin(), integer_para.end(),-1) != integer_para.end()) {
  //   cout << "incorrect integer parameters" << endl;
  // }
  // if (find(continuous_para.begin(), continuous_para.end(),-1) != continuous_para.end()) {
  //   cout << "incorrect continuous parameters" << endl;
  // }
  // if (find(category_para.begin(), category_para.end(),"NULL") != category_para.end()) {
  //   cout << "incorrect categorical parameters" << endl;
  // }
  cout << ga.EstimateERT(integer_para, continuous_para, category_para, pbo, targets, budgets)[0] << endl;

}
