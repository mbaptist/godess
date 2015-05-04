#!/usr/bin/env python

import os
import subprocess

def Main():
	cmake_cmd = "/usr/bin/cmake"
	
	top_dir = os.path.dirname(os.path.realpath(__file__))
	
	build_dir = os.path.join(top_dir,"build")
	
	install_dir = os.path.join(top_dir,"install")
	
	packages_dir = os.path.join(top_dir,"packages")

	print build_dir
	try:
		os.makedirs(build_dir)
	except:
		pass	
	os.chdir(build_dir)
	
	os_run([cmake_cmd,"-DCMAKE_INSTALL_PREFIX:PATH="+install_dir,top_dir])

	os_run(["make","all"])

	try:
		os.makedirs(install_dir)
	except:
		pass
	os_run (["make","install"])


def os_run(cmd_line):
	p=subprocess.Popen(cmd_line)
	p.wait()


if __name__ == "__main__":
	Main()

