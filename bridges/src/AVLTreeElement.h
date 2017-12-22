#ifndef AVL_ELEMENT_H
#define AVL_ELEMENT_H

#include "BSTElement.h" //string, sstream, using std

namespace bridges{
/**
 * @brief This class can be used to create avl tree elements, derived from 
 *	BSTElement
 *
 *  This class extends the BSTElement class by adding height and balance factor
 *  attributes to allow for easier use in a avl tree implementation.
 *
 * Generic Parameters:
 *      K that is the search key type,
 *      E the application data type
 *
 * @author Kalpathi Subramanian
 * @date 6/18/15, 7/15/16
 */
template <typename K, typename E>
class AVLTreeElement : public BSTElement<K,E>
{
    private:
        // The height and balance factor values
        int height = 0, balFactor = 0;
    public:
        /**
         * Constructs a AVLTreeElement with the provided value, label, key,
         * setting the left and right AVLTreeElements to NULL.
         * The defaults will be used if not provided.
         *
         * @param val The data to hold
         * @param lab The label to show
         * @param k The key for ordering
         */
        AVLTreeElement(const K& k, const E& val = E(), const string& lab = string()) : BSTElement<K,E>(k,nullptr,nullptr,val,lab){}
        /** @return the data structure type */
        virtual const string getDStype() const override {return "AVLTree";}
        /** @return The height of this AVLTreeElement */
        int getHeight() const {return height;}
        /**
         * Set the height to "h" @param h The height of this AVLTreeElement
         *
         * @param h the height of the tree at this node
         */
        void setHeight(const int& h) {height = h;}
        /** @return The balance factor of this AVLTreeElement */
        int getBalanceFactor() const {return balFactor;}
        /**
         * Set the balance factor to "bf" @param bf The balance factor of this
         * AVLTreeElement
         *
         * @param bf  the balance factor to set at this node
         */
        void setBalanceFactor(const int& bf) {balFactor = bf;}
        /** @return The left child */
        virtual AVLTreeElement* getLeft() override {return static_cast<AVLTreeElement*>(BSTElement<K,E>::getLeft());}
        /**
         * Constant version
         *
         * @return The left child
         */
        virtual const AVLTreeElement* getLeft() const override {return static_cast<const AVLTreeElement*>(BSTElement<K,E>::getLeft());}
        /**
         * Sets left to "l"
         *
         * @param l The left tree element
         */
        void setLeft(AVLTreeElement* l){BSTElement<K,E>::setLeft(l);}
        /** @return The right child */
        virtual AVLTreeElement* getRight() override {return static_cast<AVLTreeElement*>(BSTElement<K,E>::getRight());}
        /**
         * Constant version
         *
         * @return The right child
         */
        virtual const AVLTreeElement* getRight() const override {return static_cast<const AVLTreeElement*>(BSTElement<K,E>::getRight());}
        /**
         * Sets right to "r"
         *
         * @param r The right BSTElement
         */
        void setRight(AVLTreeElement* r){BSTElement<K,E>::setRight(r);}
    private:
        /** adds height and balance factor attributes to the BST Element representation */
        virtual const string getRepresentation() const override final
        {
            string json = BSTElement<K,E>::getRepresentation();
            return json.insert(json.size()-1, COMMA+QUOTE+"height"+QUOTE+COLON+to_string(height)+COMMA+QUOTE+"balance_factor"+QUOTE+COLON+to_string(balFactor));
        }
}; //end of BSTElement class
}//end of bridges namespace
#endif
