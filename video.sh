#!/bin/bash

ffmpeg -framerate 2 -pattern_type glob  -i 'plot/*.png'  -c:v libx264 out.mp4
