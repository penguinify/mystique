# Makes a zip for the release of the project and outputs to dist

# Remove old dist
rm -rf dist/*

# build
cmake .
cmake --build .

# make directories
mkdir ./dist/ml/
mkdir ./dist/ml/models/

# copy other files
cp ./src/ml/classify.py ./dist/ml/classify.py
cp ./src/ml/models/model.pkl ./dist/ml/models/model.pkl

# move the executable
mv ./mystique ./dist/mystique

# zip
cd dist
zip -r mystique.zip ./*
