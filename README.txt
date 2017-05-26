Classical Snake Game 
Computer Graphics Project in OpenGl
Mayank Metha D

Windows:
	Use VS2017
	Add glut32.dll to c:/windows/system32
	Add glut.h to <VS VC location>/include/GL
	Add glut32.lib to to <VS VC location>/lib/x86 and <VS VC locaion>/lib/onecore/x86
	Clone project
	Add opengl.lib, glu32.lib, glut32.lib to Project->Properties->Linker->Input->Additional Dependence->Edit
	Compile and run
MacOS/OSX:
	Use XCode8
	Clone project
	Add OpenGl.framework and GLUT.framework to Traget Linked Frameworks and Libraries
	Compile and run
Linux(Ubuntu/Debian):
	Clone project
	run "sh ubuntuDependicies.sh" to install freeglut3
	run "make" to compile project
	run "./snakes.exe" to execute project 
