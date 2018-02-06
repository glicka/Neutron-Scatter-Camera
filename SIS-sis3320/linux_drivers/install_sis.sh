#! /bin/bash
<<<<<<< HEAD
=======

>>>>>>> e4aa30a799dc65d13d18cfeef2e707f0cfd0a7a0
if [[ $EUID -ne 0 ]]; then
  echo "This script must be run as root" 1>&2
  exit 1
fi

# Get users in order to run this script as multiple users
USER_LIST=`users`
stringarray=($USER_LIST)
NON_ROOT_USER=${stringarray[0]}

# Env for running as a different user
RUNAS="sudo -u $NON_ROOT_USER"

# Get ubuntu version
VERSION_STRING=`lsb_release -r`
VERSION=${VERSION_STRING//[A-Z:a]/}
SISDIR=$HOME/SIS
PERMISSION_FILE=/etc/udev/rules.d/60-sis3150.rules
CURDIR=`pwd`
<<<<<<< HEAD
if [ $VERSION == "12.04" ] || [ $VERSION == "14.04" ]|| [ $VERSION == "16.04" ]|| [ $VERSION == "18" ]|| [ $VERSION == "18.2" ]; then
  # Unpack the SIS tar
  #  message = dpkg -l libusb-dev
    PKG_OK=$(dpkg-query -W --showformat='${Status}\n' libusb-dev|grep "install ok installed")
    echo Checking for libusb: $PKG_OK
    if [ "" == "$PKG_OK" ]; then
      echo "No libusb-dev. Setting up libusb-dev."
      sudo apt-get --force-yes --yes install libusb-dev
    else
      echo "libusb-dev found."
      echo "moving on"
    fi
=======

if [ $VERSION == "12.04" ] || [ $VERSION == "14.04" ]|| [ $VERSION == "16.04" ]|| [ $VERSION == "18" ]; then
  # Unpack the SIS tar
>>>>>>> e4aa30a799dc65d13d18cfeef2e707f0cfd0a7a0
  $RUNAS bash<<___
  mkdir $SISDIR
  tar -C $SISDIR -xzf sisusb-1.2-003.tar.gz
___
  # Preparation for 14.04 version - install usb backward compatibility
<<<<<<< HEAD
  if [ $VERSION == "14.04" ] || [ $VERSION == "16.04" ]|| [ $VERSION == "18" ] || [ $VERSION == "18.2" ]; then
=======
  if [ $VERSION == "14.04" ] || [ $VERSION == "16.04" ]|| [ $VERSION == "18" ]; then
>>>>>>> e4aa30a799dc65d13d18cfeef2e707f0cfd0a7a0
    ./install_usb_compat.sh
  fi

$RUNAS bash<<___
  # Configure the build
  cd $SISDIR/sisusb-1.2-003
<<<<<<< HEAD

  if [ $VERSION == "14.04" ] || [ $VERSION == "16.04" ]|| [ $VERSION == "18" ] || [ $VERSION == "18.2" ]; then
=======
  if [ $VERSION == "14.04" ] || [ $VERSION == "18" ]; then
>>>>>>> e4aa30a799dc65d13d18cfeef2e707f0cfd0a7a0
    ./configure --prefix=$SISDIR --with-usb-headerdir=/usr/local/include --with-usb-libdir=/usr/local/lib --with-tcl-libdir=/usr/lib/x86_64-linux-gnu/ --with-tcl-header-dir=/usr/include/tcl8.5/
  else
   ./configure --prefix=$SISDIR --with-usb-headerdir=/usr/include --with-usb-libdir=/lib/x86_64-linux-gnu
  fi
  # A couple config changes necessary for linking
  sed -i 's/LIBS = -ldl/LIBS = -ldl -lusb/g' loader/apps/Makefile
  sed -i 's/LIBS = -ldl/LIBS = -ldl -lusb/g' hotplug/Makefile
  # Build and install
  make
  make install
___
  # Setup permissions
  cat <<EOM >$PERMISSION_FILE
SUBSYSTEM=="usb", ATTR{idVendor}=="1657", ATTR{idProduct}=="3150", MODE="0777"
EOM

cd $CURDIR

else
  echo "Detected Ubuntu Version: $VERSION"
<<<<<<< HEAD
  echo "Add your version to install_sis.sh on lines 23, 30, and 37."
=======
  echo "install_sis.sh only works for ubuntu 12.04"
>>>>>>> e4aa30a799dc65d13d18cfeef2e707f0cfd0a7a0
  echo "Exiting..."
fi
