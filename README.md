otachecker-u [![Build Status](https://travis-ci.org/ABeltramo/otachecker-u.svg?branch=master)](https://travis-ci.org/ABeltramo/otachecker-u) [![license: MIT](https://img.shields.io/badge/License-MIT-lightgrey.svg)](https://opensource.org/licenses/MIT)
==========

Otachecker written in pure C++ for any Operating System

Usage
-------

*An internet connection is required to download the plist from Apple server*

	otachecker [-d deviceName -v iOSVersion [-s] ]

If you call it without any argument the result will be all the current OTA's Apple allow

[![asciicast](https://asciinema.org/a/OpSfatjP8qMyiY7BUq01xqkVR.png)](https://asciinema.org/a/OpSfatjP8qMyiY7BUq01xqkVR?speed=2)
	
If you specify what device (-d) and what version (-v) the result will be the OTA URL where you can download it  

[![asciicast](https://asciinema.org/a/df59N057v65JOj9BRZeJbxoYm.png)](https://asciinema.org/a/df59N057v65JOj9BRZeJbxoYm?speed=2)

If you also add the -s argument the result will also include the latest signign firmware from Apple for the specified device and the URL where you can download the latest IPSW
Using:  
[api.ineal.me](http://api.ineal.me/)  
[api.ipsw.me](http://api.ipsw.me/)

[![asciicast](https://asciinema.org/a/0OXqAaVXYo5tCrnLkaDhMNK7u.png)](https://asciinema.org/a/0OXqAaVXYo5tCrnLkaDhMNK7u?speed=2)

How to compile
-------
The makefile it's only tested in Linux.
You need first to install boost and curl library:

	apt-get install libboost-dev libcurl-dev

Then you can start compiling

	make

You can also find already compiled version of otachecker in the [release](https://github.com/ABeltramo/otachecker-u/releases) tab

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

