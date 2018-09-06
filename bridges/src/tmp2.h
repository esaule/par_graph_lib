#ifndef  CIRC_SL_ELEMENT_H

#define CIRC_SL_ELEMENT_H
#include "SLelement.h"

namespace bridges {
/**
 *  @brief This class can be used to instantiate Singly Linked
 *  Circular List Elements.

 * 	This class can be used to instantiate Circular (Singly) Linked
 *	List Elements, derived from Singly Linked Element. The main difference
 *	from the SLelement is that they create circularly linked elements and
 *  their traversals are slightly different.
 *
 * 	Elements have labels (string) that are displayed on the visualization
 *  Elements take an generic object as a user defined parameter, any native
 *	type or object.
 *
 * 	Element contains a visualizer object for setting visual attributes (color,
 *	shape, opacity, size), necessary for displaying them in a web browser
 *
 *	@author Kalpathi Subramanian
 *	@date 10/5/2016
 *
 *	@param <E>
 */


	template <typename E>
	class CircSLelement : public SLelement<E> {

		public:
			/**
			* 	This constructor creates an CircSLelement object
			* 	and sets its next pointer to itself
			*
			*/
			CircSLelement() : SLelement<E> (this) {
			}
			/**
			 * 	This constructor creates an CircSLelement object of value "e" and
			 *	label "label"
			 * 	and sets the next pointer to null
			 *
			 * 	@param label the label of CircSLelement that shows up on
			 *		the Bridges visualization
			 * 	@param e the generic object that this CircSLelement will hold
			 */
			CircSLelement (E val = E(), string label = string()) 
						: SLelement<E> (this, val, label) {
			}

			/**
			 * Creates a new element with value "e" and sets the next pointer
			 * to the CircSLelement referenced by the "next" argument
			 *
			 * @param e the generic object that this CircSLelement will hold
			 * @param next the CircSLelement that should be assigned to the next
			 * 		pointer
			 */
			CircSLelement (E e = E(), CircSLelement *next = nullptr) 
								: SLelement<E> (next, e) {
			}

			/**
			 * Creates a new element and sets the next pointer
			 * to the CircSLelement "next"
			 * @param next the CircSLelement that should be assigned to the
			 *	next pointer
			 */
			CircSLelement (CircSLelement *next) : SLelement<E> (next) {
			}

			/**
			 *	This method gets the data structure type
			 *
			 *	@return  The date structure type as a string
			 */
			virtual const string getDStype() const override {
				return "CircularSinglyLinkedList";
			}

			/**
			 * Retrieves the next CircSLelement
			 * @return CircSLelement<E> assigned to next
			 */
			virtual CircSLelement<E> *getNext() override {
				return static_cast<CircSLelement*> (SLelement<E>::getNext());
			}

			/**
			 * Sets the pointer to the next CircSLelement
			 * @param next CircSLelement<E> that should be assigned to the next
			 *	pointer
			 */
			void setNext(CircSLelement<E> *next) {
				SLelement<E>::setNext(next);
			}

			//		virtual const pair<string, string> getDataStructureRepresentation(const
			//						unsigned int& arr_size) const override final {
			//			return pair<string, string>("","");
			//		}
	};

} // namespace bridges
#endif
