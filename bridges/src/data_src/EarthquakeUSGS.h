#ifndef EARTHQUAKEUSGS_H

#define EARTHQUAKEUSGS_H

#include <string>

using namespace std;

namespace bridges {
/**
 * @brief  Class that hold earthquake data, for use with USGIS retrieved quake data.
 *
 * Class that holds earthquake USGIS data. BRIDGES uses scripts to continually monitor
 * USGIS site (tweets) and retrieve the latest quake data for use in student projects.
 *
 * Kalpathi Subramanian, 2/18/18
 */


	class EarthquakeUSGS {
		private:
			double magnitude;		// earthquake magnitude
			double latit;			// earthquake location
			double longit;			// (lat/long)
			string location;		// location of quake
			string title;			// combo info of quake
			string url;				// url for more info
			string time;				// date

									// access by date
			int year, month, day,  hour, min, sec;

			/**
			 *  Gets the epoch time of the quake - used internally to get
			 *	actual date - year, month, day, etc
			 *
			 */
			void getDate () {
								// get eq's epoch time
				string s = getTime();

				long epoch_time = std::stol(getTime());
				time_t eq_time = epoch_time/1000;

								// convert to time_t 
				
				struct tm *eqt = gmtime(&eq_time);

				year = eqt->tm_year + 1900;
				month = eqt->tm_mon;
				day = eqt->tm_mday;
				hour = eqt->tm_hour;
				sec = eqt->tm_sec;
				min = eqt->tm_min;
			}

		public:

			EarthquakeUSGS() {
				this->magnitude = 0.0;
				this->latit = 0.0;
				this->longit = 0.0;
				this->location = "";
				this->title = "";
				this->url = "";
				this->time = "";
				this->year = this->month = this->day = this->hour =
					this->min = this->sec = 0;
				
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
				this->time = time;
			}

			EarthquakeUSGS(EarthquakeUSGS *eq) {
				this->magnitude = eq->magnitude;
				this->latit = eq->latit;
				this->longit = eq->longit;
				this->location = eq->location;
				this->title = eq->getTitle();
				this->url = eq->url;
				this->time = eq->time;
			}

			/**
			 *  return the epoch time of the quake
			 *
			 *  @return string
			 */

			string getTime() {
				return time;
			}
			

			/** 
			 *	returns the real date in a string format
			 *
			 *  @return  string
			 */
			string getDateStr() {
				getDate();
				string mstr;

				switch (month) {
					case 0 : mstr = "Jan. "; break;
					case 1 : mstr = "Feb. "; break;
					case 2 : mstr = "Mar. "; break;
					case 3 : mstr = "Apr. "; break;
					case 4 : mstr = "May "; break;
					case 5 : mstr = "Jun. "; break;
					case 6 : mstr = "Jul. "; break;
					case 7 : mstr = "Aug. "; break;
					case 8 : mstr = "Sept. "; break;
					case 9 : mstr = "Oct. "; break;
					case 10 : mstr = "Nov. "; break;
					case 11 : mstr = "Dec. "; break;
				}

						// put into a string
				string date_str = "  " + mstr+ to_string(day) + "  " + to_string(year) +
					"  " + to_string(hour)+":"+to_string(min)+":" + to_string(sec);

				return date_str;
			}
					
			/** 
			 *	set epoch time 
			 * 
			 *	@param tm (string)
			 *
			 */
			void setTime (string tm) {
				// process tm to convert to a date
				time = tm;
			}

			/** 
			 *	get year of quake
			 * 
			 *	@return (int)
			 *
			 */
			int getYear() {
				getDate();

				return year;
			}
			/** 
			 *	get month of quake
			 * 
			 *	@return (int)
			 *
			 */
			int getMonth() {
				getDate();

				return month;
			}
			/** 
			 *	get day of quake
			 * 
			 *	@return (int)
			 *
			 */
			int getDay() {
				getDate();

				return day;
			}
			/** 
			 *	get hour of quake
			 * 
			 *	@return (int)
			 *
			 */
			int getHour() {
				getDate();

				return hour;
			}
			/** 
			 *	get minutes of quake
			 * 
			 *	@return (int)
			 *
			 */
			int getMinutes() {
				getDate();

				return min;
			}
			/** 
			 *	get seconds of quake
			 * 
			 *	@return (int)
			 *
			 */
			int getSeconds() {
				getDate();

				return sec;
			}
				
			/** 
			 *	get latitude of quake
			 * 
			 *	@return (float)
			 *
			 */
			float getLatit() {
				return this->latit;
			}
			/** 
			 *	set latitude
			 * 
			 *	@param (float)
			 *
			 */
			void setLatit(float latit) {
				this->latit = latit;
			}
			/** 
			 *	get longitude of quake location
			 * 
			 *	@return (float)
			 *
			 */
			float getLongit() {
				return longit;
			}
			/** 
			 *	set longitude of quake location
			 * 
			 *	@param (float)
			 *
			 */
			void setLongit(float longit) {
				this->longit = longit;
			}
			/** 
			 *	get quake location
			 * 
			 *	@return (string)
			 *
			 */
			string getLocation() {
				return location;
			}
			/** 
			 *	set quake location (string)
			 * 
			 *	@param (string)
			 *
			 */
			void setLocation(string location) {
				this->location = location;
			}
			/** 
			 *	get quake title
			 * 
			 *	@return (string)
			 *
			 */
			string getTitle() {
				return this->title;
			}
			/** 
			 *	set quake title (string)
			 * 
			 *	@param (string)
			 *
			 */
			void setTitle(string title) {
				this->title = title;
			}
			/** 
			 *	get quake url
			 * 
			 *	@return (string)
			 *
			 */
			string getUrl() {
				return url;
			}
			/** 
			 *	set quake url (string)
			 * 
			 *	@param (string)
			 *
			 */
			void setUrl(string url) {
				this->url = url;
			}
			/** 
			 *	get quake magnitude
			 * 
			 *	@return (double)
			 *
			 */
			double getMagnitude() {
				return this->magnitude;
			}
			/** 
			 *	set quake magnitude (double)
			 * 
			 *	@param (string)
			 *
			 */
			void setMagnitude(double magnitude) {
				this->magnitude = magnitude;
			}
	};

} // namespace bridges

#endif
