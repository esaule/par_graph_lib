#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include <vector>
#include <string>
using namespace std;

#include <rapidjson/document.h>
#include "ServerComm.h"
#include "./data_src/EarthquakeUSGS.h"
#include "./data_src/Game.h"
#include "./data_src/Shakespeare.h"
#include "./data_src/GutenbergBook.h"
#include "./data_src/CancerIncidence.h"
#include "./data_src/ActorMovieIMDB.h"
#include "./data_src/Song.h"


namespace bridges {
	/**
	 * @brief This provides an API to various data sources used in BRIDGES.
	 *
	 * BRIDGES currently supports a few external datasets for use with BRIDGES
	 * assignments: USGIS Earthquake Tweeet streaming data feed, IMDB (file),
	 * Book metadata collection, IGN Game Data, Shakespear book/poem meta data.

	 * Functions are provided that access a user specified number of data
	 * records; objects of the appropriate type are returned as a list.
	 *
	 */

	namespace DataSource {

		/**
		 *
		 *  Get meta data of the IGN games collection.
		 *
		 *  This function retrieves  and formats the data into a list of
		 *  Game objects
		 *
		 *  @throws Exception if the request fails
		 *
		 *  @return a list of Game objects,
		 *
		 */
		vector<Game> getGameData() {
			using namespace rapidjson;
			Document d;

			// request the game dataset and parse it
			d.Parse(
				ServerComm::makeRequest(
					"http://bridgesdata.herokuapp.com/api/games",
			{"Accept: application/json"}).c_str()
			);

			const Value& D = d["data"];
			vector<Game> wrapper;
			for (SizeType i = 0; i < D.Size(); i++) {
				const Value& V = D[i];
				const Value& G = V["genre"];

				vector<string> genre;
				for (SizeType j = 0; j < G.Size(); j++) {
					genre.push_back(G[j].GetString());
				}
				wrapper.push_back(
					Game(	V["game"].GetString(),
						V["platform"].GetString(),
						V["rating"].GetDouble(),
						genre ) );
			}
			return wrapper;
		}
		/**
		 *  Get ActorMovie IMDB Data
		 *  retrieved, formatted into a list of ActorMovieIMDB objects
		 *
		 *  @param number the number of actor/movie pairs, but currently unused,
		 *      returns all records.
		 *  @throws Exception if the request fails
		 *
		 *  @return a list of ActorMovieIMDB objects, but only actor and
		 *			movie fields in this version
		 */
		vector<ActorMovieIMDB> getActorMovieIMDBData(int number = 0) {
			using namespace rapidjson;
			Document d;
			vector<ActorMovieIMDB> wrapper;
			string url = "http://bridgesdata.herokuapp.com/api/imdb?limit=" +
				to_string(number);

			// retrieve the data and parse
			d.Parse(ServerComm::makeRequest( url,
			{"Accept: application/json"}).c_str());

			const Value& D = d["data"];
			for (SizeType i = 0; i < D.Size(); i++) {
				const Value& V = D[i];
				wrapper.push_back(
					ActorMovieIMDB(
						V["actor"].GetString(),
						V["movie"].GetString()
					)
				);
			}
			return wrapper;
		}


		/**
		 *  Get ActorMovie IMDB Data
		 *  retrieved, formatted into a list of ActorMovieIMDB objects
		 *
		 *  @throws Exception if the request fails
		 *
		 *  @return a list of ActorMovieIMDB objects, consisting of
		 *	actor name, movie name, movie genre and movie rating is returned.
		 *
		 */
		vector<ActorMovieIMDB> getActorMovieIMDBData2() {
			using namespace rapidjson;
			Document d;
			vector<ActorMovieIMDB> wrapper;
			string url = "https://bridgesdata.herokuapp.com/api/imdb2";

			// retrieve the data and parse
			d.Parse(ServerComm::makeRequest( url,
			{"Accept: application/json"}).c_str());

			const Value& D = d["data"];
			for (SizeType i = 0; i < D.Size(); i++) {
				const Value& V = D[i];
				string actor = V["actor"].GetString();
				string movie = V["movie"].GetString();
				double rating = V["rating"].GetDouble();
				const Value& G = V["genres"];
				vector<string> genres;
				for (SizeType j = 0; j < G.Size(); j++) {
					genres.push_back(G[j].GetString());
				}
				wrapper.push_back(ActorMovieIMDB( actor, movie, (float)rating, genres));
			}
			return wrapper;
		}

		/**
		 *  Get USGS earthquake data
		 *  USGS Tweet data (https://earthquake.usgs.gov/earthquakes/map/)
		 *  retrieved, formatted into a list of EarthquakeUSGS objects
		 *
		 *  @param number the number of earthquake records retrieved,
		 *		limited to 5000
		 *  @throws Exception if the request fails
		 *
		 *  @return a list of earthquake records
		 */
		vector<EarthquakeUSGS> getEarthquakeUSGSData(int number = 0) {
			using namespace rapidjson;
			Document d;
			vector<EarthquakeUSGS> wrapper;
			if (number <= 0) {
				d.Parse(ServerComm::makeRequest(
						"http://earthquakes-uncc.herokuapp.com/eq",
				{"Accept: application/json"}).c_str());
				for (SizeType i = 0; i < d.Size(); i++) {
					const Value& V = d[i]["properties"];
					const Value& G = d[i]["geometry"]["coordinates"];
					wrapper.push_back(
						EarthquakeUSGS(
							V["mag"].GetDouble(),
							G[0].GetDouble(),
							G[1].GetDouble(),
							V["place"].GetString(),
							V["title"].GetString(),
							V["url"].GetString(),
							V["time"].GetString() )
					);
				}
			}
			else {
				d.Parse(ServerComm::makeRequest(
						"http://earthquakes-uncc.herokuapp.com/eq/latest/" +
						to_string(number), {"Accept: application/json"}).c_str());
				const Value& D = d["Earthquakes"];
				for (SizeType i = 0; i < D.Size(); i++) {
					const Value& V = D[i]["properties"];
					const Value& G = D[i]["geometry"]["coordinates"];
					//				wrapper.push_back({V["mag"].GetDouble(),G[0].GetDouble(),G[1].GetDouble(),V["place"].GetString(),V["title"].GetString(),V["url"].GetString(),V["time"].GetString()});
					wrapper.push_back(
						EarthquakeUSGS(
							V["mag"].GetDouble(),
							G[0].GetDouble(),
							G[1].GetDouble(),
							V["place"].GetString(),
							V["title"].GetString(),
							V["url"].GetString(),
							V["time"].GetString() )
					);
				}
			}
			return wrapper;
		}
		/**
		 *
		 *  Get data of Shakespeare works (plays, poems)
		 *
		 *  This function retrieves  and formats the data into a
		 *  a list of Shakespeare objects.
		 *
		 *	Valid endpoints: 'poems','plays', <title>
		 *	Valid queryParams: format{simple}
		 *
		 *  @throws Exception if the request fails
		 *
		 *  @param endpoint  can be either "plays" or "poems". If this is
		 *		specified, then only these types of works are retrieved.
		 *  @param textOnly  if this is set, then only the text is retrieved.
		 *
		 *  @return an array of Shakespeare objects
		 *
		 */
		vector<Shakespeare> getShakespeareData(string endpoint = "",
			bool textonly = false) {
			using namespace rapidjson;
			Document d;
			vector<Shakespeare> wrapper;

			string url =
				"http://bridgesdata.herokuapp.com/api/shakespeare/";

			if (endpoint == "plays" || endpoint == "poems")
				url += "/" + endpoint;
			if (textonly) {
				url += "?format=simple";
			}
			// retrieve the data and parse
			d.Parse(ServerComm::makeRequest( url,
			{"Accept: application/json"}).c_str());

			const Value& D = d["data"];
			for (SizeType i = 0; i < D.Size(); i++) {
				const Value& V = D[i];
				wrapper.push_back(
					Shakespeare(
						V["title"].GetString(),
						V["type"].GetString(),
						V["text"].GetString()
					)
				);

			}
			return wrapper;
		}
		/**
		 *
		 *  Get data of a particular songs (including lyrics) using the Genius API
		 *  (https://docs.genius.com/), given the song title and artist name.
		 *	Valid endpoints:  http://bridgesdata.herokuapp.com/api/songs/find/
		 *	Valid queryParams: song title, artist name
		 *
		 *  This function retrieves  and formats the data into a
		 *  Song object. The song if not cached in the local DB is queried
		 *  and added to the DB
		 *
		 *  @throws Exception if the request fails
		 *
		 *  @return a Song object,
		 *
		 */
		Song getSong(string songTitle, string artistName) {
			using namespace rapidjson;

			Document d;
			vector<Song> wrapper;
			string url = "http://bridgesdata.herokuapp.com/api/songs/find/";
			// retrieve the data and parse
			if (songTitle.size())
				url += songTitle;
			else {
				// need to throw an exception or something
			}
			if (artistName.size())
				url += "?artistName=" + artistName;
			else {
				// need to throw an exception or something
			}
			// check for spaces in url and replace them by '%20'
			string::size_type n = 0;
			while ( (n = url.find(" ", n)) != string::npos) {
				url.replace(n, 1, "%20");
				n++;
			}

			d.Parse(ServerComm::makeRequest( url,
			{"Accept: application/json"}).c_str());

			string artist 	= (d.HasMember("artist")) ?
				d["artist"].GetString() : string();
			string song 	= (d.HasMember("song"))	?
				d["song"].GetString() : string();
			string album 	= (d.HasMember("album"))	?
				d["album"].GetString() : string();
			string lyrics 	= (d.HasMember("lyrics")) ?
				d["lyrics"].GetString() : string();
			string release_date = (d.HasMember("release_date")) ?
				d["release_date"].GetString() : string();

			return Song (artist, song, album, lyrics, release_date);
		}
		/**
		 *
		 *  Get data of the songs (including lyrics) using the Genius API
		 *  https://docs.genius.com/
		 *	Valid endpoints:  https://bridgesdata.herokuapp.com/api/songs/
		 *
		 *  This function retrieves  and formats the data into a list of
		 *  Song objects. This version of the API retrieves all the cached
		 *  songs in the local DB.
		 *
		 *  @throws Exception if the request fails
		 *
		 *  @return a list of Song objects,
		 *
		 */
		vector<Song> getSongData() {
			using namespace rapidjson;

			Document d;
			vector<Song> all_songs;

			string url = "http://bridgesdata.herokuapp.com/api/songs/";
			// retrieve the data and parse

			d.Parse(ServerComm::makeRequest( url,
			{"Accept: application/json"}).c_str());


			const Value& D = d["data"];

			// get the songs and put them into a vector
			for (SizeType i = 0; i < D.Size(); i++) {
				const Value& v = D[i];

				//cout << v["artist"].GetString() << endl;
				string artist 	= (v.HasMember("artist")) ? v["artist"].GetString() : string();
				string song 	= (v.HasMember("song"))	? v["song"].GetString() : string();
				string album 	= (v.HasMember("album"))	? v["album"].GetString() : string();
				string lyrics 	= (v.HasMember("lyrics")) ? v["lyrics"].GetString() : string();
				string release_date = (v.HasMember("release_date")) ?
					v["release_date"].GetString() : string();
				all_songs.push_back( Song ( artist, song, album, lyrics, release_date) );

			}
			return all_songs;
		}
		/**
		 *
		 *  Get meta data of the Gutenberg book collection (1000 books)
		 *  This function retrieves,  and formats the data into a list of
		 *  GutenbergBook objects
		 *
		 *  @throws Exception if the request fails
		 *
		 *  @return a list of GutenbergBook objects,
		 *
		 */
		vector<GutenbergBook> getGutenbergBookData(int num = 0) {
			using namespace rapidjson;

			Document d;
			vector<GutenbergBook> wrapper;
			string url = "http://bridgesdata.herokuapp.com/api/books";
			if (num > 0) {
				url += "?limit=" + to_string(num);
			}

			d.Parse(ServerComm::makeRequest(
					url, {"Accept: application/json"}).c_str());
			const Value& D = d["data"];
			for (SizeType i = 0; i < D.Size(); i++) {
				const Value& V = D[i];

				const Value& A = V["author"];
				const Value& L = V["languages"];

				vector<string> lang;
				for (SizeType j = 0; j < L.Size(); j++) {
					lang.push_back(L[j].GetString());
				}

				const Value& G = V["genres"];
				vector<string> genre;
				for (SizeType j = 0; j < G.Size(); j++) {
					genre.push_back(G[j].GetString());
				}

				const Value& S = V["subjects"];
				vector<string> subject;
				for (SizeType j = 0; j < S.Size(); j++) {
					subject.push_back(S[j].GetString());
				}

				const Value& M = V["metrics"];
				wrapper.push_back(
					GutenbergBook(
						A["name"].GetString(),
						A["birth"].GetInt(),
						A["death"].GetInt(),
						V["title"].GetString(),
						lang,
						genre,
						subject,
						M["characters"].GetInt(),
						M["words"].GetInt(),
						M["sentences"].GetInt(),
						M["difficultWords"].GetInt(),
						V["url"].GetString(),
						V["downloads"].GetInt()
					)
				);
			}
			return wrapper;
		}
		/*
		 * Retrieves the CDC dataset into a vector of records
		 * See CancerIncidence class for more information
		 *
		 */
		vector<CancerIncidence> getCancerIncidenceData(int num = 0) {
			using namespace rapidjson;

			Document d;
			vector<CancerIncidence> wrapper;
			string url =
				"https://bridgesdata.herokuapp.com/api/cancer/withlocations";
			if (num > 0) {
				url += "?limit=" + to_string(num);
			}

			d.Parse(ServerComm::makeRequest(
					url, {"Accept: application/json"}).c_str());

			// get the JSON dataset
			const Value& D = d["data"];

			CancerIncidence c;
			for (SizeType i = 0; i < D.Size(); i++) {
				const Value& v = D[i];
				const Value& age = v["Age"];

				c.setAgeAdjustedRate( age["Age Adjusted Rate"].GetDouble());
				c.setAgeAdjustedCI_Lower(age["Age Adjusted CI Lower"].GetDouble());
				c.setAgeAdjustedCI_Upper(age["Age Adjusted CI Upper"].GetDouble());

				c.setYear(v["Year"].GetInt());

				const Value& data = v["Data"];
				c.setCrudeRate(data["Crude Rate"].GetDouble());
				c.setCrudeRate_CI_Lower(data["Crude CI Lower"].GetDouble());
				c.setCrudeRate_CI_Upper(data["Crude CI Upper"].GetDouble());
				c.setRace(data["Race"].GetString());
				c.setPopulation(data["Population"].GetInt());
				c.setEventType(data["Event Type"].GetString());

				c.setAffectedArea(v["Area"].GetString());

				const Value& loc = v["loc"];
				c.setLocationX(loc[0].GetDouble());
				c.setLocationY(loc[1].GetDouble());

				wrapper.push_back(c);
			}
			return wrapper;
		}

	} // namespace DataSource

} // namespace bridges
#endif
