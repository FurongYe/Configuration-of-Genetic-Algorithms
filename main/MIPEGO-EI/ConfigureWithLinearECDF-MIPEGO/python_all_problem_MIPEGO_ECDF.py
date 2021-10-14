import os, itertools
import numpy as np
from mpi4py import MPI  

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()


if rank == 0:
    fcts = list(range(1, 26))
    N = len(fcts)

    r = N % size
    step = int((N - r) / size)
    data = [fcts[(i * step) : ((i + 1) * step)] for i in range(size)]

else:
    data = None

data = comm.scatter(data, root=0)

for fct in data:
    fID = fct
    command1 = 'python3 problem.py {0} > logs/problem_{0}.log 2>&1 &'.format(fID)
    os.system(command1)
