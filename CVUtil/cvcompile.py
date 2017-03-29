import subprocess
import sys

def remext(filename):
	return filename[:filename.rfind('.')]

files = sys.argv[1:]
subprocess.run('g++ `pkg-config --cflags opencv` {} `pkg-config --libs opencv` -std=c++11 -o {}'.format(' '.join(files), remext(files[-1])), shell=True)