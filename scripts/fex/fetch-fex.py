#!/usr/bin/env python3
# The aarch64 core runs the 32-bit x86 loader and game through FEX-Emu, which
# needs an i386 root file system for the libraries the loader's AppDir does
# not carry (glibc first of all). This fetches both into <out>:
#   <out>/fex         FEX and FEXServer (Ubuntu 22.04 arm64, from FEX's PPA)
#   <out>/fex-rootfs  libc6, libuuid1 and libwayland-client0 for i386, from
#                     Ubuntu 22.04, the release the loader's AppDir is built on
# Package versions come from the archives' indexes, so a security update does
# not break the download. Needs dpkg-deb.
import gzip, io, os, shutil, subprocess, sys, tempfile, urllib.request

PPA = 'https://ppa.launchpadcontent.net/fex-emu/fex/ubuntu'
UBUNTU = 'http://archive.ubuntu.com/ubuntu'
FEX_PACKAGE = 'fex-emu-armv8.0'  # the build for every ARMv8 CPU
I386 = ['libc6', 'libuuid1', 'libwayland-client0']


def packages(base, dist, arch):
    url = f'{base}/dists/{dist}/main/binary-{arch}/Packages.gz'
    text = gzip.decompress(urllib.request.urlopen(url, timeout=120).read()).decode('utf-8', 'replace')
    found = {}
    for block in text.split('\n\n'):
        fields = dict(line.split(': ', 1) for line in block.splitlines() if ': ' in line and not line.startswith(' '))
        if 'Package' in fields and 'Filename' in fields:
            found[fields['Package']] = fields['Filename']
    return found


def extract(base, filename, dest):
    with tempfile.NamedTemporaryFile(suffix='.deb') as deb:
        deb.write(urllib.request.urlopen(f'{base}/{filename}', timeout=300).read())
        deb.flush()
        subprocess.run(['dpkg-deb', '-x', deb.name, dest], check=True)
    print('fetched', filename)


out = sys.argv[1]
os.makedirs(out, exist_ok=True)

ppa = packages(PPA, 'jammy', 'arm64')
with tempfile.TemporaryDirectory() as tmp:
    extract(PPA, ppa[FEX_PACKAGE], tmp)
    os.makedirs(f'{out}/fex', exist_ok=True)
    for name in ('FEX', 'FEXServer'):
        shutil.copy2(f'{tmp}/usr/bin/{name}', f'{out}/fex/{name}')

rootfs = f'{out}/fex-rootfs'
os.makedirs(rootfs, exist_ok=True)
updates = packages(UBUNTU, 'jammy-updates', 'i386')
release = packages(UBUNTU, 'jammy', 'i386')
for name in I386:
    extract(UBUNTU, updates.get(name) or release[name], rootfs)
