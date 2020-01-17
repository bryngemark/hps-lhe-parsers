#!/bin/sh

g++ -g `root-config --cflags` lhetree_SIMP.cc -o lhetree_SIMP.exe `root-config --libs`
#g++ -g -DDEBUG `root-config --cflags` lhetree_SIMP.cc -o lhetree_SIMP.exe `root-config --libs`
g++ -g `root-config --cflags` lhetree_WAB.cc -o lhetree_WAB.exe `root-config --libs`
#g++ -g -DDEBUG `root-config --cflags` lhetree_WAB.cc -o lhetree_WAB.exe `root-config --libs`
