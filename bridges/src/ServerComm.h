#ifndef SERVER_COMM_H
#define SERVER_COMM_H

#include <string>
#include <vector>
using namespace std;
#include <curl/curl.h> //curl
#include "./data_src/EarthquakeUSGS.h"
#include "./data_src/Game.h"
#include "./data_src/Shakespeare.h"
#include "./data_src/GutenbergBook.h"
#include "./data_src/CancerIncidence.h"
#include "./data_src/ActorMovieIMDB.h"

namespace bridges {
	namespace DataSource {
		vector<Game> getGameData();
		vector<EarthquakeUSGS> getEarthquakeData(int);
		vector<Shakespeare> getShakespeareData(string, bool);
		vector<GutenbergBook> getGutenbergBookData(int);
		vector<CancerIncidence> getCancerIncidenceData(int);
		vector<ActorMovieIMDB> getActorMovieIMDBData(int);
		vector<ActorMovieIMDB> getActorMovieIMDBData2(int);
		
	}
	/**
	 *	@brief This is a detail class for the Bridges namespace and
	 *			is not intended for external use
	 */
	class ServerComm {
			//Used to access to this class private functions
			friend void Bridges::visualize();
			friend vector<Game> DataSource::getGameData();
			friend vector<EarthquakeUSGS> DataSource::getEarthquakeData(int);
			friend vector<Shakespeare> DataSource::getShakespeareData(string, bool);
			friend vector<GutenbergBook> DataSource::getGutenbergBookData(int);
			friend vector<CancerIncidence> DataSource::getCancerIncidenceData(int);
			friend vector<ActorMovieIMDB> DataSource::getActorMovieIMDBData(int);
			friend vector<ActorMovieIMDB> DataSource::getActorMovieIMDBData2(int);

			ServerComm() = delete; //Prevents instantiation

			/** CURL WRITE FUNCTION PLACEHOLDER (TODO - Replace with something
			 * 		better)
			 */
			static size_t curlWriteFunction(void *contents, size_t size,
				size_t nmemb, void *results) {
				size_t handled = size * nmemb;
				if (results) {
					((string*)results)->append((char*)contents);
				}
				return handled;
			}
			/**
			 * Uses Easy CURL library to execute a simple request.
			 *
			 * @param url The url destination for the request
			 * @param headers The headers for the request
			 * @param data The content sent in POST requests
			 * @throw string Thrown if curl request fails
			 */
			static string makeRequest(const string& url, const vector<string>&
				headers, const string& data = "") {
				string results;
				// first load curl enviornment (only need be called
				// once in entire session tho)
				curl_global_init(CURL_GLOBAL_ALL);
				CURL* curl = curl_easy_init(); // get a curl handle
				if (curl) {
					// set the URL to GET from
					curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
					//pass pointer to callback function
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, &results);
					//sends all data to this function
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunction);
									// need this to catch http errors
					curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
					if (data.length() > 0) {
						// Now specify the POST data
						curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
						// Now specify the POST data size
						curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length());
						//  a post request
						curl_easy_setopt(curl, CURLOPT_POST, true);
					}

					struct curl_slist* curlHeaders = nullptr;
					for (const string& header : headers) {
						curlHeaders = curl_slist_append(curlHeaders, header.c_str());
					}
					curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);

					// Perform the request, res will get the return code
					CURLcode res = curl_easy_perform(curl);

					if (res != CURLE_OK) {
						throw "curl_easy_perform() failed.\nCurl Error Code "
						+ to_string(res) + "\n" + curl_easy_strerror(res) + 
						"\n" + "Possibly Bad BRIDGES Credentials\n";
					}
					curl_easy_cleanup(curl);
				}
				else {
					throw "curl_easy_init() failed!\nNothing retrieved from server.\n";
				}

				return results;
			}
	}; //server comm


}// namespace bridges
#endif
