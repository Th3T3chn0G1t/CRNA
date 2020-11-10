#!/bin/sh

if [ $# == 0 ]; then
    echo "Usage: ./generateApplicationTemplate.sh destination"
fi

make clean
mkdir $1
rsync -avr --exclude='.git' ./ $1/
cd $1
cd src/game
rm -rf *
