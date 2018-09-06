#ifndef ELEMENT_H

#define ELEMENT_H

#include <unordered_set>
#include <unordered_map>
#include <cmath>

using namespace std;

#include "DataStructure.h"
#include "ElementVisualizer.h"
#include "LinkVisualizer.h"

namespace bridges {
	// forward Declarations
	template <typename K, typename E1, typename E2> class GraphAdjList;
	template <typename K, typename E1, typename E2> class GraphAdjMatrix;

	/**
	 *	@brief This is the fundamental building block for all data structures
	 *	in BRIDGES.
	 *
	 *	This is the Superclass Element with SLelement, DLelement, MLElement,
	 *	CircSlElement, CircDlElement, TreeElement, AVLTreeElement, BSTElement
	 *	subclasses.
	 *
	 * 	Generic Parameters: E the application data type
	 *
	 * 	The label field(string type) is used to label the visualization of the
	 * 	element.
	 *
	 * 	Element holds a LinkVisualizer for each of its links and
	 * 	an ElementVisualizer for itself
	 *
	 * 	@author Kalpathi Subramanian
	 *
	 * 	@date 6/11/15, 11/27/16
	 */


	template <typename E> class Element {
			//Used for access to generateJSON() and for links manipulation
			template <typename K, typename E1, typename E2> friend class GraphAdjList;
			template <typename K, typename E1, typename E2> friend class GraphAdjMatrix;
			template <typename K> friend class Array;

		private:
			static const unordered_map<const Shape, const string, hash<int>>
				ShapeNames;
			//this element's label
			string label;
			// appl. specific data stored with element
			E value = E();
			// this element's visualizer
			ElementVisualizer* elvis;

		protected:

			// this element's collection of links
			unordered_map<Element*, LinkVisualizer> links;

		public:
			/**
			 * Constructs an element with the provided value and label.
			 * The defaults will be used if not provided.
			 *
			 * @param val The data to hold
			 * @param lab The label to show
			 */
			Element(const E& val = E(), const string& lab = string()) :
				label(lab), value(val) {
				elvis = new ElementVisualizer;
			}

			Element(const Element& e)
				: label(e.label), value(e.value), elvis(new ElementVisualizer(*(e.elvis))), links(e.links) {
			}

			Element& operator= (const Element& e) {
				this->label = e.label;
				this->value = e.value;
				*(this->elvis) = *(e.elvis);
				this->links = e.links;
				return *this;
			}

			virtual ~Element() {
				delete elvis;
			}

			/**
			 *	@return The ElementVisualizer of this element
			 */
			ElementVisualizer* getVisualizer() {
				return elvis;
			}
			/**
			 * Constant version
			 *
			 * @return The ElementVisualizer of this element
			 */
			const ElementVisualizer* getVisualizer() const {
				return elvis;
			}
			/**
			 * Returns the LinkVisualizer to element "el" or NULL if no link exists
			 *
			 * @param el The terminating element of the link
			 *
			 * @return The LinkVisualizer
			 */
			LinkVisualizer* getLinkVisualizer(const Element* el) {
				if (links.find(const_cast<Element*>(el)) != links.end()) {
					return &(links.at(const_cast<Element*>(el)));
				}
				cerr << "Element " << label << " not linked to Element "
					<< el->getLabel() << ", returning NULL" << endl;
				return nullptr;
			}

			/**
			 * Constant version
			 *
			 * @param el The terminating element of the link
			 * @return The LinkVisualizer
			 */
			LinkVisualizer* getLinkVisualizer(const Element* el) const {
				return const_cast<Element*> (this)->getLinkVisualizer(el);
			}

			/**
			 *	@return The label of the element
			 */
			string getLabel() const {
				return label;
			}

			/**
			 * Sets label to "lab"
			 *
			 * @param lab The label of the element
			 */
			void setLabel(const string& lab) {
				label = lab;
			}

			/**
			 *	@return The value of the element
			 */
			E getValue() const {
				return value;
			}

			/**
			 * Sets value to "val"
			 *
			 * @param val The value of the element
			 */
			void setValue(const E& val) {
				value = val;
			}

		protected:
			/**
			 *	@return to_string of "num" without unnessasary trailing 0s
			 */
			static string removeTrailingZeros(const double& num) {
				if (static_cast<int>(num) == num) {
					return to_string(static_cast<int>(num));
				}	//if integer return as int
				string numRep = to_string(num);
				//removes trailing 0s
				numRep.erase(numRep.find_last_not_of("0") + 1);
				return numRep;
			}

			/**
			 *	@return The JSON string of this element's properties
			 */
			virtual const string getElementRepresentation() const {
				//write out ElementVisualizer properties

				// first check if location is set and needs to be included
				string loc_str = "";
				if ( (elvis->getLocationX() != INFINITY) &&
					(elvis->getLocationY() != INFINITY) ) {
					loc_str =  QUOTE + "location" + QUOTE + COLON +
						OPEN_BOX +
						to_string(elvis->getLocationX())  + COMMA +
						to_string(elvis->getLocationY()) +
						CLOSE_BOX + COMMA;
				}
				return  OPEN_CURLY +
					QUOTE + "color" + QUOTE + COLON + getCSSRepresentation(elvis->getColor())
					+ COMMA +
					loc_str +
					QUOTE + "shape" + QUOTE + COLON + QUOTE +
					ShapeNames.at(elvis->getShape()) + QUOTE + COMMA +
					QUOTE + "size" + QUOTE + COLON +
					removeTrailingZeros(elvis->getSize()) + COMMA +
					QUOTE + "name" + QUOTE + COLON + QUOTE + label + QUOTE +
					CLOSE_CURLY;
			}
			/**
			 * Gets the JSON representation of this link visualizer using
			 * the supplied source and destination strings
			 *
			 * @param lv The LinkVisualizer
			 * @param src The source vertex
			 * @param dest The destination vertex
			 * @return The JSON of this link visualizer
			 *
			 */
			static const string getLinkRepresentation(const LinkVisualizer& lv,
				const string& src, const string& dest) {
				//write out LinkVisualizer properties
				return OPEN_CURLY +
					QUOTE + "color"     + QUOTE + COLON + getCSSRepresentation(lv.getColor())
					+ COMMA +
					(!lv.getLabel().empty() ?
						(QUOTE + "label" + QUOTE + COLON +
							QUOTE + lv.getLabel() + QUOTE + COMMA) : "") +
					QUOTE + "thickness" + QUOTE + COLON +
					removeTrailingZeros(lv.getThickness()) + COMMA +
					QUOTE + "weight"    + QUOTE + COLON +
					removeTrailingZeros(lv.getWeight()) + COMMA +
					QUOTE + "source"    + QUOTE + COLON + src  + COMMA +
					QUOTE + "target"    + QUOTE + COLON + dest +
					CLOSE_CURLY;
			}
			/**
			 * Gets the JSON representation of this color
			 *
			 * @param col The Color
			 * @return Equivilant Legal CSS color representation
			 */
			static const string getCSSRepresentation(const Color& col) {
				if (col.isTransparent()) {
					//leaves off other channels if transparent
					return "[0, 0, 0, 0.0f]";
				}
				const string strCSS =
					to_string(col.getRed()) + "," +
					to_string(col.getGreen()) + "," +
					to_string(col.getBlue()) + "," +
					to_string( ((float) (col.getAlpha()) / 255.0f));

				return OPEN_BOX + strCSS + CLOSE_BOX;
			}
		public:
			void printLinks() {
				cout << "[printLinks]Source vert: " << label << ", " << this << endl;

				for (auto& it : links) {
					cout << "\t Dest Elements : " << (it.first)->getLabel() << ","
						<< it.first << endl;
				}
			}

			// temp
	};	//end of Element class

	template <typename E> const unordered_map<const Shape, const string, hash<int>>
	Element<E>::ShapeNames {
		{CIRCLE, "circle"},
		{SQUARE, "square"},
		{DIAMOND, "diamond"},
		{CROSS, "cross"},
		{TRIANGLE, "triangle"},
		{WYE, "wye"},
		{STAR, "star"}
	};


}//end of bridges namespace

#endif



/**
 * Generates the JSON of the given the nodes and associated links
 *
 * @param nodes List of nodes
 * @throw string If maximum elements exceeded
 * @return A pair holding the nodes and links JSON strings respectively
 */
/*
			static const pair<string, string> generateJSON(
				const unordered_set<const Element*>& nodes) {
				// cant exceed max number of elements
				if (MAX_ELEMENTS_ALLOWED <= nodes.size()) {
					throw "Max allowed elements(for visualization) exceeded.."
					+ to_string(nodes.size()) +
					" Must be less than " + to_string(MAX_ELEMENTS_ALLOWED);
				}
				// map the nodes to a sequence of ids, 0...N-1
				// then get the JSON string for nodes placeholder
				// nullptr prevents insertion of other nullptrs
				unordered_map<const Element*, int> map{{nullptr, -1}};

				string nodes_JSON, links_JSON;

				int i = 0; // get the JSON string for nodes
				for (const auto* e : nodes) {
					// short circut only incriments i and
					//gets rep upon successful emplacement
					if (map.emplace(e, i).second && ++i) {
						nodes_JSON += e->getElementRepresentation() + COMMA;
					}
				}
				map.erase(nullptr); //Remove trailing comma and nullptr entry
				if (nodes_JSON.size()) {
					nodes_JSON = nodes_JSON.erase(nodes_JSON.size() - 1);
				}
				for (const auto& ele_int : map) { //each pair<Element*,int> in map
					for (const auto& ele_lv : ele_int.first->links) {
						//each pair<Element*,LinkVisualizer>
						// in Element*->links

						//mapping of destination node
						auto it = map.find(ele_lv.first);
						//only add link if dest node exists
						if (it != map.end()) {
							links_JSON += getLinkRepresentation(ele_lv.second,
									to_string(ele_int.second), to_string(it->second))
								+ COMMA;
						}
					}
				}
				if (links_JSON.size()) {
					//Remove trailing comma
					links_JSON = links_JSON.erase(links_JSON.size() - 1);
				}
				return pair<string, string>(nodes_JSON, links_JSON);
			}

			static const pair<string, string>	generateOrderedJSON(
				const vector<const Element*>& nodes) {

				if (MAX_ELEMENTS_ALLOWED <= nodes.size()) {
					// cant exceed max number of elements
					throw "Max allowed elements(for visualization) exceeded.. " +
					to_string(nodes.size()) + " Must be less than " +
					to_string(MAX_ELEMENTS_ALLOWED);
				}
				// map the nodes to a sequence of ids, 0...N-1
				// then get the JSON string for nodes placeholder
				// nullptr prevents insertion of other nullptrs
				unordered_map<const Element*, int> node_map { {nullptr, -1} };

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
				// for each pair<Element*,int> in map
				for (const auto& ele_int : node_map) {
					// for each pair<Element*,LinkVisualizer>
					// in Element*->links
					for (const auto& ele_lv : ele_int.first->links) {
						// mapping of destination node
						auto it = node_map.find(ele_lv.first);
						if (it != node_map.end() ) { 	//only add link if dest node exists
							links_JSON += getLinkRepresentation(ele_lv.second,
									to_string(ele_int.second),
									to_string(it->second)) + COMMA;
						}
					}
				}
				//Remove trailing comma
				if (links_JSON.size()) {
					links_JSON = links_JSON.erase(links_JSON.size() - 1);
				}

				return pair<string, string>(nodes_JSON, links_JSON);
			}
*/
// temp
