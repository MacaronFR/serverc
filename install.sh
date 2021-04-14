#!/bin/bash
#must run in sudo
if [ "$EUID" -ne 0 ]
	then echo "Please run script as root"
	#exit error
	exit 1
fi
apt install libxml2-dev cmake
#change install dir (default /usr/bin)
read -p "Where install binaries ? (default in /usr/bin/)" bindir
if [ -z "$bindir" ]
then bindir="/usr/bin/"
fi
#cmake command
cmake CMakeLists.txt
#create bin dir if not exist
mkdir -p "$bindir"
#make
make
#move result in bin dir
mv serverc hyperion_xml_saver
mv hyperion_xml_saver "$bindir"
#delete all build file
rm CMakeCache.txt CMakeFiles/ cmake_install.cmake Makefile -R

#########################################
#CREDENTIALS
#########################################
#deposit credentials
read -p "XML saving path (default /var/hyperion/backup/): " xmls
read -p "XML retrieving path (default /var/hyperion/sftp/): " xmlr

if [ -z "$xmls" ]
then xmls="/var/hyperion/backup/"
fi
if [ -z "$xmlr" ]
then xmlr="/var/hyperion/sftp/"
fi

if [ "${xmls: -1}" != "/" ]
then xmls="${xmls}/"
fi
if [ "${xmlr: -1}" != "/" ]
then xmlr="${xmlr}/"
fi
mkdir -p "$xmls"
mkdir -p "$xmlr"

xmldir="[XML]\n${xmlr}\n${xmls}\n\n"

echo -e "\n\nIf you misspelled something, all setup info is in the file located at /etc/hyperion/xml_saver.conf\n\n"

#Write credentials to conf file
mkdir -p "/etc/hyperion"
echo -e "$xmldir" > "/etc/hyperion/xml_saver.conf"

#create cron task

echo "30 00 2 * * hyperion_xml_saver" >> /var/spool/cron/crontabs/root

#exit OK
exit 0
