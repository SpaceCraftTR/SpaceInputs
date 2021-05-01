# Installer script for SpaceInputs library.

#!/bin/bash
echo "Where are the shared libraries in your system?"; 
read shared_lib_path;
echo "Are you sure about the path "$shared_lib_path"? [y/n]"; 
read selection; if [ $$selection = "n" ] || [ $$selection = "N" ]; then echo "Aborting the installation..."; exit 0 ; fi 
sudo cp $(pwd)/build/shared_lib/* $shared_lib_path && sudo cp -r $(pwd)/spaceinclude /usr/include && sudo cp $(pwd)/spaceinputs.hpp /usr/include/ && sudo cp $(pwd)/lib/spacelogs.hpp /usr/include;
