import math
from copy import deepcopy

import numpy as np
from numpy.linalg import eig
from numpy.linalg import inv
from numpy.linalg import svd
from numpy.linalg import norm

import matplotlib.pyplot as plt



def graphToH(G):
    """For a connectivity matrix G, returns the corresponding H2."""
    H2 = deepcopy(G)
    np.fill_diagonal(H2, 1)
    return H2

def errorMat(x, H2):
    A = np.outer(x, x)
    # Note that this is element-wise multiplication (mask).
    return A - H2*A

def grad(x, E):
    """Only in this form because of the loop construction;
    otherwise, one ought to show where E comes from.

    This notation only works because E has a zero diagonal,
    because H2 has diagonals all along the axis."""
    return 2*(np.matmul(E, x) + np.matmul(E.T, x))

def renormL2(y):
    return y/norm(y)

def renormCube(y):
    return y/np.max(np.fabs(y))

# The last bit is the initial projection of H2 to rank1 space.
# We can do this simply, with svd.

def r1(H2):
    """Returns the projection of H2 to N-dimensional rank-1 space
    (or more precisely, the space ot the generating vectors).

    As written, this only works for symmetric matrices, but that's OK,
    becaurse H2 is a symmetric matrix."""
    u, s, v = svd(H2)
    x = v[0]
    return x*math.sqrt(s[0])

def seek(x, H2, ren=renormL2, beta = 0.001, cutoff = 1e-4, maxIter = 100000, recordStep=100):
    """If recordStep = 0, then there is no recording done.
    Undefined behavior if not integer."""
    errors = []
    i = 0
    y = ren(x)
    while i < maxIter:
        #### First, the deep math.
        # Error matrix
        E = errorMat(y, H2)
        # Gradient.
        g = grad(y, E)
        #  Grad descent.
        y = y - beta*g
        #  Renorm
        y = ren(y)
        #### Next the logistics; counters, etc.
        r = norm(E)
        if recordStep != 0 and i % recordStep == 0:
            print y
            print E
            print r
            print '#####'
            errors.append(r)
        if r < cutoff:
            break
        i += 1
    #If we did not dip below the cutoff, we did not converge.
    if r > cutoff:
        print "Warning: Error greater than cutoff, did not converge."
    #Return vector, the clique it represents, and the error trace.
    return y, np.sign(np.round(y, 4)), errors


def solve(G, ren=renormL2, beta=1e-3, cutoff=1e-4, maxIter=100000, recordStep=100):
    H2 = graphToH(G)
    print H2
    x = r1(H2)
    print x
    return seek(x, H2, ren, beta, cutoff, maxIter, recordStep)


