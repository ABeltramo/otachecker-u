otachecker-u
==========

Otachecker written in pure C++ for any Operating System

Usage
-------

*An internet connection is required to download the plist from Apple server*  
If you call it without any argument the result will be all the current OTA's Apple allow

	bin/otachecker

	[...]
	[iOS 8.3 ]
	AppleTV3,1 AppleTV3,2 

	[iOS 8.4.1 ]
	iPad2,1 iPad2,2 iPad2,3 iPad2,4 iPad2,5 iPad2,6 iPad2,7 iPad3,1 iPad3,2 iPad3,3 iPad3,4 iPad3,5 iPad3,6 
	iPhone4,1 iPhone5,1 iPhone5,2 
	iPod5,1 

	[iOS 9.1 ]
	iPad2,1 iPad2,2 iPad2,3 iPad2,4 iPad2,5 iPad2,6 iPad2,7 iPad3,1 iPad3,2 iPad3,3 iPad3,4 iPad3,5 iPad3,6 iPad4,1 iPad4,2 iPad4,3 iPad4,4 iPad4,5 iPad4,6 iPad4,7 iPad4,8 iPad4,9 iPad5,1 iPad5,2 iPad5,3 iPad5,4 iPad6,7 iPad6,8 
	iPhone4,1 iPhone5,1 iPhone5,2 iPhone5,3 iPhone5,4 iPhone6,1 iPhone6,2 iPhone7,1 iPhone7,2 iPhone8,1 iPhone8,2 
	iPod5,1 iPod7,1 
	[...]
	
If you specify what device (-d) and what version (-v) the result will be the OTA URL where you can download it  
	
	bin/otachecker -d iPhone4,1 -v 6.1.3
	
	*Downloading latest plist from Apple.com*
	Device: iPhone4,1
	Version: 6.1.3
	OTA URL:http://appldnld.apple.com/iOS6.1/091-3360.20130311.BmfR4/com_apple_MobileAsset_SoftwareUpdate/82b056c7a9e455ad4f00d1b5169e5b56ab8c2cc7.zip

If you also add the -s argument the result will also include the latest signign firmware from Apple for the specified device and the URL where you can download the latest IPSW
Using:  
[api.ineal.me](http://api.ineal.me/)  
[api.ipsw.me](http://api.ipsw.me/)

	bin/otachecker -d iPhone4,1 -v 6.1.3 -s

	 *Downloading latest plist from Apple.com*
	Device: iPhone4,1
	Version: 6.1.3
	OTA URL:http://appldnld.apple.com/iOS6.1/091-3360.20130311.BmfR4/com_apple_MobileAsset_SoftwareUpdate/82b056c7a9e455ad4f00d1b5169e5b56ab8c2cc7.zip

	 *Downloading signign firmware for iPhone4,1 from http://api.ineal.me*
	[ iPhone4,1 ] Signign fw: 
	9.1
	IPSW URL: http://appldnld.apple.com/ios9.1/031-41357-20151021-866B88C4-73FC-11E5-91CE-6B7443DA716B/iPhone4,1_9.1_13B143_Restore.ipsw


How to compile
-------
The makefile it's only tested in Linux.
You need first to install boost and curl library:

	apt-get install libboost-dev libcurl-dev

Then you can start compiling

	make

An already compiled version is present in bin directory

Credits
-------
Developed by: ABeltramo  
Based on [tihmstar](https://github.com/tihmstar) [Source](https://github.com/tihmstar/otachecker)  
Upon an idea of [GenHack](https://github.com/genhack)  
Using [PlistCpp](https://github.com/animetrics/PlistCpp), [Boost](http://www.boost.org/) and [Curl](http://curl.haxx.se/)

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

