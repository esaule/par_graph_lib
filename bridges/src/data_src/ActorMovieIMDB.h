#ifndef IMDB_H

#define IMDB_H

#include <string>

using namespace std;

namespace bridges {

/**
 *	@brief A class to hold actor movie data -- using IMDB dataset
 *
 *
 *	@author Kalpathi Subramanian
 *	@date 2/18/18
 *
 */

class ActorMovieIMDB {

	private:
		string actor, movie;
		double rating;
		vector<string> genres;

	public:
		ActorMovieIMDB () {
			actor = movie = "";
			rating = 0.0;
		}
	
		/**
	 	 * This method initializes an actor movie object with an actor/movie pair.
		 *
		 *	@param actor  (string)
		 *	@param movie  (string)
	 	 */
		ActorMovieIMDB(string a, string m){
			actor = a;
			movie = m;
			rating = 0.0;
		}


		/**
	 	 * This method initializes an actor movie object with an actor/movie pair.
		 *
		 *	@param actor  (string)
		 *	@param movie  (string)
		 *	@param rating  (float)
		 *	@param genres  (vector)
	 	 */
		ActorMovieIMDB(string a, string m, float r, vector<string> genr){
			actor = a;
			movie = m;
			rating = r;
			genres = genr;
		}

		/**
	 	 *
	 	 * Get actor name
	 	 *
	 	 * @return actor name (string)
	 	 *
	 	 */
		string getActor() {
			return actor;
		}
		/**
	 	 *
	 	 * Set actor name
	 	 *
	 	 * @param actor name (string)
	 	 *
	 	 */
		void setActor (string a) {
			actor = a;
		}

		/**
	 	 *
	 	 * Get movie name
	 	 *
	 	 * @return movie name (string)
	 	 *
	 	 */
		string getMovie() {
			return movie;
		}
		/**
	 	 *
	 	 * Set movie name
	 	 *
	 	 * @param movie name (string)
	 	 *
	 	 */
		void setMovie (string m) {
			movie = m;
		}

		/**
	 	 *
	 	 * Get movie rating
	 	 *
	 	 * @return movie rating  (double)
	 	 *
	 	 */
		double getMovieRating() {
			return rating;
		}

		/**
	 	 *
	 	 * Set movie rating
	 	 *
	 	 * @param movie rating (double)
	 	 *
	 	 */
		void setMovieRating(double r) {
			rating = r;
		}

		/**
	 	 *
	 	 * Get movie genres
	 	 *
	 	 * @return movie genres  (vector)
	 	 *
	 	 */
		vector<string> getGenres() {
			return genres;
		}

		/**
	 	 *
	 	 * Set movie genres
	 	 *
	 	 * @param movie genres (vector)
	 	 *
	 	 */
		void setGenres(vector<string> g) {
			genres = g;
		}
	
	};

} // namespace bridges

#endif
