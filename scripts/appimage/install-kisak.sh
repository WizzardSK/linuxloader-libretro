#!/usr/bin/env bash

# On a GitHub runner: keep its snaps and kernel as they are through the upgrade.
# In a container (the libretro buildbot) there is neither, and nothing to hold.
if command -v snap >/dev/null 2>&1; then
    sudo snap refresh --hold=forever
fi
for pkg in linux-image-$(uname -r) linux-headers-$(uname -r); do
    if dpkg -s "$pkg" >/dev/null 2>&1; then
        sudo apt-mark hold "$pkg"
    fi
done
sudo add-apt-repository ppa:kisak/turtle -y
sudo apt update --allow-unauthenticated -y && sudo apt upgrade -y --allow-unauthenticated
