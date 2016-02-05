import numpy as np


def isSquareMatrix(m):
    s = np.shape(m)
    return s[0]==s[1]

def getSquareMatrixDim(m):
    if not isSquareMatrix(m):
        print "Error: matrix not quadratic"
        exit()
    return np.shape(m)[0]

def changeVarOrderInCor(cor, newOrder):
	'''Swap rows and columns of a correlation
	matrix to match a new order of variables.
	\param cor 	The correlation matrix (numpy matrix)
	\param newOrder An array defining the new order, e.g.
			[2,1,3,4], which will swap the order
			of the first two variables.
	\return The new correlation matrix.'''
	# check input dimensions
	ndim = getSquareMatrixDim(cor)	
	if len(newOrder)!=ndim:
		print "newOrder dimension doesn't match that of cor."
		return
	# change newOrder to start counting variables at 0 not at 1
	for i in xrange(0,ndim):
		newOrder[i] -= 1
	# check if every variable is present in newOrder
	newOrderSorted = sorted(newOrder)
	for i in xrange(0,ndim):
		if newOrderSorted[i]!=i:
			print "now all variables present once in newOrder."
			return
	# reorder correlation matrix
	newCor = np.asmatrix(np.zeros(shape=(ndim,ndim)))
	for i in xrange(0,ndim):
		for j in xrange(0,ndim):
			newCor[i,j] = cor[newOrder[i],newOrder[j]]
	return newCor


if __name__ == "__main__":
	#
	# test
	#
	cor = np.matrix([
	[ 11, 21, 31, 41, 51 ],
	[ 12, 22, 32, 42, 52 ],
	[ 13, 23, 33, 43, 53 ],
	[ 14, 24, 34, 44, 54 ],
	[ 15, 25, 35, 45, 55 ]
	])
	print cor
	print changeVarOrderInCor(cor,[5,4,3,2,1])

