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

using namespace std;

string versionSearch = "";
string deviceSearch = "";

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
		for(vector<string>::iterator device = curRis.begin(); device != curRis.end(); ++device){
			cout << *device << " ";
		}		
		cout << endl << endl;
	}
}

bool cpequal(const char *a, const char *b, int length){			//Helper function for argc,argv
	for(int i=0;i<length; i++)
		if(a[i] != b[i])
			return false;
	return true;
}

string data; // Contain the download plist file

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up){	//Helper function needed to download content
    for (int c = 0; c<size*nmemb; c++){
        data.push_back(buf[c]);
    }
    return size*nmemb; 							//tell curl how many bytes we handled
}

int main(int argc, const char * argv[]){
	cout << "Downloading latest plist from Apple.com" << endl;
	CURL* curl;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "http://mesu.apple.com/assets/com_apple_MobileAsset_SoftwareUpdate/com_apple_MobileAsset_SoftwareUpdate.xml");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
	curl_easy_perform(curl);
	//Saving to file
	ofstream plist;
  	plist.open ("mobileAssets.xml");
	plist << data;
	plist.close();
	//Reading the plist
	map<string, boost::any> dict; 
	Plist::readPlist("mobileAssets.xml", dict);

	if (argc == 1) {
            printOtas(dict);
        }
	else{
		//Read the argument passed
		for (int i = 1; i < argc; i++) {
			if (cpequal(argv[i],"-d",2)){
				deviceSearch = argv[i+1];
				i++;
			}
			else if(cpequal(argv[i],"-v",2)){
				versionSearch = argv[i+1];
				i++;
			}
		}
		findOTA(dict);
	}
	cout << endl << "Developed by: ABeltramo - Based on tihmstar Source - Upon and idea of GenHack" << endl;
	remove("mobileAssets.xml"); // Delete the file
}
