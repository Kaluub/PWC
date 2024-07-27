# Install libraries (Ubuntu)
echo "Installing required packages..."
sudo apt-get install -y build-essential git libasound2-dev libx11-dev \
    libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev \
    libxcursor-dev libxinerama-dev emscripten

# Setup raylib library file
echo "Installing raylib library..."
mkdir -p setup
mkdir -p lib
cd setup
git clone https://github.com/raysan5/raylib.git
cd raylib
git pull
git checkout 5.0
cd src
make PLATFORM=PLATFORM_DESKTOP
cp libraylib.a ../../../lib/
make clean

# Compile raylib for web
emcc -c rcore.c -O2 -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
emcc -c rshapes.c -O2 -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
emcc -c rtextures.c -O2 -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
emcc -c rtext.c -O2 -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
emcc -c rmodels.c -O2 -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
emcc -c utils.c -O2 -Wall -DPLATFORM_WEB
emcc -c raudio.c -O2 -Wall -DPLATFORM_WEB
emar rcs libraylibweb.a rcore.o rshapes.o rtextures.o rtext.o rmodels.o utils.o raudio.o
cp libraylibweb.a ../../../lib/
rm libraylibweb.a
make clean

echo "Done!"