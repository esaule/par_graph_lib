#ifndef BST_ELEMENT_H
#define BST_ELEMENT_H

#include <sstream>

#include "BinTreeElement.h" //string, sstream, using std

namespace bridges {
	/**
	 * @brief This class can be used to create binary search tree elements, derived
	 *  from BinTreeElement
	 *
	 * This class extends the BinTreeElement class by adding a key property
	 * to allow for use in a binary search tree implementation.
	 *
	 * Generic Parameters:
	 *      K that is the search key type,
	 *      E the application data type
	 *
	 * @author Kalpathi Subramanian
	 * @date 6/18/15, 7/17/16
	 */
	template <typename K, typename E>
	class BSTElement : public BinTreeElement<E> {
		protected:
			K key = K();// The search key value
		public:
			/**
			 * Constructs a BSTElement with the provided value, label, key,
			 * left and right BSTElements.  The defaults will be used if
			 * not provided.
			 *
			 * @param k The key for ordering
			 * @param val The data to hold
			 * @param lab The label to show
			 * @param l The left BSTElement
			 * @param r The right BSTElement
			 */
			BSTElement(const K& k, BSTElement* l, BSTElement* r, const E& val = E(),
				const string& lab = string())
				: BinTreeElement<E>(l, r, val, lab), key(k) {
			}
			/**
			 * Constructs a BSTElement with the provided value, label, key,
			 * setting the left and right BSTElements to NULL.
			 * The defaults will be used if not provided.
			 *
			 * @param val The data to hold
			 * @param lab The label to show
			 * @param k The key for ordering
			 */
			BSTElement(const K& k, const E& val = E(), const string& lab = string())
				: BSTElement(k, nullptr, nullptr, val, lab) {
			}
			/** @return the data structure type */
			virtual const string getDStype() const override {
				return "BinarySearchTree";
			}
			/** @return The key of this BSTElement */
			K getKey() const {
				return key;
			}
			/**
			 * Set key to "k"
			 *
			 * @param k The key of this BSTElement
			 */
			void setKey(const K& k) {
				key = k;
			}
			/** @return The left child */
			virtual BSTElement* getLeft() override {
				return static_cast<BSTElement*>(BinTreeElement<E>::getLeft());
			}
			/**
			 * Constant version
			 *
			 * @return The left child
			 */
			virtual const BSTElement* getLeft() const override {
				return static_cast<const BSTElement*>(BinTreeElement<E>::getLeft());
			}
			/**
			 * Sets left to "l"
			 *
			 * @param l The left child
			 */
			void setLeft(BSTElement* l) {
				BinTreeElement<E>::setLeft(l);
			}
			/** @return The right child */
			virtual BSTElement* getRight() override {
				return static_cast<BSTElement*>(BinTreeElement<E>::getRight());
			}
			/**
			 * Constant version
			 *
			 * @return The right child
			 */
			virtual const BSTElement* getRight() const override {
				return static_cast<const BSTElement*>(BinTreeElement<E>::getRight());
			}
			/**
			 * Sets right to "r"
			 *
			 * @param r The right BSTElement
			 */
			void setRight(BSTElement* r) {
				BinTreeElement<E>::setRight(r);
			}
		protected:
			virtual const string getElementRepresentation() const override {
				string json = Element<E>::getElementRepresentation();
				stringstream conv;
				conv << key;
				return json.insert(
						json.size() - 1,
						COMMA + QUOTE + "key" + QUOTE + COLON + QUOTE + conv.str() +
						QUOTE
					);
			}
	}; //end of BSTElement class


}//end of bridges namespace
#endif
