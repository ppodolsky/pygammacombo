import re

# read in the tex source
with open("3fbGLWADSresult.tex") as f:
	content = f.readlines()

# parse the variable name, the central value, and two errors
print "\nANA order: parsed output with line numbers"
parsedcontent = []
for i in xrange(0,len(content)):
	#print content[i]
	mo = re.match ("(\S+).*?(-?\d+\.\d+|X+).*?(\d+\.\d+).*?(\d+\.\d+).*?", content[i])
	if mo:
		parsedcontent += [mo.groups()]
		print len(parsedcontent), mo.groups()


# print in corrected order
print "\ngammacombo order: 2-body"
for i in (1, 3, 2, 4, 5, 6, 8, 7, 9, 10, 11, 12, 13):
	print "%2i"%i, "%-30s %-10s %-10s %-10s" % parsedcontent[i-1]

