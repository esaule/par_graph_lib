#ifndef LINK_VISUALIZER_H
#define LINK_VISUALIZER_H

#include "Color.h" //string, using std

namespace bridges{
/**
 * @brief This class maintains the visual properties of links within data structures.
 *
 * This class is used to keep the visual properties of links that are part of
 * data structures such as linked lists, pointer based trees, link based
 * graph representations, etc.  Relevant attributes include color and thickness
 *
 * Objects of this class are stored as properties of Elements.
 * A user may manipulate the LinkVisualizer returned from the Element's getLinkVisualizer() method.
 *
 * BRIDGES supports color of any legal named CSS or #hexadecimal value. Defalt:
 *  opaque black
 * Thickness values must range from [0.0,10.0]. Default: 1.0
 *
 * @author Kalpathi Subramanian, Dakota Carmer
 * @date 6/29/15, 6/10/16
 */
class LinkVisualizer
{
    public:

        static constexpr double DEFAULT_THICKNESS = 1.0;
        static const Color DEFAULT_COLOR; //SteelBlue

    private:

        Color color=DEFAULT_COLOR;
        double thickness=DEFAULT_THICKNESS;
        double weight = 1.0;

    public:
		/**
		 * Constructs a LinkVisualizer with the specified color and thickness.
		 * The defaults will be used if not provided (black,1)
		 *
		 * @param col Link color
		 * @param thick Link thickness
		 *
		 */
        LinkVisualizer(Color col = DEFAULT_COLOR,
					double th = DEFAULT_THICKNESS): 
					color(col) {
			setThickness(th);
		}

        /**
         * Set the thickness to "thick"
         * Valid Range:[0,10] Default: 1
         *
         * @param thick The size in pixels of the link's line weight
         * @throw string If invalid thickness
         */
        void setThickness(const double& th) {
			if (th < 0|| 10 < th)
				throw "Invalid Thickness Value.. "+to_string(th)+
					" Must be in the [0.0,10.0] range"; 
			else 
				thickness=th;
        }
        /** 
		 *	@return Size in pixels of the link's line thickness 
		 */
		double getThickness() const {
			return thickness;
		}

        /**
         * Set the link weight to "wt"
         * Valid Range: determined by application, can be negative
         *
         * @param wt The size in pixels of the link's line weight
         * @throw string If invalid thickness
         */
        void setWeight(const double& wt) {
			weight = wt;
		}

		/** 
		 *	@return link weight 
		 */
        double getWeight() const {
			return weight;
		}

        /**
         * Set the color to "col", default black
         *
         * @param color The color of the element
         */
		void setColor(const Color& col){
			color = col;
		}
        /** 
		 *	@return The color of the link 
		 */
        Color getColor() const {
			return color;
		}
}; //end of LinkVisualizer class

constexpr double LinkVisualizer::DEFAULT_THICKNESS;
const Color LinkVisualizer::DEFAULT_COLOR("SteelBlue");

}//end of bridges namespace
#endif
