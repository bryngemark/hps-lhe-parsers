#!/bin/sh

g++ -g `root-config --cflags` lhetree_SIMP.cc -o lhetree_SIMP.exe `root-config --libs`
#g++ -g -DDEBUG `root-config --cflags` lhetree_SIMP.cc -o lhetree_SIMP.exe `root-config --libs`
g++ -g `root-config --cflags` lhetree_WAB.cc -o lhetree_WAB.exe `root-config --libs`
#g++ -g -DDEBUG `root-config --cflags` lhetree_WAB.cc -o lhetree_WAB.exe `root-config --libs`
g++ -g `root-config --cflags` lhetree_TriTrig.cc -o lhetree_TriTrig.exe `root-config --libs`
#g++ -g -DDEBUG `root-config --cflags` lhetree_TriTrig.cc -o lhetree_TriTrig.exe `root-config --libs`
g++ -g `root-config --cflags` lhetree_Ap.cc -o lhetree_Ap.exe `root-config --libs`
#g++ -g -DDEBUG `root-config --cflags` lhetree_Ap.cc -o lhetree_Ap.exe `root-config --libs`
g++ -g `root-config --cflags` lhetree_Ap_to_ee.cc -o lhetree_Ap_to_ee.exe `root-config --libs`
#g++ -g -DDEBUG `root-config --cflags` lhetree_Ap_to_ee.cc -o lhetree_Ap_to_ee.exe `root-config --libs`
g++ -g `root-config --cflags` lhetree_Rad.cc -o lhetree_Rad.exe `root-config --libs`
#g++ -g -DDEBUG `root-config --cflags` lhetree_Rad.cc -o lhetree_Rad.exe `root-config --libs`
