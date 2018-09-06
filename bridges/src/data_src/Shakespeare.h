#ifndef SHAKESPEARE_H

#define SHAKESPEARE_H

#include <string>

using namespace std;

namespace bridges {
	/**
	 * @brief  A Shakespeare book object, used along with the Shakespeare
	 * books  data source.
	 *
	 * This is a convenience class provided for  users who wish to use this
	 *  data source as part of their application. It provides an API that makes
	 *  it easy to access the attributes of this data set.
	 *
	 * Refer to tutorial examples to using this data source in data structure
	 *  assignments.
	 *
	 * @author Kalpathi Subramanian
	 * @date   1/16/17
	 *
	 */


	class Shakespeare {
		private:
			string 	title,			// title of work
					type, 			// play, sonnet, ...
					text;			// content?

		public:
			Shakespeare()
				: title(""), type(""), text("") {
			}
			Shakespeare(const string& title, const string& type, const string& text)
				: title(title), type(type), text(text) {
			}
			string getTitle() const {
				return title;
			}
			void setTitle (const string& title) {
				this->title = title;
			}
			string getType() const {
				return type;
			}
			void setType (const string& type) {
				this->type = type;
			}
			string getText() const {
				return text;
			}
			void setText (const string& text) {
				this->text = text;
			}
	};

} //namespace bridges

#endif
