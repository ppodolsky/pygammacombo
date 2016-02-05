#!/usr/bin/env python

def propagateProduct( avals, bvals ):

	a = avals[0]
	astat = avals[1]
	asyst = avals[2]

	b = bvals[0]
	bstat = bvals[1]
	bsyst = bvals[2]

	c = a*b

	cstat = c * ( (astat**2/a**2) + (bstat**2/b**2) )**0.5 # add in quadrature - correlation?
	csyst = c * ( (asyst**2/a**2) + (bsyst**2/b**2) )**0.5 # add in quadrature - correlation?

	return [ c, cstat, csyst ]

def propagateADSVar( radsvals, aadsvals, sign=1 ):

	assert( sign==-1 or sign==1 )

	rads      = radsvals[0]
	rads_stat = radsvals[1]
	rads_syst = radsvals[2]

	aads      = aadsvals[0]
	aads_stat = aadsvals[1]
	aads_syst = aadsvals[2]

	c = rads * ( 1 + (sign * aads) ) # i.e R- = Rads ( 1 + Aads ) and R+ = Rads ( 1 - Aads )

	cstat = c * ( (rads_stat**2/rads**2) + (aads_stat**2/(1 + sign*aads)**2) )**0.5
	csyst = c * ( (rads_syst**2/rads**2) + (aads_syst**2/(1 + sign*aads)**2) )**0.5

	return [ c, cstat, csyst ]

def printObs( name, observables ):

	# want to organise to print in a nice order (probably a dumb way of doing it by whatever)
	printOrder = [ 'rkp' ,'rcp_kk', 'rcp_pipi', 'a_prod', 'afav', 'acp', 'rads', 'aads', 'rm_dk', 'rp_dk', 'rm_dpi', 'rp_dpi' ]

	printKeys = []
	unordered_keys = observables.keys()

	for order in printOrder:
		for key in observables.keys():
			if key.startswith( order ):
				printKeys.append(key)
				unordered_keys.remove(key)

	#for key in observables.keys():
		#for order in printOrder:
			#if key.startswith( order ):
				#printKeys.append(key)
				#unordered_keys.remove(key)
				#break

	assert( len(unordered_keys)==0 )
	assert( len(printKeys)==len(observables.keys()) )

	print name
	print '\t %-15s  %9s  %8s  %8s'%('name','val','stat','syst')
	print '\t ----------------------------------------------'
	for obs in printKeys:
		values = observables[obs]
		if values:
			print '\t %-15s  %9.6f  %8.6f  %8.6f'%(obs,values[0],values[1],values[2])
		else:
			print '\t %-15s  None'%(obs)
	print '================================================='

def twoBody():

	new_observables = \
					{  'rkp_kpi'  	 : [ 0.0779 , 0.0006 , 0.0019  ] ,
						 'rcp_kk'   	 : [ 0.968  , 0.022  , 0.021   ] ,
						 'rcp_pipi' 	 : [ 1.002  , 0.040  , 0.026   ] ,
						 'a_prod'  	 	 : [-0.0023 , 0.0017 , 0.0019  ] ,
						 'afav_dk_kpi' : [-0.0194 , 0.0072 , 0.0060  ] ,
						 #'afav_dpi_kpi': [ 0.0  	 , float('nan')    , float('nan')    ] ,
						 'acp_dk_kk'   : [ 0.0866 , 0.0202 , 0.0081  ] ,
						 'acp_dk_pipi' : [ 0.128  , 0.037  , 0.012   ] ,
						 'acp_dpi_kk'  : [-0.0145 , 0.0050 , 0.0017  ] ,
						 'acp_dpi_pipi': [0.00430 , 0.00860, 0.00309 ] ,
						 'rads_dk_kpi' : [0.0188  , 0.0011 , 0.0010  ] ,
						 'aads_dk_kpi' : [-0.403  , 0.056  , 0.0106  ] ,
						 'rads_dpi_kpi': [0.00360 , 0.00012, 0.00009 ] ,
						 'aads_dpi_kpi': [0.100   , 0.0314 , 0.0094  ]
					}
	old_observables = \
					{  'rkp_kpi'  	 : None ,
						 'rkp_kk'   	 : None ,
						 'rkp_pipi' 	 : None ,
						 'afav_dpi_kpi': None ,
						 'afav_dk_kpi' : None ,
						 'acp_dk_kk'   : None ,
						 'acp_dk_pipi' : None ,
						 'acp_dpi_kk'  : None ,
						 'acp_dpi_pipi': None ,
						 'rm_dk_kpi'   : None ,
						 'rp_dk_kpi'   : None ,
						 'rm_dpi_kpi'  : None ,
						 'rp_dpi_kpi'  : None
					}

	# copy over values
	for obs, values in new_observables.iteritems():
		if obs in old_observables.keys():
			old_observables[obs] = values

	# now do specifics
	old_observables['afav_dpi_kpi'] = [0., float('nan'), float('nan')]
	old_observables['rkp_kk']       = propagateProduct( new_observables['rkp_kpi'], new_observables['rcp_kk']   )
	old_observables['rkp_pipi']     = propagateProduct( new_observables['rkp_kpi'], new_observables['rcp_pipi'] )
	old_observables['rm_dk_kpi']    = propagateADSVar( new_observables['rads_dk_kpi'], new_observables['aads_dk_kpi'],  1 )
	old_observables['rp_dk_kpi']    = propagateADSVar( new_observables['rads_dk_kpi'], new_observables['aads_dk_kpi'], -1 )
	old_observables['rm_dpi_kpi']   = propagateADSVar( new_observables['rads_dpi_kpi'], new_observables['aads_dpi_kpi'],  1 )
	old_observables['rp_dpi_kpi']   = propagateADSVar( new_observables['rads_dpi_kpi'], new_observables['aads_dpi_kpi'], -1 )

	printObs( '2-body NEW', new_observables )
	printObs( '2-body OLD', old_observables )

def fourBody():

	new_observables = \
					{  'rkp_k3pi'  	  : [ 0.0793 , 0.0010  , 0.017  ] ,
						 'a_prod'  	 	  : [-0.0042 , 0.0027  , 0.0020 ] ,
						 'afav_dk_k3pi' : [-0.0004 , 0.0119  , 0.0019 ] ,
						 #'afav_dpi_k3pi': [ 0.0  	 , float('nan')    , float('nan')    ] ,
						 'rads_dpi_k3pi': [ 0.00377, 0.00018 , 0.00006] ,
						 'rads_dk_k3pi' : [ 0.01399, 0.00149 , 0.00060] ,
						 'aads_dpi_k3pi': [ 0.0232 , 0.0480  , 0.0047 ] ,
						 'aads_dk_k3pi' : [-0.313  , 0.102   , 0.038  ]
					}
	old_observables = \
					{  'rkp_k3pi'  	  : None ,
						 'afav_dk_k3pi' : None ,
						 'afav_dpi_k3pi': None ,
						 'rm_dk_k3pi'   : None ,
						 'rp_dk_k3pi'   : None ,
						 'rm_dpi_k3pi'  : None ,
						 'rp_dpi_k3pi'  : None
					}

	# copy over values
	for obs, values in new_observables.iteritems():
		if obs in old_observables.keys():
			old_observables[obs] = values

	# now do specifics
	old_observables['afav_dpi_k3pi'] = [0., float('nan'), float('nan')]
	old_observables['rm_dk_k3pi']    = propagateADSVar( new_observables['rads_dk_k3pi'], new_observables['aads_dk_k3pi'],  1 )
	old_observables['rp_dk_k3pi']    = propagateADSVar( new_observables['rads_dk_k3pi'], new_observables['aads_dk_k3pi'], -1 )
	old_observables['rm_dpi_k3pi']   = propagateADSVar( new_observables['rads_dpi_k3pi'], new_observables['aads_dpi_k3pi'],  1 )
	old_observables['rp_dpi_k3pi']   = propagateADSVar( new_observables['rads_dpi_k3pi'], new_observables['aads_dpi_k3pi'], -1 )

	printObs( '4-body NEW', new_observables )
	printObs( '4-body OLD', old_observables )


# __main__
twoBody()
fourBody()
