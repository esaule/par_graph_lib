/**
 * @author Kalpathi Subramanian
 * @date  10/5/16
 *
 *  @brief This class can be used to instantiate Circular Doubly Linked 
 *  List Elements.

 *  Structurally they are the same as doubly linked elements
 *  except that each node constructed with the next and the previous pointers 
 *  pointing to itself.

 *  User's implementation of the circularly linked list needs to ensure that
 *  the last node's next pointer points to the first node and the first node's
 *  previous pointer points to the last node, as the visualization generation 
 *  is dependent on this.

 *  Elements have labels (string) that are displayed on the visualization.
 *  Elements take an generic object E as a user defined parameter, which can
 *  any native type or object.
 *  Elements contain a visualizer object for setting visual attributes (color, 
 *  shape, opacity, size), necessary for displaying them in a web browser
 *      
 */
#include "DLelement.h"

namespace bridges{

template <typename E>
class CircDLelement : public  DLelement<E>{
	public:
		/** 
	 	 *	Constructs an empty CircDLelement with next and prev pointers set 
	 	 *	to itself
		*/
		CircDLelement() : DLelement<E> (this, this, E()) {
		}
	
		/** Constructs a CircDLelement labeled "label", holding an object "e", 
	 	 *	with next and prev pointers set to itself
	 	 * 	@param e the genereic object that this CircDLelement is holding
	 	 * 	@param label the label for this CircDLelement that shows up on the 
	 	 *		Bridges visualization
	 	 */
		CircDLelement (E e, string label) 
				: DLelement<E>(this, this, e, label) {
		}

		/** 
	 	 *	Constructs an empty DLelement with the next pointer set to the 
		 *	CircDLelement "next" and the prev pointer set to CircDLelement 
		 *	"prev". 
		 *
		 * 	@param next the DLelement that should be assigned to the next 
		 *		pointer
		 *	@param prev the DLelement that should be assigned to the prev 
		 *		pointer
		 *
		 */
		CircDLelement(CircDLelement<E> next, CircDLelement<E> prev) 
							: DLelement<E>(this, this) {
		}

		/** 
	 	 *	Constructs a DLelement holding an object "e", with the next pointer 
	 	 *	set to the DLelement "next" and the prev pointer set to DLelement 
	 	 *	"prev". 
	 	 *
	 	 *	@param e the genereic object that this CircDLelement is holding
	 	 *	@param next the CircDLelement that should be assigned to the next 
	 	 *		pointer
		 *	@param prev the CircDLelement that should be assigned to the prev 
	 	 *	pointer
	 	 *
	 	 */
		CircDLelement(E e, CircDLelement<E> next, CircDLelement<E> prev) 
									: DLelement<E>(this, this, e) {
		}
	
		/**
	 	 *	This method gets the data structure type
	 	 *
	 	 *	@return  The date structure type as a string
	 	 **/
		 string getDSType() {
			 return "CircularDoublyLinkedList";
		 }

		/**
	 	 * This method returns the pointer to the next DLelement
		 * @return the DLelement assigned to the next pointer
		 */
		const CircDLelement<E> *getNext() const {
			return static_cast<const CircDLelement*>(SLelement<E>::getNext());
		}
	
		/**
	 	 * This method sets the pointer to the next DLelement
		 *
	 	 * @param next the DLelement that should be assigned to the next pointer
	 	 *
	 	 */
		 void setNext(CircDLelement<E> *next) {
			 DLelement<E>::setNext(next);
		 }
	

		/**
		 * This method returns the pointer to the previous DLelement
	 	 * @return the DLelement assigned to the prev pointer
	 	 */
		 const CircDLelement<E> *getPrev() const {
			 return static_cast<const CircDLelement*>(SLelement<E>::getPrev());
		 }

		/**
		 * This method sets the pointer to the previous DLelement
	 	 * @param prev the DLelement that should be assigned to the prev pointer
	 	 */
		void setPrev(CircDLelement<E> *prev) {
			DLelement<E>::setPrev(prev);
		}
};

} //namespace bridges
