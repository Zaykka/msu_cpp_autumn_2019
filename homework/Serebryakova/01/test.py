import subprocess

def check(expr, result):
	out = subprocess.run(['./calc', expr], stdout=subprocess.PIPE)
	if out.stdout.decode('ascii') != result:
		print('error {0} != {1}, got {2}'.format(expr, result, out.stdout))


check('2+2', '4')
check('-2+6', '4')
check('-1', '-1')
check('2+30+100', '132')
check('3*-5', '-15')
check('-3*5', '-15')
check('1*2 + 3*4 ', '14')
check('1+10*2', '21')
check('  10*  2  + 1  ', '21')

