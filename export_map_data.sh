#!/bin/zsh

./data.py maze_map.png | cut -d "=" -f2 > map_data
