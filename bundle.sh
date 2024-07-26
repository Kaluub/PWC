mkdir -vp release/PWC
cp -vrpu assets release/PWC/assets
cp -vpu PWC release/PWC/PWC
cp -vpu PWC.exe release/PWC/PWC.exe
cd release
zip -vr PWC.zip *