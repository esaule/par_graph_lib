#ifndef ARRAY_H 
#define ARRAY_H 

/**
 * 
 *
 * @brief This class can be used to create arrays of type Element<E> where E 
 *  is a generic type representation application specific data.  
 *  Arrays are internally represented as 1D arrays; currently 1D, 2D  and
 *  3D arrays are supported.
 *
 * @param <E>

 * @author  Kalpathi Subramanian
 * @date    10/8/16
 *
 */


#include "Element.h"

#include "Bridges.h"

namespace bridges{
/**
 * @brief A BRIDGES array type
 *
 * This class can be used to create 1D, 2D, and 3D arrays of any type.
 *
 * Generic Parameters: E the application data type
 *
 * @author Kalpathi Subramanian
 * @date 1/14/17
 */


template <typename E>
class Array : public DataStructure {

	friend class Element<E>;
	private:
		Element<E> *array_data;
		int num_dims;
		int dims[3];
		int size;

	public:
		Array() {
			array_data = NULL;
			num_dims = 1;
			dims[0] = dims[1] = dims[2] = 1;
			size = 0;
		}

		~Array(){
			delete [] array_data;
		}

		Array(int num_dims, int *dims) {
			setNumDimensions(num_dims);
			setDimensions(dims);
						// for json 
			Bridges::setDimensions(dims);
		}

		void setNumDimensions(int nd) {
			if (nd > 3) {
				cout << "Only 1D, 2D and 3D arrays supported." << endl;
				exit(-1);
			}
			num_dims = nd;
		}
		void setDimensions(int *dim) {
			int sz = 1;
			for (int k = 0; k < num_dims; k++) {
				dims[k] = dim[k];
				sz *= dim[k];
			}
							// first check the dimensions are all positive
			if (sz < 0) {
				cout << "Negative size in dimension encountered" << endl;
				exit(-1);
			}
			size = sz;
							// allocate space for the array 
cout<< "Array Size: " << size;
			array_data = new Element<E>[size];	

						// for json 
			Bridges::setDimensions(dims);
		}

		int *getDimensions(int *d) {
			for (int k = 0; k < num_dims; k++)
				d[k] = dims[k]; 
		}
			

		Element<E>& getValue(int indx) {
			return array_data[indx];
		}

		void setValue(int indx, Element<E> el) {
			array_data[indx] = el;
		}

		Element<E>& getValue(int x_indx, int y_indx) {
				return array_data[x_indx + y_indx*dims[0]];
		}

		void setValue(int x_indx, int y_indx, Element<E> el) {
			array_data[x_indx + y_indx*dims[0]] = el;
		}

		
		Element<E>& getValue(int x_indx, int y_indx, int z_indx) {
				return array_data[x_indx + y_indx*dims[0] + 
								z_indx*dims[1]*dims[0]];
		}

		void setValue(int x_indx, int y_indx, int z_indx, Element<E> el) {
			array_data[x_indx + y_indx*dims[0] + z_indx*dims[0]*dims[1]] = el;
		}

		virtual const string getDStype() const override {
/*
			string s = "1D_Array";
			if (num_dims == 1) 
				return "1D_Array";
			else if (num_dims == 2) 
				return "2D_Array";
			else if (num_dims == 3)
				return "3D_Array";
*/

			return "Array";
		}

		virtual const pair<string,string> getDataStructureRepresentation() 
											const override final {
			vector<const Element<E>*> nodes;

			for (int k = 0; k < size; k++) {
				nodes.push_back(&array_data[k]);
			}
								//  also send dimensions to 
			return Element<E>::generateOrderedJSON(nodes);
		}

/*
	private:
        static const pair<string,string>generateOrderedJSON(
								const vector<const Element<E>*>& nodes) {
            if (MAX_ELEMENTS_ALLOWED <= nodes.size()) { 
							// cant exceed max number of elements
				throw "Max allowed elements(for visualization) exceeded.. " +
							to_string(nodes.size())+" Must be less than "+
							to_string(MAX_ELEMENTS_ALLOWED);
			}
						// map the nodes to a sequence of ids, 0...N-1 
						// then get the JSON string for nodes placeholder 
						// nullptr prevents insertion of other nullptrs
			unordered_map<const Element<E>*,int> map{{nullptr,-1}}; 

			string nodes_JSON;

            int i = 0; // get the JSON string for nodes
            for(const auto* e: nodes) {
                if (map.emplace(e,i).second && ++i)  {
						// short circut only incriments i and gets rep 
						// upon successful emplacement
					nodes_JSON += e->getRepresentation() + COMMA;
				}
			}
			map.erase(nullptr); //Remove trailing comma and nullptr entry
			if (nodes_JSON.size()){
				nodes_JSON = nodes_JSON.erase(nodes_JSON.size()-1);
			}

            return pair<string,string>(nodes_JSON, ""); 
	}
*/
};

}// end namespace bridges
#endif
