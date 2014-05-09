#!/usr/bin/make

DEBVERSION := 4.8.4+dfsg
UBVERSION := 0ubuntu18.3~ubuntu12.04.1
TRVERSION := +true1
VERSION := ${DEBVERSION}-${UBVERSION}${TRVERSION}
APPNAME=qt4-x11
SRCDIR=./src
DEBDIR=./debs
APPDIR=${SRCDIR}/${APPNAME}-${VERSION}
TARNAME=${APPDIR}.tar.gz
DSCNAME=${APPNAME}_${VERSION}.dsc
MAINTAINER=mpnolan@truefitness.com
BUILDDIR=${SRCDIR}/${APPNAME}-${DEBVERSION}
#DEBDIR := ${APPDIR}/debian
DEBIAN_TGZ := http://software.truefitness.com/true-qt-webkit/qt4-x11_4.8.4+dfsg-0ubuntu18.3~ubuntu12.04.1${TRVERSION}.debian.tar.gz


getsources: get_debian_tgz get_source_package
all: shownames getsources unpack build repo

shownames:
	@echo packaging ${APPDIR}
	@echo packagename=${APPNAME}
	@echo version=${VERSION}
	@echo dirname=${APPDIR}
	@echo debdir=${DEBDIR}
	@echo srcdir=${SRCDIR}
	@echo dscname=${DSCNAME}
	@echo buildir=${BUILDDIR}	
	@echo debian_tgz=${DEBIAN_TGZ}	
	
unpack:
	@echo dpkg-source ...
	(cd ${SRCDIR}; dpkg-source -x ${DSCNAME})

get_debian_tgz:
	@echo "downloading debian.tar.gz..."
	(cd ${SRCDIR}; wget ${DEBIAN_TGZ})

get_source_package:
	@echo "downloading orig.tar.gz from server..."
	(cd ${SRCDIR}; wget http://software.truefitness.com/true-qt-webkit/qt4-x11_4.8.4+dfsg.orig.tar.xz)

source:
	@echo "creating source package..."
	debuild --no-lintian -S -uc -us -sd

build:
	@echo building...
	( cd ${BUILDDIR}; dpkg-buildpackage -rfakeroot -b -us -uc -j4)

repo:
	@ echo building repository
	@mkdir -p repo/
	cp ${SRCDIR}/*.deb repo/
	(cd repo; dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz)
	
repo-clean:
	rm -rf ${BUILDDIR}
	rm -rf repo 

clean:
	rm -rf ${SRCDIR}/*.deb 
	rm -rf ${BUILDDIR}
	rm -rf repo

		
