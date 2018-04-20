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
	 * @author Kalpathi Subramanian, Dakota Carmer
	 * @date  7/26/15, 6/5/17
	 */
	namespace Bridges {
		// static variables used in Bridges

		static bool jsonFlag = false;   	// if JSON is to be printed
		static string user_name = string(), api_key = string(); // user credentials
		static unsigned int assn_num = 0;	// assignment id
		static int array_dims[3] = {0, 0, 0};
		static DataStructure* ds_handle = nullptr;  // data structure handle
		static string server_url = "http://bridges-cs.herokuapp.com";

		/**
		 *	@return flag indicating if JSON should be printed upon visualization
		 */

		bool& getVisualizeJSONFlag() {
			return jsonFlag;;
		}

		void setVisualizeJSONFlag(bool flag) {
			jsonFlag = flag;
		}

		/**
		 *	@return reference to member holding the username credential
		 *	for the server
		 */
		string& getUserName() {
			return user_name;
		}
		/**
		 *	@param  user_name   user id to set
		 */
		void setUserName(string name) {
			user_name = name;
		}
		/**
		 *	@return Reference to member holding the api key credential for
		 *	the server
		 */
		string& getApiKey() {
			return api_key;
		}
		/**
		 *	@param k API key to set for user
		 */
		void setApiKey(string k) {
			api_key = k;
		}
		/**
		 *	@return Reference to member holding the assignment number for
		 *	holding the visualization on the server
		 */
		unsigned int& getAssignment() {
			return assn_num;
		}
		/**
		 *	@param assn sets the assignment number
		 */
		void setAssignment(unsigned int num) {
			assn_num =  num;
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
		 *  @param ds_ptr pointer to user's data Structure
		 */
		void setDataStructure(DataStructure *ds) {
			ds_handle = ds;
		}

		/**
		 *  @return Reference to member holding the data structure handle
		 */
		DataStructure*& getDataStructure() {
			return ds_handle;
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
			const string& key) {
			assn_num = num;
			user_name = name;
			api_key = key;
		}
		/**
		 *
		 *  @param  server server to which to connect.
		 *      Options are: ['live', 'local', 'clone'], and 'live' is the default;
		 *
		 */
		void setServer(string server_type) {
			if (server_type == "live")
				server_url = "http://bridges-cs.herokuapp.com";
			else if (server_type == "clone")
				server_url = "http://bridges-clone.herokuapp.com";
			else if (server_type == "local") 
				server_url = "http://127.0.0.1:3000";
		}

		/**
		 * Sends relevant data handle information to the server, and
		 * upon successful completion, prints the URL to display the
		 * Bridges visualization.
		 */
		void visualize() {
			static unsigned int lastAssign = 0, part = 0;
			static const string BASE_URL = server_url + "/assignments/";

			if (assn_num != lastAssign) { 		// reset if a new assignment
				lastAssign = assn_num;
				part = 0;
			}
			if (part == 99) {
				cout << "#sub-assignments limit(99) exceeded, visualization not generated .."
					<< endl;
				return;
			}
			if (!ds_handle) {
				cerr << "Error: Data Structure handle null! Visualization not generated.";
				return;
			}

			// generate the JSON of the data structure

			string ds_type = ds_handle->getDStype();
			string ds_json = OPEN_CURLY +
				QUOTE + "visual" + QUOTE + COLON + QUOTE + ds_type + QUOTE + COMMA +
				QUOTE + "title" + QUOTE + COLON + QUOTE + getTitle() + QUOTE + COMMA +
				QUOTE + "description" + QUOTE + COLON + QUOTE + getDescription() + QUOTE + COMMA +
				QUOTE + "coord_system_type" + QUOTE + COLON + QUOTE + "Cartesian" + QUOTE + COMMA;

			// for arrays, must pass dimensions
			if (ds_type == "Array") {
				// get dimensions
				// write dimensions
				ds_json += QUOTE + "dims" + QUOTE + COLON +
					OPEN_BOX +
					to_string(array_dims[0]) + COMMA +
					to_string(array_dims[1]) + COMMA +
					to_string(array_dims[2]) +
					CLOSE_BOX + COMMA;
			}


			//
			// get the nodes and link representations
			//

			ds_json +=  QUOTE + "nodes"  + QUOTE + COLON;
			const pair<string, string> json_nodes_links =
				ds_handle->getDataStructureRepresentation();

			//
			// for tree structures, get a hierarchical JSON representation
			// of the nodes and links
			//
			if  (ds_type == "Tree" || ds_type == "BinaryTree" ||
				ds_type == "BinarySearchTree" || ds_type == "AVLTree" ) {
				ds_json += json_nodes_links.first + CLOSE_CURLY;
			}
			else {
				ds_json += OPEN_BOX + json_nodes_links.first + CLOSE_BOX + COMMA +
					QUOTE + "links" + QUOTE + COLON + OPEN_BOX + json_nodes_links.second + CLOSE_BOX +
					CLOSE_CURLY;
			}

			//
			// print JSON if flag is on
			//
			if (getVisualizeJSONFlag()) {
				cout << "JSON String:\t" << ds_json << endl;
			}

			try {
				ServerComm::makeRequest(BASE_URL + to_string(assn_num) + "." +
					(part > 9 ? "" : "0") + to_string(part) + "?apikey=" + api_key,
				{"Content-Type: application/json"}, ds_json);
				cout << "Success: Assignment posted to the server. " << endl <<
					"Check out your visualization at:" << endl << endl
					<< BASE_URL + to_string(assn_num) + "/" + user_name << endl << endl;
				part++;
			}
			catch (const string& error_str) {
				cerr << "\nPosting assignment to the server failed!" << endl 
					<< error_str << endl << endl;
				cerr << "Provided Bridges Credentials:" << endl <<
						"\t User Name: " << user_name << endl <<
						"\t API Key: " << api_key << endl <<
						"\t Assignment Number: " << assn_num << endl;
			}
		}
	}	//end of Bridges namespace


}	// end of bridges namespace
#endif
