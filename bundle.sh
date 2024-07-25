mkdir -vp release/PWC
cp -vrpu assets release/PWC/assets
cp -vpu PWC release/PWC/PWC
cd release
zip -vr PWC.zip *