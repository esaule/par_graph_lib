#ifndef DLelement_H
#define DLelement_H

#include "SLelement.h" //string, using std

namespace bridges{
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
class DLelement: public SLelement<E>
{
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
				const string& lab = string()) : SLelement<E>(n,val,lab) {
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
        DLelement (const E& val = E(),const string& lab = string()) : 
					DLelement(nullptr,nullptr,val,lab) {
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
            if (this->next!=n && this->next!=prev){
							//if different, remove old link data
				this->links.erase(this->next);
			} 
            if((this->next=n)){
				this->links[this->next];
			} 
        }
        /** @return The previous DLelement */
        DLelement* getPrev() {return prev;}
        /**
         * Constant version
         *
         * @return The previous DLelement
         */
        const DLelement* getPrev() const {return prev;}
        /**
         * Sets prev to "p"
         *
         * @param p The previous DLelement
         */
        void setPrev(DLelement* p)
        {
            if(prev!=p && this->next!=prev){this->links.erase(prev);} //if different, remove old link data
            if((prev=p)){this->links[prev];}//set prev to p and if not null, create default link data if none already present
        }

}; //end of DLelement class
}//end of bridges namespace
#endif
