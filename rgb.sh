#!/bin/zsh

# if [ "$EUID" -ne 0 ]; then
#     echo "Please run as root"
#     exit
# fi

make keychron/k8_pro/ansi/rgb:coravacav
sudo mkdir -p /mnt/fast/qmk
sudo cp keychron_k8_pro_ansi_rgb_coravacav.bin /mnt/fast/qmk
