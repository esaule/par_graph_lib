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
			mutable int year, month, day,  hour, minu, sec; //calling min minu to bypass a VS macro
			mutable bool date_correct;

#ifdef _WIN32
			//visual studio 2017 has not yet adopted the posix gmtime_r but has its platform specific gmtime_s.
			//this function converts the call (though drops error handling)
			void gmtime_r(time_t* eq_time, struct tm *eqt) const {
				gmtime_s(eqt, eq_time);
			}
#endif

			/**
			 *  Gets the epoch time of the quake - used internally to get
			 *	actual date - year, month, day, etc
			 *
			 */
			void getDate () const {
				if (date_correct)
					return;
				// get eq's epoch time
				string s = getTime();

				long epoch_time = std::stol(getTime());
				time_t eq_time = epoch_time / 1000;

				// convert to time_t

				struct tm reqt;
				struct tm *eqt = &reqt;
				gmtime_r(&eq_time, eqt);

				year = eqt->tm_year + 1900;
				month = eqt->tm_mon;
				day = eqt->tm_mday;
				hour = eqt->tm_hour;
				sec = eqt->tm_sec;
				minu = eqt->tm_min;

				date_correct = true;
			}

		public:

			EarthquakeUSGS()
				: magnitude(0.0), latit(0.0), longit(0.0),
				  location(""), title(""), url(""), time(""),
				  year(0), month(0), day(0), hour(0), minu(0), sec(0),
				  date_correct(false) {
			}

			EarthquakeUSGS(double magnitude, double longit, double latit,
				const string& location, const string& title, const string& url, const string& time)
				: magnitude(magnitude), latit(latit), longit(longit),
				  location(location), title(title), url(url), time(time),
				  year(0), month(0), day(0), hour(0), minu(0), sec(0),
				  date_correct(false) {
			}

			EarthquakeUSGS(const EarthquakeUSGS *eq)
				: magnitude(eq->magnitude), latit(eq->latit), longit(eq->longit),
				  location(eq->location), title(eq->title), url(eq->url), time(eq->time),
				  year(0), month(0), day(0), hour(0), minu(0), sec(0),
				  date_correct(false) {
			}

			/**
			 *  return the epoch time of the quake
			 *
			 *  @return string
			 */

			string getTime() const {
				return time;
			}


			/**
			 *	returns the real date in a string format
			 *
			 *  @return  string
			 */
			string getDateStr() const {
				getDate();
				string mstr;

				switch (month) {
					case 0 :
						mstr = "Jan. ";
						break;
					case 1 :
						mstr = "Feb. ";
						break;
					case 2 :
						mstr = "Mar. ";
						break;
					case 3 :
						mstr = "Apr. ";
						break;
					case 4 :
						mstr = "May ";
						break;
					case 5 :
						mstr = "Jun. ";
						break;
					case 6 :
						mstr = "Jul. ";
						break;
					case 7 :
						mstr = "Aug. ";
						break;
					case 8 :
						mstr = "Sept. ";
						break;
					case 9 :
						mstr = "Oct. ";
						break;
					case 10 :
						mstr = "Nov. ";
						break;
					case 11 :
						mstr = "Dec. ";
						break;
					default :
						mstr = "???. ";
						break;
				}

				// put into a string
				string date_str = "  " + mstr + to_string(day) + "  " + to_string(year) +
					"  " + to_string(hour) + ":" + to_string(minu) + ":" + to_string(sec);

				return date_str;
			}

			/**
			 *	set epoch time
			 *
			 *	@param tm (string)
			 *
			 */
			void setTime (const string& tm) {
				// process tm to convert to a date
				time = tm;
				date_correct = false;
			}

			/**
			 *	get year of quake
			 *
			 *	@return (int)
			 *
			 */
			int getYear() const {
				getDate();

				return year;
			}
			/**
			 *	get month of quake
			 *
			 *	@return (int)
			 *
			 */
			int getMonth() const {
				getDate();

				return month;
			}
			/**
			 *	get day of quake
			 *
			 *	@return (int)
			 *
			 */
			int getDay() const {
				getDate();

				return day;
			}
			/**
			 *	get hour of quake
			 *
			 *	@return (int)
			 *
			 */
			int getHour() const {
				getDate();

				return hour;
			}
			/**
			 *	get minutes of quake
			 *
			 *	@return (int)
			 *
			 */
			int getMinutes() const {
				getDate();

				return minu;
			}
			/**
			 *	get seconds of quake
			 *
			 *	@return (int)
			 *
			 */
			int getSeconds() const {
				getDate();

				return sec;
			}

			/**
			 *	get latitude of quake
			 *
			 *	@return (float)
			 *
			 */
			float getLatit() const {
				return (float) this->latit;
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
			float getLongit() const {
				return (float) longit;
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
			string getLocation() const {
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
			string getTitle() const {
				return this->title;
			}
			/**
			 *	set quake title (string)
			 *
			 *	@param (string)
			 *
			 */
			void setTitle(const string& title) {
				this->title = title;
			}
			/**
			 *	get quake url
			 *
			 *	@return (string)
			 *
			 */
			string getUrl() const {
				return url;
			}
			/**
			 *	set quake url (string)
			 *
			 *	@param (string)
			 *
			 */
			void setUrl(const string& url) {
				this->url = url;
			}
			/**
			 *	get quake magnitude
			 *
			 *	@return (double)
			 *
			 */
			double getMagnitude() const {
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
