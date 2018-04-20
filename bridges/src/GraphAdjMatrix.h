#ifndef GRAPH_ADJ_MATRIX_H
#define GRAPH_ADJ_MATRIX_H

#include <stdexcept>    //out of range
#include <sstream>      //stringstream

#include "Element.h"    //DataStructure, unordered_map, string, cerr, using std

namespace bridges {
	/**
	 *	@brief This class provides methods to represent adjacency matrix based
	 *	graphs
	 *
	 *	The class is simply a wrapper around the C++ STL unordered_map class
	 *	and thus derives all its operations from it.  Given the use of operator
	 *	overloading, the adjacency matrix implementation is almost identical
	 *	to a normal array representation, except that any ordered type can
	 *	be used to index into the matrix.
	 *
	 *	Generic Parameters:
	 *		K that is used as an index,
	 *		E the application data type
	 *
	 *	@author Kalpathi Subramanian, Dakota Carmer
	 *	@date 6/29/15, 7/10/16, 11/27/16
	 */
	template <typename K, typename E>
	class GraphAdjMatrix : public DataStructure {
		private:
			unordered_map<K, Element<E>* > vertices;
			unordered_map<K, unordered_map<K, int> > matrix;

		public:
			/**
			 *	@return The string representation of this data structure type
			 */
			virtual const string getDStype() const override {
				return "GraphAdjacencyMatrix";
			}

			/**
			 * Adds a vertex of key "k" and value "e" to the graph.
			 * Sets all of its edges to be of weight 0.
			 *
			 * @param k Vertex key
			 * @param e Vertex data
			*/
			void addVertex(const K& k, const E& e = E()) {
				stringstream conv;
				conv << k; //Converts key into string
				vertices[k] = new Element<E>(e, conv.str());
				for (const auto& p : vertices) {
					// edge weights are 0
					matrix[k][p.first] = matrix[p.first][k] = 0;
				}
			}

			/**
			 * Sets the weight of the edge from "src" to "dest", to "wt".
			 * This will overwrite the existing edge weight.
			 *
			 * @param src The key of the source Vertex
			 * @param dest The key of the destination Vertex
			 * @param wt The weight of the edge
			 * @throw out_of_range If "src" or "dest" is non-existent
			 *	within this graph
			 */
			void addEdge(const K& src, const K& dest, const unsigned int& wt) {
				try { 					//create default link data
					vertices.at(src)->links[vertices.at(dest)];
					// add edge
					matrix.at(src).at(dest) = wt;
				}
				catch (const out_of_range& oor) {
					cerr << "Cannot addEdge between non-existent verticies." << endl;
					throw;
				}
			}
			/**
			 *	@return The matrix of this graphs edges
			 */
			const unordered_map<K, unordered_map<K, int>>& getMatrix() const {
				return matrix;
			}

			/**
			 *	@return The graph verticies
			 */
			unordered_map<K, Element<E> *>* getVertices() {
				return &vertices;
			}
			/**
			 *  @return the requested vertex of this graph
			 */
			const Element<K>* getVertex(const K& key) const {
				return vertices.at(key);
			}

			/**
			 *  @return the requested vertex of this graph
			 *
			 *  non-const version
			 */
			Element<K>* getVertex(const K& key) {
				return vertices.at(key);
			}

		private:

			/**
			 * Gets the JSON representation of this Graph's nodes and links
			 *
			 * @return A pair holding the nodes and links JSON strings respectively
			 */
			virtual const pair<string, string> getDataStructureRepresentation() const override {

				// map the nodes to a sequence of ids, 0...N-1
				// then get the JSON string for nodes placeholder
				// nullptr prevents insertion of other nullptrs

				unordered_map<K, int> node_map;
				int i = 0;
				string nodes_JSON = "", links_JSON = "";

				for (const auto& v : vertices) {
					if (node_map.emplace(v.first, i).second) {
						i++;
						nodes_JSON += v.second->getElementRepresentation() + COMMA;
					}
				}

				//Remove trailing comma and nullptr entry

				if (nodes_JSON.size()) {
					nodes_JSON = nodes_JSON.erase(nodes_JSON.size() - 1);
				}

				// iterate through the N squared entries vertices and form the links JSON

				for (const auto& src : vertices) {
					for (const auto& dest : vertices) {
						if (matrix.at(src.first).at(dest.first)) {	// link exists
							Element<E>* src_v = vertices.at(src.first);
							Element<E>* dest_v = vertices.at(dest.first);
							links_JSON +=  src_v->getLinkRepresentation(
									*(src_v->getLinkVisualizer(dest_v)),
									to_string(node_map.at(src.first)),
									to_string(node_map.at(dest.first))) + COMMA;
						}
					}
				}

				//Remove trailing comma
				if (links_JSON.size()) {
					links_JSON = links_JSON.erase(links_JSON.size() - 1);
				}

				return pair<string, string> (nodes_JSON, links_JSON);
			}
	}; //end of GraphAdjList class

}//end of bridges namespace
#endif
