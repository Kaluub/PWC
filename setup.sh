# Install libraries (Ubuntu)
echo "Installing required packages..."
sudo apt-get update
sudo apt-get install -y build-essential git libasound2-dev libx11-dev \
    libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev \
    libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev \
    emscripten

# Setup raylib library file
echo "Installing raylib library..."
mkdir -p setup
mkdir -p lib
cd setup
git clone https://github.com/raysan5/raylib.git
cd raylib
git fetch
git checkout 8ea5db3ec43d1fa702b29df9066307d0d337b229
cd src
make clean

# Compile raylib for desktop
make PLATFORM=PLATFORM_DESKTOP
cp libraylib.a ../../../lib/
make clean

# Compile raylib for web
make PLATFORM=PLATFORM_WEB
cp libraylib.a ../../../lib/libraylibweb.a
make clean

echo "Done!"