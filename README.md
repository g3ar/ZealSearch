# ZealSearch
## About
ZealSearch is the [Zeal](http://zealdocs.org/) integration plugin for KTextEditor-based 
editors(Kate, KWrite, KDevelop, Kile, etc).
### Features
- Search selected test in Zeal
- Configurable tying up docset filters to file extensions
## How to install?
Installation process described for Ubuntu 14.04. Required package names and package manager may vary 
depending of your distro.
### Run this command to install a packages required for building the plugin
```
sudo apt-get install git cmake build-essential kdelibs5-dev
```
###Run this commands to clone this repo in `/tmp`, build and install the plugin
You need to change `-DCMAKE_INSTALL_PREFIX:PATH` parameter value from `/usr` to value suitable for your 
distro before running the commands listed below. Ubuntu users can leave this value as is.
```
mkdir /tmp/ZealSearch
cd /tmp/ZealSearch
git clone https://github.com/g3ar/ZealSearch.git
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr -DCMAKE_BUILD_TYPE=Release ../ZealSearch
make
```
Run this for installing the plugin if build completes successfull.
```
sudo make install
```
## Configuration tips
Start Kate after installing. Go to `Settings -> Configure Kate -> Editor Components -> Extensions`. Enable 
ZealSearch. Click configuration button. Here you can change path to zeal binary and tie docset filters to 
file extensions. Click `Defaults` button to see example. You can find more info about zeal docset filters 
[at zeal usage page](http://zealdocs.org/usage.html). 

You can go to `Settings -> Configure Shortcuts` scroll down to `ZealSearch` and bind it to a key.

## Bugs
Developed and tested on Kubuntu 14.04. Still can be buggy. Use github issue tracker to report bugs.

# Have a nice day:)
