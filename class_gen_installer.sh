#!/bin/bash

REPO_URL = "https://github.com/AlRodriguezGar14/generate_class.git class_generator"
EXECUTABLE = "class_generator"
DIR = "/tmp/class_generator_alrodriguezgar14"

git clone $REPO_URL $DIR
cd DIR
make

mv $EXECUTABLE /usr/local/bin
cd ..
rm -rf $DIR
