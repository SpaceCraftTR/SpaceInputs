COMPILER = c++
COMPILER_FLAGS = -g -c -Wall -fPIC
CPP_STD = c++11

examples:
		@echo "Making examples..."
		$(COMPILER) "examples/keyboard_checker.cpp" -o "build/examples/keyboard_checker" -std=$(CPP_STD) -lspaceinputs -lX11
		$(COMPILER) "examples/mouse_checker.cpp" -o "build/examples/mouse_checker" -std=$(CPP_STD) -lspaceinputs -lX11
library:
		$(COMPILER) $(COMPILER_FLAGS) spaceinputs.cpp -o "build/shared_lib/spaceinputs.o"
		$(COMPILER) -shared -o "build/shared_lib/libspaceinputs.so" "build/shared_lib/spaceinputs.o"	
		@echo "Building success! Run install.sh to install SpaceInputs."		
