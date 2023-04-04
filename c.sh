#!/bin/zsh

# if [ "$EUID" -ne 0 ]; then
#     echo "Please run as root"
#     exit
# fi

/home/mask/.local/bin/qmk compile -kb massdrop/ctrl -km coravacav &&
    sudo rm -rf /share/qmkbuild &&
    sudo mkdir -p /share/qmkbuild &&
    sudo cp massdrop_ctrl_coravacav.bin /share/qmkbuild
