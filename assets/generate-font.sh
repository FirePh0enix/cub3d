#!/bin/sh

LABEL=" !\"#$\\%\\&'()*+,0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\\\]^_\`abcdefghijklmnopqrtuvwxyz{|}~"

convert -font JetBrainsMono-Regular.ttf -pointsize 72 label:"$LABEL" JetBrainsMono-Regular.ppm
