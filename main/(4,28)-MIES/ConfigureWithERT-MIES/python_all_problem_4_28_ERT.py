import os, itertools
import numpy as np
from mpi4py import MPI  

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

if rank == 0:
    fcts = list(itertools.product([1,5,7,8,9,18,22,23,25],range(1,6)))
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
    command1 = 'python3 problem.py {0} {1} > logs/problem_{0}-{1}.log 2>&1 &'.format(fID,random_seed)
    os.system(command1)
