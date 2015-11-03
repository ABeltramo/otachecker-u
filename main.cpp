/*
 *	https://github.com/ABeltramo/otachecker-u
 *
 *	The MIT License (MIT)
 *
 *	Copyright (c) 2015 Alessandro Beltramo
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */

#include "PlistCpp/Plist.hpp"
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>    // std::sort
#include <curl/curl.h>
#include <getopt.h>
#include <sstream>	// make url simple

using namespace std;

/***********************************
 * CURL HELPERS
 ***********************************/
string data; // Contain the download result

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up){	// Helper function needed to download content
    for (int c = 0; c<size*nmemb; c++){
        data.push_back(buf[c]);
    }
    return size*nmemb; 							// Tell curl how many bytes we handled
}

string getRemote(const char *URL){
	data = "";
	CURL* curl;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, URL);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
	curl_easy_perform(curl);
	return data;
}

void downloadFile(const char * URL, const char * resultFile){		// Take a URL and create a file with data inside
	getRemote(URL);
	//Saving to file
	ofstream plist;
  	plist.open (resultFile);
	plist << data;
	plist.close();
}

/************************************/

string versionSearch = "";
string deviceSearch = "";

void findSignignOTA(map<string, boost::any>& dict, string device){
	const map<string, boost::any>& dictionary = boost::any_cast<const map<string, boost::any>& >(dict.find(device)->second);//Get the device dictionary
	const vector<boost::any>& firmwares = boost::any_cast<const vector<boost::any>& >(dictionary.find("firmwares")->second);//Get the firmwares vector
	cout << "[ "<< device << " ] Signign fw: " << endl;
	for(vector<boost::any>::const_iterator it = firmwares.begin(); it != firmwares.end(); ++it){
		map<string, boost::any> firmDict = boost::any_cast<const map<string, boost::any> >(*it); 			//Get the dict inside the vector
		bool signing = boost::any_cast<bool>(firmDict["signing"]);
		if(!signing)
			continue;
		try {
			double version = boost::any_cast<double>(firmDict["version"]);						// Sometimes it's a double
			cout << version << endl;
			std::ostringstream url;
			url << "http://api.ipsw.me/v2.1/" << device << "/" << version << "/url";
			cout << "IPSW URL: " << getRemote(url.str().c_str()) << endl;	
		}
		catch (const std::exception& e){
			string version = boost::any_cast<string>(firmDict["version"]);						// Sometimes it's a string
			cout << version << endl;
			std::ostringstream url;
			url << "http://api.ipsw.me/v2.1/" << device << "/" << version << "/url";
			cout << "IPSW URL: " << getRemote(url.str().c_str()) << endl;	
		}
	}
}

void findOTA(map<string, boost::any>& dict){
	const vector<boost::any>& plistArray = boost::any_cast<const vector<boost::any>& >(dict.find("Assets")->second); 	//Get the main vector from plist
	for(vector<boost::any>::const_iterator it = plistArray.begin(); it != plistArray.end(); ++it){
		map<string, boost::any> dictionary = boost::any_cast<const map<string, boost::any> >(*it); 			//Get the dict inside the vector
		string version = boost::any_cast<const string>(dictionary["OSVersion"]);
		if(version == versionSearch ) {											//If this is the searching version
			const vector<boost::any>& devices = boost::any_cast<const vector<boost::any>& >(dictionary.find("SupportedDevices")->second);
			for(vector<boost::any>::const_iterator it = devices.begin(); it != devices.end(); ++it){		//Search the device in the array
				string device = boost::any_cast<const string>(*it);
				if(device == deviceSearch){									//Found IT! Just print.
					string URL =  boost::any_cast<const string>(dictionary["__BaseURL"]);
					URL +=  boost::any_cast<const string>(dictionary["__RelativePath"]);
					cout << "Device: " << deviceSearch << endl << "Version: " << versionSearch << endl << "OTA URL:" << URL << endl;
					return;
				}
			}
		}
	}
	cout << "Device: " << deviceSearch << endl << "Version: " << versionSearch << endl << "Not found." << endl;		//End of Plist, not found
}


string firstNumberstring(string const & str){				// Helper function: return the string before the first number
  size_t const n = str.find_first_of("0123456789");
  if (n != string::npos){
    return str.substr(0, n-1);
  }
  return string();
}

void printOtas(map<string, boost::any>& dict){
	map<string,vector<string> > results;
	cout << "Apple currently signs following ota firmwares" << endl;
	const vector<boost::any>& plistArray = boost::any_cast<const vector<boost::any>& >(dict.find("Assets")->second); //Get the main vector from plist
	for(vector<boost::any>::const_iterator it = plistArray.begin(); it != plistArray.end(); ++it){ 			//Searching for AllowableOTA key
		map<string, boost::any> dictionary = boost::any_cast<const map<string, boost::any> >(*it); 		//Get the dict inside the vector
		if(dictionary.count("AllowableOTA") > 0 && !boost::any_cast<bool>(dictionary["AllowableOTA"])) 
			continue;											//Skipping the AllowableOTA = False entries
		string version = boost::any_cast<const string>(dictionary["OSVersion"]);
		vector<string> dev;
		if(results.count(version) > 0)										//Already encounter this version
			dev = results[version];
		
		const vector<boost::any>& devices = boost::any_cast<const vector<boost::any>& >(dictionary.find("SupportedDevices")->second);
		for(vector<boost::any>::const_iterator it = devices.begin(); it != devices.end(); ++it){		// Print all the devices
			string device = boost::any_cast<const string>(*it);
			if(find(dev.begin(),dev.end(),device) == dev.end())						// If it's not already there
				dev.push_back(device);									// Push it back!
		}
		results[version] = dev; 										// Save it back
	}														// Ending research. Print the map
	for(map<string,vector<string> >::iterator it = results.begin(); it != results.end(); ++it){
		vector<string> curRis = it->second;
		sort(curRis.begin(),curRis.end());									// Ordering the devices
		cout << "[iOS " << it->first << " ]" << endl;
		string prevDevice = curRis[0];										// Variable to decide when to print new line
		for(vector<string>::iterator device = curRis.begin(); device != curRis.end(); ++device){
			if(firstNumberstring(prevDevice) != firstNumberstring(*device))					// Found a new device!
				cout << endl;										// Print a new line
			cout << *device << " ";
			prevDevice = *device;										// Update the prevDevice
		}		
		cout << endl << endl;
	}
}

void printHelp(){							// Just printing wich arguments it need
	cout << "otachecker: [-d device] [-i version] [-s]" << endl;
	cout << "default (no args): shows what ota firmware is signed for which devices" << endl;
	cout << "	-h:	Show this help" << endl;
	cout << "	-d:	Specify wich device you wan't to search" << endl;
	cout << "	-v:	Specify the version of the firmware" << endl;
	cout << "	-s:	Used with -d and -v to find the latest signign ipsw firmware and the relative download URL" << endl;
	cout << endl;
}

int main(int argc, char **argv){
	if (argc == 1) {
		cout << " *Downloading latest plist from Apple.com*" << endl;
		downloadFile("http://mesu.apple.com/assets/com_apple_MobileAsset_SoftwareUpdate/com_apple_MobileAsset_SoftwareUpdate.xml", "mobileAssets.xml");		
		map<string, boost::any> dict; 
		Plist::readPlist("mobileAssets.xml", dict);
		printOtas(dict);
	}

	bool searchSigned = false;
	int c;
	while ((c = getopt (argc, argv, "shd:v:")) != -1){ //Read the argument passed
    		switch (c){
			case 'h':
            			printHelp();
            		break;
			case 'd':
            			deviceSearch = optarg;
            		break;
			case 'v':
            			versionSearch = optarg;
            		break;
			case 's':
				searchSigned = true;
			break;
			case '?':
			default:
				cout << "*Invalid argument passed.*" << endl;
				printHelp();
				exit(1);
			break;
				
		}
	}
	if(deviceSearch != "" && versionSearch != ""){	// Arguments passed correctly
		cout << endl << " *Downloading latest plist from Apple.com*" << endl;
		downloadFile("http://mesu.apple.com/assets/com_apple_MobileAsset_SoftwareUpdate/com_apple_MobileAsset_SoftwareUpdate.xml", "mobileAssets.xml");
		map<string, boost::any> dict; 				//Reading the plist
		Plist::readPlist("mobileAssets.xml", dict);
		findOTA(dict);
		if(searchSigned){
			cout << endl <<  " *Downloading signign firmware for " << deviceSearch << " from http://api.ineal.me*" << endl;
			downloadFile(("http://api.ineal.me/tss/" + deviceSearch + "/plist").c_str(), "apiIneal.xml");
			Plist::readPlist("apiIneal.xml", dict);
			findSignignOTA(dict,deviceSearch);
			remove("apiIneal.xml"); 		// Delete the file
		}
	}
	remove("mobileAssets.xml"); 				// Delete the file	
	cout << endl << "Developed by: ABeltramo - Based on tihmstar source - Upon an idea of GenHack" << endl << endl;
	
}
