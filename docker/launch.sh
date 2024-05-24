#!/bin/bash

docker run -it -v $PWD:/cub3d -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY --privileged cub3d
