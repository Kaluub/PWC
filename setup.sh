# Install libraries (Ubuntu)
echo "Installing required packages..."
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
git checkout efce4d69ce913bca42289184b0bffe4339c0193f
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