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

namespace bridges {
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
			Array()
				: array_data(nullptr), num_dims(1), dims{0, 0, 0}, size(0) {
			}

			virtual ~Array() {
				if (array_data != nullptr)
					delete [] array_data;
			}

			Array(int num_dims, int *dims)
				: array_data(nullptr) {
				setNumDimensions(num_dims);
				setDimensions(dims);
				// for json
				Bridges::setDimensions(dims);
			}

			///builds a 1D array.
			///@param xsize size of the array's only dimension
			Array(int xsize)
				: Array(1, &xsize) {
			}

			///builds a 2D array.
			///@param xsize size of the array's first dimension
			///@param ysize size of the array's second dimension
			Array(int xsize, int ysize)
				: Array() {
				dims[0] = xsize;
				dims[1] = ysize;
				dims[2] = 1;
				setNumDimensions(2);
				setDimensions(dims);
				Bridges::setDimensions(dims);
			}

			///builds a 3D array.
			///@param xsize size of the array's first dimension
			///@param ysize size of the array's second dimension
			///@param zsize size of the array's third dimension
			Array(int xsize, int ysize, int zsize)
				: Array() {
				dims[0] = xsize;
				dims[1] = ysize;
				dims[2] = zsize;
				setNumDimensions(3);
				setDimensions(dims);
				Bridges::setDimensions(dims);
			}

			void setNumDimensions(int nd) {
				if (nd > 3) {
					cout << "Only 1D, 2D and 3D arrays supported." << endl;
					exit(-1);
				}
				num_dims = nd;
			}

			int getNumDimensions() const {
				return num_dims;
			}

			///change the size of the array dimensions
			///@param dim give the size of the dimension. dim should be of size at least getNumDimensions() or undefined behavior could happen.
			void setDimensions(int *dim) {
				int sz = 1;
				for (int k = 0; k < num_dims; k++) {
					if (dim[k] <= 0) {
						cout << "Dimensions of array must be positive!" << endl
							<< "\tProvided dimension: " << dim[k] << endl;
					}
					dims[k] = dim[k];
					sz *= dim[k];
				}
				// first check the dimensions are all positive
				if (sz <= 0) {
					cout << "Negative size in dimension encountered" << endl;
					exit(-1);
				}
				size = sz;
				// allocate space for the array
				if (array_data != nullptr)
					delete[] array_data;
				array_data = new Element<E>[size];

				// for json
				Bridges::setDimensions(dims);
			}

			///returns the size of the dimensions
			///@param dim will contain the size of the dimension. dim should be of size at least getNumDimensions() or undefined behavior could happen.
			void  getDimensions(int *d) {
				for (int k = 0; k < num_dims; k++)
					d[k] = dims[k];
			}

			/**
			 *
			 *  Get the object at index x  - 1D array
			 *
			 *  @param x_indx - index into the array
			 *
			 *  @return Element<E>  object at 'indx'
			 */
			Element<E>& getElement(int x) {
				return array_data[x];
			}

			/**
			 *
			 *  Get the object at x, y, z -- for 3D arrays
			 *
			 *  @param x  - column index
			 *  @param y  - row index
			 *
			 *  @return Element<E>  object at x, y
			 */
			Element<E>& getElement(int x, int y) {
				return array_data[y * dims[0] + x];
			}
			/**
			 *
			 *  Get the object at x, y, z -- for 3D arrays
			 *
			 *  @param x  - column index
			 *  @param y  - row index
			 *
			 *  @return Element<E>  object at x, y, z
			 */
			Element<E>& getElement(int x, int y, int z) {
				return array_data[z * dims[0] * dims[1] + y * dims[0] + x];
			}

			/**
			 *
			 *  Set the object at index x  - 1D array
			 *
			 *  @param x - index into the array
			 *  @el - Element object
			 *
			 *  @return none
			 */
			void setElement(int indx, Element<E> el) {
				array_data[indx] = el;
			}

			/**
			 *
			 *  Set the object at index x, y  - 2D array
			 *
			 *  @param x - col index into the array
			 *  @param y - row index into the array
			 *  @el - Element object
			 *
			 *  @return none
			 */
			void setElement(int x_indx, int y_indx, Element<E> el) {
				array_data[x_indx + y_indx * dims[0]] = el;
			}
			/**
			 *
			 *  Set the object at index x, y, z  - 3D array
			 *
			 *  @param x - col index into the array
			 *  @param y - row index into the array
			 *  @param z - slice index into the array
			 *  @el - Element object
			 *
			 *  @return none
			 */

			void setElement(int x_indx, int y_indx, int z_indx, Element<E> el) {
				array_data[x_indx + y_indx * dims[0] + z_indx * dims[0]*dims[1]] = el;
			}

			virtual const string getDStype() const override {
				return "Array";
			}

			virtual const pair<string, string> getDataStructureRepresentation()
			const override final {
				vector<const Element<E>*> nodes;

				for (int k = 0; k < size; k++) {
					nodes.push_back(&array_data[k]);
				}
				//  also send dimensions to
				return generateJSON(nodes);
			}

			Array(const Array&) = delete; //would be incorrect, so disabled.
			Array& operator=(const Array&) = delete; //would be incorrect, so disabled.


		private:
			static const pair<string, string>generateJSON( const vector<const Element<E>*>& nodes) {
				if (MAX_ELEMENTS_ALLOWED <= nodes.size()) {
					// cant exceed max number of elements
					throw "Max allowed elements(for visualization) exceeded.. " +
					to_string(nodes.size()) + " Must be less than " +
					to_string(MAX_ELEMENTS_ALLOWED);
				}
				// map the nodes to a sequence of ids, 0...N-1
				// then get the JSON string for nodes placeholder
				// nullptr prevents insertion of other nullptrs
				unordered_map<const Element<E>*, int> map{{nullptr, -1}};

				string nodes_JSON;

				int i = 0; // get the JSON string for nodes
				for (const auto* e : nodes) {
					if (map.emplace(e, i).second && ++i)  {
						// short circut only incriments i and gets rep
						// upon successful emplacement
						nodes_JSON += e->getElementRepresentation() + COMMA;
					}
				}
				map.erase(nullptr); //Remove trailing comma and nullptr entry
				if (nodes_JSON.size()) {
					nodes_JSON = nodes_JSON.erase(nodes_JSON.size() - 1);
				}

				return pair<string, string>(nodes_JSON, "");
			};


	}; // Array

}// end namespace bridges

#endif
