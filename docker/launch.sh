#!/bin/bash

docker run -it -v $PWD:/cub3d -v /tmp/.X11-unix:/tmp/.X11-unix -v ~/.local/bin:/root/.local/bin -e DISPLAY=$DISPLAY --privileged cub3d
