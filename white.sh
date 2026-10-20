#!/bin/zsh

# if [ "$EUID" -ne 0 ]; then
#     echo "Please run as root"
#     exit
# fi

make keychron/k8_pro/ansi/white:coravacav
sudo mkdir -p /share/qmkbuild
sudo cp keychron_k8_pro_ansi_white_coravacav.bin /share/qmkbuild
