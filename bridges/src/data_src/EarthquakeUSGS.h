#ifndef EARTHQUAKEUSGS_H

#define EARTHQUAKEUSGS_H

#include <string>

using namespace std;

namespace bridges {

class EarthquakeUSGS {
	private:
		double magnitude;		// earthquake magnitude
		double latit;			// earthquake location
		double longit;			// (lat/long)
		string location;		// location of quake
		string title;			// combo info of quake
		string url;				// url for more info
		string time;			// date
	
	public:

		EarthquakeUSGS() {
			this->magnitude = 0.0;
			this->latit = 0.0;
			this->longit = 0.0;
			this->location = "";
			this->title = "";
			this->url = "";
		}
	
		EarthquakeUSGS(double magnitude, double longit, double latit, 
					string location, string title, string url, string time) {
			this->magnitude = magnitude;
			this->time = time;
			this->longit = longit;
			this->latit = latit;
			this->location = location;
			this->title = title;
			this->url = url;
		}

		EarthquakeUSGS(EarthquakeUSGS *eq){
			this->magnitude = eq->magnitude;
			this->latit = eq->latit;
			this->longit = eq->longit;
			this->location = eq->location;
			this->title = eq->getTitle();
			this->url = eq->url;
		}
		
		string getTime() {
			return time;	
		}
		void setTime (string tm) {
				// process tm to convert to a date
			time = tm;
		}
		float getLatit() {
			return this->latit;
		}
		void setLatit(float latit) {
			this->latit = latit;
		}
		float getLongit() {
			return longit;
		}
		void setLongit(float longit) {
			this->longit = longit;
		}
		string getLocation() {
			return location;
		}
		void setLocation(string location) {
			this->location = location;
		}
		string getTitle() {
			return this->title;
		}
		void setTitle(string title) {
			this->title = title;
		}
		string getUrl() {
			return url;
		}
		void setUrl(string url) {
			this->url = url;
		}
		double getMagnitude() {
			return this->magnitude;
		}
		void setMagnitude(double magnitude) {
			this->magnitude = magnitude;
		}
};

} // namespace bridges

#endif
