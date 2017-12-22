#ifndef BOOK_H 

#define BOOK_H
#include <string>
using namespace std;

namespace bridges {
/**
 * @brief  A Book object, used along with the books data source.
 *	
 * This is a convenience class provided for  users who wish to use this
 *	data source as part of their application. It provides an API that makes
 *  it easy to access the attributes of this data set.
 *
 * Refer to tutorial examples to using this data source in data structure
 *  assignments.
 *
 * @author Kalpathi Subramanian
 * @date   1/16/17
 *
 */

class Book {
	string authorName;
	int authorBirth, 
		authorDeath;
	string title;
	vector<string> lang, genre, subject;
	int numChars, numWords, numSentences, numDifficultWords;
	string url;
	int downloads;

	public:
		Book () {
			authorName = title = url = "";
			authorBirth =  authorDeath = 
			numChars = numWords = numSentences = numDifficultWords = 0;
		}
		Book(string authorName, int authorBirth, int authorDeath, 
				string title, vector<string> lang, vector<string> genre,
				vector<string> subject, int numChars, int numWords, 
				int numSentences, int numDifficultWords, string url, 
				int downloads) {

			this->authorName = authorName;
			this->authorBirth = authorBirth;  
			this->authorDeath = authorDeath;
			this->title =  title;
			this->lang = lang;
			this->genre = genre;
			this->subject = subject;
			this->url = url;
			this->numChars = numChars;
			this->numWords = numWords;
			this->numSentences = numSentences;
			this->numDifficultWords = numDifficultWords;
		}

		string getAuthorName() {
			return authorName;
		}
		void setAuthorName(string authorName) {
			this->authorName = authorName;
		}

		int getAuthorBirth() {
			return authorBirth;
		}
		void setAuthorBirth(int authorBirth) {
			this->authorBirth = authorBirth;
		}

		int getAuthorDeath() {
			return authorDeath;
		}
		void setAuthorDeath(int authorDeath) {
			this->authorDeath = authorDeath;
		}

		string getTitle() {
			return title;
		}
		void setTitle(string title) {
			this->title = title;
		}

		vector<string>  getLang() {
			return lang;
		}
		void setLang(vector<string> lang)  {
			this->lang = lang;
		}

		vector<string>  getGenre() {
			return genre;
		}
		void setGenre(vector<string> genre)  {
			this->genre = genre;
		}

		vector<string>  getSubject() {
			return subject;
		}
		void setSubject(vector<string> subject)  {
			this->subject = subject;
		}

		string getURL() {
			return url;
		}
		void setURL(string url) {
			this->url = url;
		}

		int getNumChars() {
			return numChars;;
		}
		void setNumChars(int numChars) {
			this->numChars = numChars;;
		}

		int getNumWords() {
			return numWords;
		}
		void setNumWords(int numWords) {
			this->numWords = numWords;
		}

		int getNumSentences() {
			return numSentences;
		}
		void setNumSentences(int numSentences) {
			this->numSentences = numSentences;
		}

		int getNumDifficultWords() {
			return numDifficultWords;
		}
		void setNumDifficultWords(int numDifficultWords) {
			this->numDifficultWords = numDifficultWords;
		}

};

 
}// namespace bridges

#endif

