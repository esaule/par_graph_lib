#ifndef GRAPH_ADJ_LIST
#define GRAPH_ADJ_LIST

#include <stdexcept> //out of range
#include <sstream> //stringstream
#include <unordered_map>

using namespace std;

#include "SLelement.h"
#include "Edge.h"

namespace bridges {
	/**
	 * 	@brief This class provides methods to represent adjacency list
	 *	based graphs
	 *
	 * 	The class is simply a wrapper around the C++ STL unordered_map class
	 *	and thus derives all its operations from it.
	 *
	 * <b>Generic Parameters:</b>
	 * \verbatim
	       K:  used as an index to retrieve vertices,
	       E1: data type used to store vertex specific information,
	       E2: data type used to store edge specific information
	  \endverbatim
	 *
	 * @author Kalpathi Subramanian
	 * @date Last modified 4/22/18
	 */
	template<typename K, typename E1 = K, typename E2 = E1>
	class GraphAdjList : public DataStructure {
		private:
			// list of graph vertices
			// maintained as a map to accommodate strings
			unordered_map<K, Element<E1>* > vertices;
			// adjacency lists
			unordered_map<K, SLelement<Edge<K, E2> >*> adj_list;

		public:
			virtual ~GraphAdjList() override {
				//			for(auto& p : adj_list) {  //frees edges
				//				if (p.second){p.second->cleanup();}
				//			}
			}
			/**
			 *	@return The string representation of this data structure type
			 */
			virtual const string getDStype() const override {
				return "GraphAdjacencyList";
			}

			/**
			 * 	Adds a vertex of key "k" and value "e" to the graph,
			 *	and initializes its adjacency list; If this key already
			 *	exists  then this will not create a new vertex.
			 *
			 *
			 * @param k The vertex key
			 * @param e The vertex data
			 *
			 */
			void addVertex(const K& k, const E1& e = E1()) {
				stringstream conv;
				conv << k;
				if (vertices.find(k) == vertices.end()) {
					// vertex does not exist, create one
					vertices[k] = new Element<E1>(e, conv.str());
					adj_list[k] = nullptr;
				}
			}
			/**
			 * 	Sets the edge from "src" to "dest", weight to "wt" and data
			 *	to "data".  Note. This function adds the edge regardless of
			 *	the contents of the adjacency list; its the user's responsibility
			 *	to ensure there are no duplicates and ensure consistency.
			 *
			 * @param src The key of the source Vertex
			 * @param dest The key of the destination Vertex
			 * @param wt The weight of the edge
			 * @param data The edge data
			 * @throw out_of_range If "src" or "dest" is non-existenet within
			 *	this graph
			 * @throw bad_alloc If allocation of a graph adjacency list item failed
			 */
			void addEdge(const K& src, const K& dest, const unsigned int& wt,
				const E2& data = E2()) {
				try {
					vertices.at(src);
					vertices.at(dest);
					// links structure is redundant and needs
					// to be removed in future implementations!
					vertices[src]->links[vertices.at(dest)];

					stringstream conv;
					conv << dest;
					// add the edge
					adj_list.at(src) =
						new SLelement<Edge<K, E2> > (adj_list.at(src),
						Edge<K, E2> (dest, wt, data), conv.str());

				}
				catch ( const out_of_range& ) {
					cerr << "addEdge(): Nonexistent vertex?" << endl <<
						"Create vertices first prior to adding edges that use that vertex" << endl
						<<  "Cannot add edge between non-existent verticies"
						<< endl;
					throw;
				}
			}
			/**
			 * 	Gets vertex data for a graph vertex
			 *
			 * @param src The key of the source vertex
			 *
			 * @return E1  vertex specific data
			 */
			E1  getVertexData (const K& src) {
				try {
					Element<E1> *el = vertices.at(src);
					return  (vertices.at(src))->getValue();
				}
				catch ( const out_of_range& ) {
					cerr << "getVertexData(): vertex not found" << endl;
					throw;
				}
				// should never reach here
				throw "getVertexData(): vertex not found";
			}
			/**
			 * 	Loads vertex specific information for a graph vertex
			 *
			 * @param src The key of the source Vertex
			 *
			 */
			void setVertexData (const K& src, E1& data) {
				try {
					Element<E1> *el = vertices.at(src);
					el->setValue (data);
				}
				catch ( const out_of_range& ) {
					cerr << "setVertexData(): Nonexistent vertices or " <<
						" edge not found" << endl;
					throw;
				}
				catch (const char* msg) {
					cerr << msg << endl;
				}
			}
			/**
			 * 	Gets edge data for the edge from "src" to "dest"
			 *
			 * @param src The key of the source Vertex
			 * @param dest The key of the destination Vertex
			 *
			 * @return E2  edge specific data
			 */
			E2&  getEdgeData (const K& src, const K& dest) {
				try {
					vertices.at(src);
					vertices.at(dest);
					SLelement<Edge<K, E2> > *sle = adj_list.at(src);
					while (sle) {
						Edge<K, E2> ed = sle->getValue();
						if (ed.getVertex() == dest) { //edge exists
							return ed.getEdgeData();
						}
						sle = sle->getNext();
					}
					throw "Edge not found!";
				}
				catch ( const out_of_range& ) {
					cerr << "getEdgeData(): Edge not found" << endl;
					throw;
				}
				catch (const char* msg) {
					cerr << msg << endl;
				}
				// should never reach here
				throw "getEdgeData(): Edge not found";
			}
			/**
			 * 	Loads edge specific information for the edge from "src" to
			 *   "dest"
			 *
			 * @param src The key of the source Vertex
			 * @param dest The key of the destination Vertex

			 */
			void setEdgeData (const K& src, const K& dest, E2& data) {
				try {
					vertices.at(src);
					vertices.at(dest);
					SLelement<Edge<K, E2> > *sle = adj_list.at(src);
					while (sle) {
						Edge<K, E2> ed = sle->getValue();
						if (ed.getVertex() == dest) { //edge exists
							ed.setEdgeData(data); //change edge data
							sle->setValue(ed); //change slelement data
							return;
						}
						sle = sle->getNext();
					}
					throw "getEdgeData(): Edge not found!";
				}
				catch ( const out_of_range& ) {
					cerr << "setEdgeData(): Nonexistent vertices or " <<
						" edge not found" << endl;
					throw;
				}
				catch (const char* msg) {
					cerr << msg << endl;
				}
				// will never reach here, but avoids compiler warnings
				throw "getEdgeData(): Edge not found";
			}
			/*
			        void addEdge(const K& src, const K& dest, const unsigned int& wt,
										const string& data = string()) {
						try {
			                vertices.at(src); vertices.at(dest);
			                if(wt==0){				//remove link data
								vertices.at(src).links.erase(&(vertices.at(dest)));
							}
							SLelement<Edge<K> > *sle = adj_list.at(src);
			                while(sle) {
			                    Edge<K> ed = sle->getValue();
			                    if(ed.getVertex() == dest){ //edge already exists
			                        ed.setWeight(wt); //change edge weight
			                        ed.setEdgeData(data); //change edge data
			                        sle->setValue(ed); //change slelement data
			                        return;
			                    }
			                    sle = sle->getNext();
			                }
									// edge doesn't exist creates default link data
									// if none already present
			                vertices.at(src).links[&(vertices.at(dest))];
			                stringstream conv; conv << dest;
			                adj_list.at(src) =
								new SLelement<Edge<K> > (adj_list.at(src),
									Edge<K> (dest, wt, data), conv.str());// create edge
			            }
			            catch( const out_of_range& ){
							cerr<<"addEdge(): must create vertices first prior to adding "
								<< "edges; cannot addEdge between non-existent verticies"
								<< endl;
							throw;
						}
			        }
			*/
			/**
			 *	@return The vertex list of this graph
			 */
			unordered_map<K, Element<E1>*>* getVertices() {
				return &vertices;
			}
			/**
			 *	@return the requested vertex of this graph
			 */
			const Element<E1>* getVertex(const K& key) const {
				return vertices.at(key);
			}


			/**
			 *	@return the requested vertex of this graph
			 *
			 *  non-const version
			 */
			Element<E1>* getVertex(const K& key) {
				return vertices.at(key);
			}


			/**
			 *	@return The adjacency list  of the graph
			 */
			const unordered_map<K, SLelement<Edge<K, E2> >*>&
			getAdjacencyList() const {
				return adj_list;
			}

			/**
			 * Returns adjacency list of a vertex with name k
			 *
			 * @param k The key of the source vertex
			 * @throw out_of_range If key is non-existent within this graph
			 *
			 * @return The adjacency list of key "k"
			 */
			SLelement<Edge<K, E2> >* getAdjacencyList(const K& k) {
				try {
					return adj_list.at(k);
				}
				catch (const out_of_range& ) {
					cerr <<  "Cannot getAdjacencyList() of a non-existent vertex!"
						<< endl;
					throw;
				}
			}

			/**
			 *  Returns the  visualizer corresponding to  a graph vertex;
			 *	convenient method to set attributes of the graph vertex
			 *
			 *  @param k The key of the graph vertex
			 *
			 *  @return the visualizer that controls the attributes  of this node
			 */
			ElementVisualizer *getVisualizer (const K& k) {
				try {
					Element<E1> *el = vertices.at(k);

					return el->getVisualizer();
				}
				catch (const out_of_range& ) {
					cerr <<  "Graph vertex " << k << " not found in graph!" << endl;
					throw;
				}
			}
			/**
			 *  Returns the link visualizer corresponding to two graph
			 *	nodes with an existing link; error returned if no link exists.
			 *
			 *  @param k1 The key of the link source vertex
			 *  @param k2 The key of the link destination  vertex
			 *
			 * @return the visualizer that controls the attributes  of this link
			 */
			LinkVisualizer *getLinkVisualizer (const K& k1, const K& k2) {
				try {
					Element<E1> *el1 = vertices.at(k1);
					Element<E1> *el2 = vertices.at(k2);

					return el1->getLinkVisualizer(el2);
				}
				catch (const out_of_range& ) {
					cerr <<  "Either source or destination node not found in graph!"
						<< endl;
					throw;
				}
			}
		private:
			/**
			 * Gets the JSON representation of this Graph's nodes and links
			 *
			 * @return A pair holding the nodes and links JSON strings respectively
			 */
			virtual const pair<string, string> getDataStructureRepresentation()
			const override {

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

				// iterate through the vertices and form the links JSON

				for (const auto& v : vertices) {
					// get adj. list
					Element<E1>* src_vert = vertices.at(v.first);
					// iterate through list and form links
					for (SLelement<Edge<K, E2>>* it = adj_list.at(v.first); it != nullptr;
						it = it->getNext()) {
						Element<E1>* dest_vert = vertices.at(it->getValue().getVertex() );
						links_JSON +=  src_vert->getLinkRepresentation(
								*(src_vert->getLinkVisualizer(dest_vert)),
								to_string(node_map.at(v.first)),
								to_string(node_map.at(it->getValue().getVertex())) ) + COMMA;
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
