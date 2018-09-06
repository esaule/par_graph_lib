#ifndef BRIDGES_H
#define BRIDGES_H

#include <iostream>

#include "DataStructure.h" //string, using std
#include "ServerComm.h" //vector

namespace bridges {
	/**
	 * @brief This class contains methods to connect and transmit a user's
	 *  data structure representation to the Bridges server (up to 5000 elements)
	 *
	 * @author Kalpathi Subramanian
	 * @date  7/26/15
	 */
	namespace Bridges {
		/**
		 *	@return flag indicating if JSON should be printed upon visualization
		 */
		static bool jsonFlag = false;
		bool& visualizeJSON() {
			return jsonFlag;;
		}

		void visualizeJSON(bool flag) {
			jsonFlag = flag;
		}

		/**
		 *	@return reference to member holding the username credential
		 *	for the server
		 */
		string& userName() {
			static string user;
			return user;
		}
		/**
		 *	@return Reference to member holding the api key credential for
		 *	the server
		 */
		string& apiKey() {
			static string key;
			return key;
		}
		/**
		 *	@return Reference to member holding the assignment number for
		 *	holding the visualization on the server
		 */
		unsigned int& assignment() {
			static unsigned int num = 0;
			return num;
		}
		/**
		 *	@return title of visualization
		 */
		static string title;

		string& getTitle() {
			return title;
		}

		/**
		 *	Set  title of visualization
		 *
		 *  @param title string t
		 */
		void setTitle(string t) {
			title = t;
		}
		/**
		 *	@return descr description of visualization
		 */
		static string description;

		string& getDescription() {
			return description;
		}
		/**
		 *	@return descr description of visualization
		 */
		void setDescription(string descr) {
			description = descr;
		}

		static int array_dims[3];
		/**
		 *	set dimensions of array
		 *
		 *  @param  dims
		 */
		void setDimensions(int *dims) {
			array_dims[0] = dims[0];
			array_dims[1] = dims[1];
			array_dims[2] = dims[2];
		}

		/**
		 *  set handle to data structure
		 *
		 *  @param ds_ptr Data Structure pointer
		 */
		static DataStructure* handle = nullptr;
		void setDataStructure(DataStructure *ds) {
			handle = ds;
		}

		/**
		 *  @return Reference to member holding the data structure handle
		 */
		DataStructure*& getDataStructure() {
			return handle;
		}

		/**
		 * Sets Bridges assignment to "num", api key to "api" and username
		 *	to "name".
		 *
		 * @param num  The assignment number
		 * @param api The API key
		 * @param user The username
		 */
		void initialize(const unsigned int& num, const string& name,
			const string& api_key) {
			assignment() = num;
			userName() = name;
			apiKey() = api_key;
		}
		/**
		 * Sends relevant data handle information to the server, and
		 * upon successful completion, prints the URL to display the
		 * Bridges visualization.
		 */
		void visualize() {
			static unsigned int lastAssign = 0, part = 0;
			static const string BASE_URL = "http://bridges-cs.herokuapp.com/assignments/";

			if (assignment() != lastAssign) {
				lastAssign = assignment();  // resets part if different using assignment number
				part = 0;
			}
			if (part == 99) {
				cout << "Visualization has been performed maximum number of times for this assignment, no action taken.." << endl; // rollover will occur
				return;
			}
			if (!handle) {
				cerr << "Error: visualizer called with a nullptr data structure... visualization not generated.";
				return;
			}

			string ds_type = handle->getDStype();
			string ds_json = OPEN_CURLY +
				QUOTE + "version"     + QUOTE + COLON + QUOTE + "0.4.0"
				+ QUOTE + COMMA +
				QUOTE + "visual"      + QUOTE + COLON + QUOTE + ds_type
				+ QUOTE + COMMA +
				QUOTE + "title"       + QUOTE + COLON + QUOTE + getTitle()
				+ QUOTE + COMMA +
				QUOTE + "description" + QUOTE + COLON + QUOTE +
				getDescription() + QUOTE + COMMA;
			// for arrays, must pass dimensions
			if (ds_type == "Array") {
				// write dimensions
				ds_json += QUOTE + "dims" 	+ QUOTE + COLON +
					OPEN_BOX +
					to_string(array_dims[0]) + COMMA +
					to_string(array_dims[1]) + COMMA +
					to_string(array_dims[2]) +
					CLOSE_BOX + COMMA;
			}

			ds_json +=  QUOTE + "nodes"  + QUOTE + COLON;

			const pair<string, string> json_nodes_links =
				handle->getDataStructureRepresentation();
			// check if the data structure is a tree,
			// in which case the json contains a hierarchical
			// representation that contains both nodes and
			// links integrated
			if  (ds_type == "Tree" || ds_type == "BinaryTree" ||
				ds_type == "BinarySearchTree" || ds_type == "AVLTree" ) {
				ds_json += json_nodes_links.first + CLOSE_CURLY;
			}
			else {
				ds_json += "[" + json_nodes_links.first + "]" + COMMA + QUOTE + "links" + QUOTE
					+ COLON + "[" + json_nodes_links.second + "]" + CLOSE_CURLY;
			}

			if (visualizeJSON()) {
				cout << "JSON String:\t" << ds_json << endl;
			}

			try {
				ServerComm::makeRequest(BASE_URL + to_string(assignment()) + "." + (part > 9 ? "" : "0") + to_string(part) + "?apikey=" + apiKey(), {"Content-Type: application/json"}, ds_json);
				cout << "Success: Assignment posted to the server. " << endl << "Check out your visualization at:" << endl << endl
					<< BASE_URL + to_string(assignment()) + "/" + userName() << endl << endl;
				part++;
			}
			catch (const string& error_str) {
				cerr << "Posting assignment to the server failed!" << endl << error_str << endl << "Generated JSON: " << ds_json << endl;
			}
		}
	}//end of Bridges namespace
}// end of bridges namespace
#endif
