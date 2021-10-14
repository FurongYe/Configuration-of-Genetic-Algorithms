import os, itertools
import numpy as np
from mpi4py import MPI  

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()


if rank == 0:
    fcts = [[2,2],[2,4],[3,4],[9,1],[9,5],[11,1],[11,2],[11,4],[11,5],[12,1],[12,2],[12,3],[12,4],[12,5],[13,1],[13,2],[18,2],[18,3],[18,4],[19,2],[19,3],[19,4],[22,3],[23,2],[23,4],[24,3],[25,1],[25,2],[25,3],[25,4],[25,5]]
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
