# Install libraries (apt only)
echo "Installing required packages..."
sudo apt-get install -y build-essential git
sudo apt-get install -y libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

# Setup raylib library file
echo "Installing raylib library..."
mkdir -p setup
mkdir -p lib
cd setup
git clone https://github.com/raysan5/raylib.git
cd raylib
git fetch
git checkout 5.0
cd src
make PLATFORM=PLATFORM_DESKTOP
cp libraylib.a ../../../lib/