#ifndef GAME_H

#define GAME_H

#include <string>

using namespace std;

namespace bridges {
	/**
	 * @brief  A Game object, used along with the Games data source.
	 *
	 * This is a convenience class provided for  users who wish to use this
	 * data source as part of their application. It provides an API that makes
	 * it easy to access the attributes of this data set.
	 *
	 * Refer to tutorial examples to using this data source in data structure
	 * assignments.
	 *
	 */


	class Game {
		private:
			string title;			// game
			string platform;		// game platform type
			double rating;			// game rating
			vector<string> genre;	// game type/category

		public:

			Game()
				: title(""), platform(""), rating(0), genre() {
			}

			Game(const string& title, const string& platform, double rating,
				const vector<string>& genre)
				: title(title), platform(platform), rating(rating), genre(genre) {
			}

			string getTitle() const {
				return title;
			}
			void setTitle (const string& title) {
				this->title = title;
			}

			string getPlatformType() const {
				return platform;
			}
			void setPlatformType(const string& platform) {
				this->platform = platform;
			}

			double getRating() const {
				return rating;
			}
			void setRating(double rating) {
				this->rating = rating;
			}
			vector<string> getGameGenre() const {
				return genre;
			}
			void setGameGenre(const vector<string>& genre) {
				this->genre = genre;
			}
	};

} // namespace bridges

#endif
