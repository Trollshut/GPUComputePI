# GPU Compute PI
Simple app to run a vertex and fragment shader to render a red rectangle and imgui demo window. Set up for the 
raspberry pi 4 with 7 inch display setup. 

# Requirements

Make sure you have the FULL 64 bit version of the raspberry pi os installed via the installer. 

Make sure you are updated:
```
sudo apt update
sudo apt upgrade
```
1.Requires install of Cmake from source as raspberry pi repo is outdated atm

  Follow these commands in cmd on raspberry pi to install cmake:
```
sudo apt install -y wget build-essential libssl-dev
cd ~
wget https://github.com/Kitware/CMake/releases/download/v3.28.3/cmake-3.28.3.tar.gz
tar -xzf cmake-3.28.3.tar.gz
cd cmake-3.28.3
./bootstrap
make -j$(nproc)
sudo make install
```
2. install libraries that include opengl and x11 requirements:

sudo apt install libgl1-mesa-dev xorg-dev -y

## Building
From the main folder run the following commands which will create a folder
configure cmake and dependencies into the build folder then make the project. 
```
mkdir build
cd build
cmake ..
make -j4
```
after project is built you can find it it GPUComputePI/build/App called ./App by default

Tested on Raspberry Pi 4 using , more testing to follow.

## Third-Party Dependencies
Uses the following third-party dependencies:
- [GLFW 3.4](https://github.com/glfw/glfw)
- [Glad](https://github.com/Dav1dde/glad)
- [glm](https://github.com/g-truc/glm)
- [ImGui](https://github.com/ocornut/imgui.git)
