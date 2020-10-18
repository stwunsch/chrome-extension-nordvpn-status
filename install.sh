#!/bin/bash

# Compile the native host application, which queries 'nordvpn status'
c++ app.cxx -o app
chmod u+x app

# Register the app with chrome
# NOTE: The install path may differ based on your system
INSTALL_PATH=$HOME/.config/chromium/NativeMessagingHosts
FILE=com.stwunsch.nordvpn_status.json
THIS_PWD=$(pwd)
cp $FILE $INSTALL_PATH
cd $INSTALL_PATH
sed -i s,PATH_TO_HOST_APP,$THIS_PWD, $FILE
