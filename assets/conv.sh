#!/bin/bash

convert -flop $1 $2.png
convert $2.png $2 # -flip
rm $2.png
