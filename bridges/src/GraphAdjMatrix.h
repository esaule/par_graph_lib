#ifndef GRAPH_ADJ_MATRIX_H
#define GRAPH_ADJ_MATRIX_H

#include <stdexcept>    //out of range
#include <sstream>      //stringstream

#include "Element.h"    //DataStructure, unordered_map, string, cerr, using std

namespace bridges{
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
		void addVertex(const K& k,const E& e=E()) {
			stringstream conv; conv<<k; //Converts key into string
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
		void addEdge(const K& src,const K& dest,const unsigned int& wt) {
			try { 					//create default link data 
                vertices.at(src)->links[vertices.at(dest)]; 
									// add edge
				matrix.at(src).at(dest) = wt;
            }
            catch(const out_of_range& oor){
				cerr<<"Cannot addEdge between non-existent verticies." << endl;
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
		const unordered_map<K, Element<E> *>& getVertices() const {
			return vertices;
		}
	private:

		/**
		 * Gets the JSON representation of this Graph's nodes and links
		 *
		 * @return A pair holding the nodes and links JSON strings respectively
		 */
		virtual const pair<string,string> getDataStructureRepresentation() 
										const override final {
			unordered_set<const Element<E>*> nodes;
			for(const auto& key_ele : vertices) {
				nodes.emplace(key_ele.second);
			}
			return Element<E>::generateJSON(nodes); // generate the JSON
		}
}; //end of GraphAdjMatrix class

}//end of bridges namespace
#endif
