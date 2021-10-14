import os, itertools
import numpy as np
from mpi4py import MPI  

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()


ins = 1
dimension = 100
eval_budget = 50000
gene_budget = 5000000
ind_runs = 10
r_seed = range(1,6)
#targets = [100,100,5050,50,90,33,100,51,100,100,50,90,33,7,51,100,100,4.74,100,200,300,50,10,20,0.2965711]
targets = [100,100,5050,50,90,33,100,51,100,100,50,90,33,7,51,100,100,4.215852,98,180,260,42,9,17.196,0.2965711]
budgets = [927.17, 7557.50, 1086.04, 598.24, 871.32, 720.34, 234979.51, 1385.89 ,3435.78, 67871.19, 2597.02, 6607.87, 1956.84, 190.98, 
        15558.87, 26965.95, 131906.94, 30463.57, 102991.55, 6241.94, 3565.14, 4472.87 , 2685.71, 23962.72, 76938.91]
for i in list(range(0,25)):
    budgets[i] = 50000

config = [[10,1,0.5,0.01],
[10,1,0.5,0.01],
[10,1,0.5,0.01],
[10,1,0.5,0.01],
[10,5,0.5,0.01],
[10,10,0,0.01],
[50,50,0,0.01],
[10,10,0.5,0.01],
[100,50,0.5,0.01],
[100,50,0.5,0.01],
[10,1,0,0.01],
[10,1,0,0.01],
[10,10,0,0.01],
[100,100,0.5,0.01],
[10,10,0,0.01],
[10,10,0,0.01],
[10,10,0.5,0.01],
[100,50,0,0.01],
[10,10,0.5,0.01],
[50,50,0,0.01],
[10,5,0,0.01],
[100,100,0,0.01],
[10,1,0,0.01],
[100,50,0,0.01],
[50,1,0,0.01]]

if rank == 0:
    fcts = list(itertools.product(range(1, 26),r_seed))
    N = len(fcts)

    r = N % size
    step = int((N - r) / size)
    data = [fcts[(i * step) : ((i + 1) * step)] for i in range(size)]

else:
    data = None

data = comm.scatter(data, root=0)

for dat in data:
    fID = dat[0]
    random_seed = dat[1]
    command0 = 'mkdir -p logs/{0}-{1}'.format(fID,random_seed)
    command1 = 'sed -e "s|problem_id|{0}|g" -e "s|instance_id|{1}|g" '\
        '-e "s|dimension|{2}|g" -e "s|evaluation_budget|{3}|g" -e "s|generation_budget|{4}|g" '\
        '-e "s|independent_runs|{5}|g" -e "s|target|{6}|g" -e "s|random_seed|{7}|g" '\
        'problem_id-train > instance/problem-{0}-{7}-train'.format(fID, ins, dimension,  int(budgets[fID-1]), int(budgets[fID-1] * 100),ind_runs,targets[fID-1],random_seed)
    command2 = 'sed -e "s|problem_id|{0}|g" -e "s|instance_id|{1}|g" '\
        '-e "s|dimension|{2}|g" -e "s|evaluation_budget|{3}|g" -e "s|generation_budget|{4}|g" '\
        '-e "s|independent_runs|{5}|g" -e "s|target|{6}|g" -e "s|random_seed|{7}|g" '\
        'problem_id-test > instance/problem-{0}-{7}-test'.format(fID, ins, dimension, int(budgets[fID-1]), int(budgets[fID-1] * 100),ind_runs,targets[fID-1],random_seed)
    command3 = 'sed -e "s|problem-id-folder|{0}-{1}|g" -e "s|problem_id|problem-{0}-{1}|g" '\
        'problem_id-scenario.txt > instance/problem-{0}-{1}-scenario.txt'.format(fID,random_seed)
    command4 = 'sed -e "s|muv|{0}|g" -e "s|lambdav|{1}|g" '\
        '-e "s|pcv|{2}|g" -e "s|pv|{3}|g" '\
        'problem_id-configurations.txt > instance/problem-{4}-configurations.txt'.format(config[fID-1][0], config[fID-1][1], config[fID-1][2],config[fID-1][3],fID)
    command5 = 'sed -e "s|problem_id|problem-{0}-{1}|g" '\
        'problem_id-Rscript > instance/problem-{0}-{1}-Rscript'.format(fID,random_seed)
    command6 = 'chmod -R 777 instance/problem-{0}-{1}-Rscript'.format(fID,random_seed)
    command7 = 'nohup ./instance/problem-{0}-{1}-Rscript 2>&1 > logs/problem-{0}-{1}.log &'.format(fID,random_seed)
    os.system(command0)
    os.system(command1)
    os.system(command2)
    os.system(command3)
    os.system(command4)
    os.system(command5)
    os.system(command6)
    os.system(command7)
