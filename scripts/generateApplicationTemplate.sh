#!/bin/sh

if [ $# == 0 ]; then
    echo "Usage: ./generateApplicationTemplate.sh destination"
    exit
fi

make clean
mkdir $1
rsync -avr --exclude='.git' ./ $1/
rm -rf $1/src/game/*
cp res/templates/template_main.c $1/src/game/
