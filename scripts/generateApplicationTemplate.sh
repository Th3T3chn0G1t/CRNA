#!/bin/sh

if [ $# == 0 ]; then
    echo "Usage: $0 <destination>"
    exit
fi

make clean
mkdir $1
rsync -avr --exclude '.git' --exclude 'docs' --exclude 'Doxyfile' --exclude 'CONTRIBUTING.md' --exclude 'tests' --exclude '.travis.yml' --exclude 'LICENCE' ./ $1/
rm -rf $1/src/game/*
cp res/templates/template_main.c $1/src/game/
