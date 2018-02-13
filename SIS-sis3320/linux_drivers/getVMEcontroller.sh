cd
mkdir WIENER
cd WIENER
wget https://iseg-hv.com/download/SOFTWARE/isegVMEcontrol/current/isegVmeControl-ubuntu64-1.0.8.7.zip
unzip isegVmeControl-ubuntu64-1.0.8.7.zip
cd isegVmeControl-ubuntu64-1.0.8.7
if ! ldconfig -p | grep qt-sdk; then
  sudo apt-get install qt-sdk
fi
sudo mv libxx_usb.so /usr/lib
