import os
import numpy as np
import sys

from pdb import set_trace

import numpy as np
from bayes_optim import BO,ParallelBO
from bayes_optim.Surrogate import RandomForest
from bayes_optim.SearchSpace import ContinuousSpace, NominalSpace, OrdinalSpace
import datetime
start = datetime.datetime.now()
np.random.seed(666)

n_step = 500
n_init_sample = 10
dimension = 100
ind_runs = 10
#targets = [100,100,5050,50,90,33,100,51,100,100,50,90,33,7,51,100,100,4.74,100,200,300,50,10,20,-0.2965711]
targets = [100,100,5050,50,90,33,100,51,100,100,50,90,33,7,51,100,100,4.215852,98,180,260,42,9,17.196,-0.2965711]
budgets = [927.17, 7557.50, 1086.04, 598.24, 871.32, 720.34, 234979.51, 1385.89 ,3435.78, 67871.19, 2597.02, 6607.87, 1956.84, 190.98, 
        15558.87, 26965.95, 131906.94, 30463.57, 102991.55, 6241.94, 3565.14, 4472.87 , 2685.71, 23962.72, 76938.91]

for i in list(range(0,25)):
    budgets[i] = 50000

eval_type = 'dict' # control the type of parameters for evaluation: dict | list

def run_alg(x):
    command = './PBO ' + str(dimension) + ' 50000 ' + str(ind_runs) + ' ' + str(x['mu']) + ' ' + str(x['lambda']) + ' ' +str(x['pc']) + ' ' + str(x['p'])
    #print(command)m
    p = os.popen(command)
    result = p.read()
    return result

def obj_func(x):
    result = run_alg(x)
    #print(result)
    return result

def g(x):
    return [-int(x['pc']), int(x['mu']) - 1.9]

def h(x):
    #print(x)
    if (int(x['pc']) > 0  & int(x['mu']) < 2):
        return 1
    else:
        return 0

# First we need to define the Search Space
# the search space consists of two continues variable
# one ordinal (integer) variable
# and one categorical.

#here we defined two variables at once using the same lower and upper bounds.
I1 = OrdinalSpace([1, 100], var_name='mu')
I2 = OrdinalSpace([1, 100], var_name='lambda')
C1 = ContinuousSpace([0, 1],var_name='pc')
C2 = ContinuousSpace([0.005, 0.5],var_name='p')
#the search space is simply the product of the above variables
search_space = C1 + C2 + I1 + I2


#next we define the surrogate model and the optimizer.

model = RandomForest(levels=search_space.levels)

opt = ParallelBO(
    search_space=search_space, 
    obj_fun=obj_func,
    eq_fun=h, 
    model=model, 
    max_FEs=2500, 
    DoE_size=10,    # the initial DoE size
    eval_type='dict',
    acquisition_fun='MGFI',
    acquisition_par={'t' : 2},
    minimize=False,
    n_job=8,       # number of processes
    n_point=10,     # number of the candidate solution proposed in each iteration
    verbose=True   # turn this off, if you prefer no output
)
# and we run the optimization.
# incumbent, stop_dict = opt.run()
# print(incumbent,stop_dict)
xopt, fitness, stop_dict = opt.run()

end = datetime.datetime.now()
print('time: {}'.format(end-start))
print('xopt: {}'.format(xopt))
print('fopt: {}'.format(fitness))
print('stop criteria: {}'.format(stop_dict))
