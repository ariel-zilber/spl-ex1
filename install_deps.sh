#!/bin/bash

sudo apt update;
sudo apt-get install python3-dev python3-setuptools -y;
sudo apt-get install libtiff5-dev libjpeg8-dev libopenjp2-7-dev zlib1g-dev -y;
sudo apt-get install ibfreetype6-dev liblcms2-dev libwebp-dev tcl8.6-dev tk8.6-dev python3-tk -y;
sudo apt-get install libharfbuzz-dev libfribidi-dev libxcb1-dev -y;
sudo apt-get install python3-pip -y;
pip3 install networkx -y;
pip3 install matplotlib -y;