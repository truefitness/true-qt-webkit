#!/bin/bash

# note: set DEBFULLNAME, DEBEMAIL in .bashrc prior to running

backportpackage -s saucy -w . -S "+true1" qtwebkit-source

#sudo apt-get build-dep qt4-x11

cd qtwebkit-source-precise
quilt new true-flash-wmode.patch
quilt add src/declarative/qml/qdeclarativedata_p.h 
patch -p6 < ../../true_patches/flash_wmode.patch
quilt refresh
#quilt header -e "message"

#dch -v "4:4.8.4+dfsg-0ubuntu18.1~precise1+true2"

#dpkg-buildpackage -us -uc -j4

# sequence to add a patch and rebuild
#make getsources
#make unpack
#cd qt4-x11-4.8.4+dfsg
#quilt new foo.patch
#quilt add src/foo.cpp
#patch -p0 < some.patch
#quilt refresh
#dch -v "4:4.8.4+dfsg-0ubuntu18.1~precise1+true3"
# edit makefile and bump TRVERSION
#make source
#dpkg-buildpackage -us -uc -j4

