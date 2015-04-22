#!/bin/bash
#this script changes the .ppm files in the current directory to .jpeg 
#just call the script in the directory with the .ppm files
for picture in ../results/*.ppm
do
pnmtojpeg "${picture}" > "${picture/%ppm/jpg}"
done
#rm ../results/*.ppm
