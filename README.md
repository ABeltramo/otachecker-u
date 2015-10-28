otachecker-u
==========

Otachecker written in pure C++ for any Operating System

Usage
-------

*An internet connection is required to download the plist from Apple server*

	build/otachecker

If you call it without any argument the result will be all the current OTA's Apple allow

	build/otachecker -d iPhone4,1 -v 6.1.3
	
	*Downloading latest plist from Apple.com*
	Device: iPhone4,1
	Version: 6.1.3
	OTA URL:http://appldnld.apple.com/iOS6.1/091-3360.20130311.BmfR4/com_apple_MobileAsset_SoftwareUpdate/82b056c7a9e455ad4f00d1b5169e5b56ab8c2cc7.zip
	 *Downloading signign firmware for iPhone4,1 from http://api.ineal.me*
	[ iPhone4,1 ] Signign firmware:
	9.1 9.0.2 


If you specify what device (-d) and what version will return the OTA URL where you can download it and the firmware signed from Apple taken from [api.ineal.me](api.ineal.me)

How to compile
-------
The makefile it's only tested in Linux.
You need first to install boost and curl library:

	apt-get install libboost-dev libcurl-dev

Then you can start compiling

	mkdir obj
	make
An already compiled version is present in build directory

Credits
-------
Developed by: ABeltramo  
Based on [tihmstar](https://github.com/tihmstar) [Source](https://github.com/tihmstar/otachecker)  
Upon an idea of [GenHack](https://github.com/genhack)  
Using [PlistCpp](https://github.com/animetrics/PlistCpp), [Boost](http://www.boost.org/) and [curl](http://curl.haxx.se/)

License
-------
	The MIT License (MIT)

	Copyright (c) 2015 Alessandro Beltramo

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

