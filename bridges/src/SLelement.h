#ifndef SLELEMENT_H
#define SLELEMENT_H

#include "DataStructure.h"
#include "Element.h" //string, using std

namespace bridges {
	/**
	 * @brief The singly linked list element, derived from Element
	 *
	 * This class can be used to create singly linked elements, with a next
	 *	SLelement pointer
	 *
	 * Generic Parameters: E the application data type
	 *
	 * @author Kalpathi Subramanian
	 * @date 6/11/15
	 */
	template <typename E>
	class SLelement : public Element<E>, public DataStructure {

		protected:
			SLelement* next = nullptr;

		public:
			/**
			 * 	Constructs an slelement with the provided value, label, and next
			 * 	slelement.
			 * 	The defaults will be used if not provided.
			 *
			 * 	@param val The data to hold
			 * 	@param lab The label to show
			 * 	@param n The next SLelement
			 */
			SLelement(SLelement* n, const E& val = E(), const string& lab =
					string()) : Element<E>(val, lab) {
				setNext(n);
			}
			/**
			 * 	Constructs an slelement with the provided value and label,
			 *  setting the next slelement to NULL.
			 * 	The defaults will be used if not provided.
			 *
			 * 	@param val The data to hold
			 * 	@param lab The label to show
			 */
			SLelement(const E& val = E(), const string& lab = string())
				: SLelement(nullptr, val, lab) {
			}
			/**
			 *	@return The string representation of this data structure type
			 */
			virtual const string getDStype() const override {
				return "SinglyLinkedList";
			}

			/**
			 *	@return The next SLelement
			 */
			virtual SLelement* getNext() {
				return next;
			}

			/**
			 *	Constant version
			 */
			virtual const SLelement* getNext() const {
				return next;
			}

			/**
			 * Sets next link  to "n"
			 *
			 * @param n The next SLelement
			 */
			void setNext(SLelement* n) {
				//if different, remove old link data
				if (next != n) {
					this->links.erase(next);
				}
				// set next to n and if not null, create default link data
				// if none already present
				if ((next = n)) {
					this->links[next];
				}
			}
			/**
			 * Calls delete on itself and each next linked SLelement*
			 *
			 * @warning Only call if these SLelements were all dynamicaly
			 * allocated(aka: using new)
			 * @warning If linked list contains redundant links, delete will be called
			 * multiple times on it, leading to undefined behavior
			 */
			virtual void cleanup() override {
				if (next) {
					next->cleanup();
				}
				DataStructure::cleanup();
			}

		private:
			/**
			 * Gets the JSON representation of this slelement and its links
			 *
			 * @param arr_size The size of the array determined by this
			 * @return A pair holding the nodes and links JSON strings respectively
			 */
			virtual const pair<string, string> getDataStructureRepresentation() const override {

				vector<const SLelement<E>*> nodes;
				// get the list of nodes
				getListElements(nodes);
				// generate the JSON string

				if (MAX_ELEMENTS_ALLOWED <= nodes.size()) {
					// cant exceed max number of elements
					throw "Max allowed elements(for visualization) exceeded.. " +
					to_string(nodes.size()) + " Must be less than " +
					to_string(MAX_ELEMENTS_ALLOWED);
				}

				return generateJSON (nodes);
			}
		protected:
			virtual const pair<string, string> generateJSON(vector<const SLelement<E>*> nodes) const {
				// map the nodes to a sequence of ids, 0...N-1
				// then get the JSON string for nodes placeholder
				// nullptr prevents insertion of other nullptrs
				unordered_map<const SLelement*, int> node_map { {nullptr, -1} };

				string nodes_JSON, links_JSON;

				int i = 0; 		// get the JSON string for nodes
				for (const auto* e : nodes) {
					if (node_map.emplace(e, i).second)  {
						// successful emplacement
						i++;
						nodes_JSON += e->getElementRepresentation() + COMMA;
					}
				}
				//Remove trailing comma and nullptr entry
				node_map.erase(nullptr);
				if (nodes_JSON.size()) {
					nodes_JSON = nodes_JSON.erase(nodes_JSON.size() - 1);
				}
				// for each pair<SLelement*,int> in map
				for (int k = 0; k < nodes.size(); k++) {
					if (nodes[k]->next != nullptr) { // link exists
						links_JSON += this->getLinkRepresentation(nodes[k]->links.at(nodes[k]->next),
								to_string(node_map[nodes[k]]),
								to_string(node_map[nodes[k]->next]) ) + COMMA;
					}
				}

				//Remove trailing comma
				if (links_JSON.size()) {
					links_JSON = links_JSON.erase(links_JSON.size() - 1);
				}

				return pair<string, string> (nodes_JSON, links_JSON);
			}
		protected:
			/**
			 * 	Get the list of nodes
			 *
			 * 	@param nodes The list of nodes
			 */
			virtual void getListElements(vector<const SLelement<E>*>& nodes) const  {

				//prevents potential infinite loop
				unordered_set<const SLelement<E>*> visited;
				auto it = this;

				// using the visited array handles both regular and
				// circular lists
				while (it != nullptr && visited.emplace(it).second) {
					nodes.push_back(it);
					it = it->next;
				}
			}
	}; //end of SLelement class

}//end of bridges namespace
#endif
