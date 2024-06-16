#!/bin/bash

REPO_URL="https://github.com/AlRodriguezGar14/generate_class.git"
EXECUTABLE="newClass"
DIR="/tmp/class_generator_alrodriguezgar14"

echo "Installing class generator"
git clone $REPO_URL $DIR
cd $DIR
make

rm /usr/local/bin/$EXECUTABLE
mv $EXECUTABLE /usr/local/bin
cd ..
rm -rf $DIR

echo "Class generator installed"
