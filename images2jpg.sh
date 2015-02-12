#!/bin/bash
#this script changes the .ppm files in the current directory to .jpeg 
#just call the script in the directory with the .ppm files
for picture in *.ppm
do
pnmtojpeg "${picture}" > "${picture/%ppm/jpg}"
done
rm *.ppm
