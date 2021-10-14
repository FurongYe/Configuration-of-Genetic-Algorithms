import os, itertools
import numpy as np
from mpi4py import MPI  

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()


if rank == 0:
    fcts = list(itertools.product([7,18,22,23,5],range(1,6)))
    N = len(fcts)

    r = N % size
    step = int((N - r) / size)
    data = [fcts[(i * step) : ((i + 1) * step)] for i in range(size)]

else:
    data = None

data = comm.scatter(data, root=0)

for fct in data:
    fID = fct[0]
    rs = fct[1]
    command1 = 'python3 problem.py {0} {1} > logs/problem_{0}-{1}.log 2>&1 &'.format(fID,rs)
    os.system(command1)
