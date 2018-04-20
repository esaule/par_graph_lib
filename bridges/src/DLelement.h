#ifndef DLelement_H
#define DLelement_H

#include "SLelement.h" //string, using std

namespace bridges {
	/**
	 * @brief The doubly linked list element, derived from SLelement
	 *
	 * This class extends the SLelelement class by adding a previous DLelement
	 * pointer
	 *
	 * Generic Parameters: E the application data type
	 *
	 * @author Kalpathi Subramanian
	 * @date 6/11/15
	 */
	template<typename E>
	class DLelement: public SLelement<E> {
		private:

			DLelement* prev = nullptr;// The pointer to the previous DLelement

		public:
			/**
			 *  Constructs a dlelement with the provided value, label, next and
			 *  previous dlelements.
			 *  The defaults will be used if not provided.
			 *
			 * @param val The data to hold
			 * @param lab The label to show
			 * @param n The next DLelement
			 * @param p The previous DLelement
			 */
			DLelement(DLelement* n, DLelement* p = nullptr, const E& val = E(),
				const string& lab = string()) : SLelement<E>(n, val, lab) {
				setPrev(p);
			}

			/**
			 * Constructs a dlelement with the provided value and label,
			 *  setting the next and previous dlelements to NULL.
			 * The defaults will be used if not provided.
			 *
			 * @param val The data to hold
			 * @param lab The label to show
			 */
			DLelement (const E& val = E(), const string& lab = string()) :
				DLelement(nullptr, nullptr, val, lab) {
			}

			/**
			 *  Return the data structure type
			 *
			 * @return The string representation of this data structure type
			 *
			 */
			virtual const string getDStype() const override {
				return "DoublyLinkedList";
			}
			/**
			 * 	Return the next DL element.
			 *
			 *	@return The next DLelement
			 */
			virtual DLelement* getNext() override {
				return static_cast<DLelement*>(SLelement<E>::getNext());
			}

			/**
			 * Constant version
			 *
			 * @return The next DLelement
			 */
			virtual const DLelement* getNext() const override {
				return static_cast<const DLelement*>(SLelement<E>::getNext());
			}
			/**
			 * Sets next to "n"
			 *
			 * @param n The next DLelement
			 *
			 */
			void setNext(DLelement* n) {
				if (this->next != n && this->next != prev) {
					//if different, remove old link data
					this->links.erase(this->next);
				}
				if ((this->next = n)) {
					this->links[this->next];
				}
			}
			/** @return The previous DLelement */
			DLelement* getPrev() {
				return prev;
			}
			/**
			 * Constant version
			 *
			 * @return The previous DLelement
			 */
			const DLelement* getPrev() const {
				return prev;
			}
			/**
			 * Sets prev to "p"
			 *
			 * @param p The previous DLelement
			 */
			void setPrev(DLelement* p) {
				if (prev != p && this->next != prev) {
					this->links.erase(prev);   //if different, remove old link data
				}
				//	set prev to p and if not null, create
				//	default link data if none already present
				if ((prev = p)) {
					this->links[prev];
				}
			}

		private:

			virtual const pair<string, string> getDataStructureRepresentation() const override {

				vector<const DLelement<E>*> nodes;

				// get the list of nodes

				getListElements(nodes);

				// generate the JSON string

				if (MAX_ELEMENTS_ALLOWED <= nodes.size()) {
					// cant exceed max number of elements
					throw "Max allowed elements(for visualization) exceeded.. " +
					to_string(nodes.size()) + " Must be less than " +
					to_string(MAX_ELEMENTS_ALLOWED);
				}

				// map the nodes to a sequence of ids, 0...N-1
				// then get the JSON string for nodes placeholder
				// nullptr prevents insertion of other nullptrs
				unordered_map<const DLelement*, int> node_map { {nullptr, -1} };

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

				// generate the links using the node map ids
				for (int k = 0; k < nodes.size(); k++) {
					if (nodes[k]->next != nullptr) { // link exists
						links_JSON += this->getLinkRepresentation(nodes[k]->links.at(nodes[k]->next),
								to_string(node_map[nodes[k]]),
								to_string(node_map[nodes[k]->getNext()]) ) + COMMA;
					}
					if (nodes[k]->prev != nullptr) { // link exists
						links_JSON += this->getLinkRepresentation(nodes[k]->links.at(nodes[k]->prev),
								to_string(node_map[nodes[k]]),
								to_string(node_map[nodes[k]->prev]) ) + COMMA;
					}
				}

				//Remove trailing comma
				if (links_JSON.size()) {
					links_JSON = links_JSON.erase(links_JSON.size() - 1);
				}

				return pair<string, string> (nodes_JSON, links_JSON);
			}

			/**
			*  Get the list of nodes
			*
			*  @param nodes The list of nodes
			*/
			virtual void getListElements(vector<const DLelement<E>*>& nodes) const  {

				//prevents potential infinite loop
				unordered_set<const DLelement<E>*> visited;
				auto it = this;

				// using the visited array handles both regular and
				// circular lists
				while (it != nullptr && visited.emplace(it).second) {
					nodes.push_back(it);
					it = it->getNext();
				}
			}

	}; //end of DLelement class


}//end of bridges namespace
#endif
