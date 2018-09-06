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
			ActorMovieIMDB(const string& a, const string& m) {
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
			ActorMovieIMDB(const string& a, const string& m, float r, const vector<string>& genr) {
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
			string getActor() const {
				return actor;
			}
			/**
			 *
			 * Set actor name
			 *
			 * @param actor name (string)
			 *
			 */
			void setActor (const string& a) {
				actor = a;
			}

			/**
			 *
			 * Get movie name
			 *
			 * @return movie name (string)
			 *
			 */
			string getMovie() const {
				return movie;
			}
			/**
			 *
			 * Set movie name
			 *
			 * @param movie name (string)
			 *
			 */
			void setMovie (const string& m) {
				movie = m;
			}

			/**
			 *
			 * Get movie rating
			 *
			 * @return movie rating  (double)
			 *
			 */
			double getMovieRating() const {
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
			vector<string> getGenres() const {
				return genres;
			}

			/**
			 *
			 * Set movie genres
			 *
			 * @param movie genres (vector)
			 *
			 */
			void setGenres(const vector<string>& g) {
				genres = g;
			}

	};

} // namespace bridges

#endif
