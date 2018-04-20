#ifndef CANCER_INCIDENCE_H

#define CANCER_INCIDENCE_H
#include <string>

using namespace std;

namespace bridges {

/**
 *  @brief A class representing the attributes for cancer incidence.
 *
 * 	From the United States Cancer Statistics as part of the U.S. Center for 
 *	Disease Control, the following data set focuses on the crude rate for 
 *	all types of cancer reported for different demograpic groups. 
 *	Significant groupings include age, gender, race and geographical area.
 *
 *	http://www.cdc.gov/cancer/npcr/uscs/download_data.htm 
 *  Data: Courtesy of Corgis Datasets, 2017
 *
 *  @author Kalpathi Subramanian
 *	@date June, 2017
 *
 */

class CancerIncidence {

	private:
		 double 
			age_adjusted_rate,		// expected cancer rate, adjusted for age
			age_adjusted_rate_ci[2],	// confidence interval-lower,upper
			crude_rate,				// cancer rate adjusted by population 	
			crude_rate_ci[2];		// confidence interval

		int  
			count,					// incidence count
			year,					// reporting year
			population;				// population of this area

		string
			gender, 				 // gender (male, female, male and female
			race,					
			event_type,				 // incidence, mortality
			affected_area;			 // location, typically, state

		double loc[2];		 	// location (cartesian coords
			

	public:
		/**
	 	 * The constructor
	 	 */
		CancerIncidence () {
			loc[0] = loc[1]  = 0.0;
			age_adjusted_rate_ci[0] = age_adjusted_rate_ci[1] = 0.0;
			crude_rate_ci[0] = crude_rate_ci[1] = 0.0;
		}

		/*
		 * Get the expected cancer rate, adjusted for age of participants.
		 *
		 * @return cancer rate
		 *
		 */
		double getAgeAdjustedRate() {
			return age_adjusted_rate;
		}

		/**
	 	 * Set age adjusted cancer rate
	 	 *
	 	 * @param double aar
	 	 *
	 	 */
		void setAgeAdjustedRate(double aar) {
			age_adjusted_rate = aar;
		}
		
		/*
		 * Get the expected cancer rate confidence interval(lower), 
		 *	adjusted for age of participants.
		 *
		 * @return cancer conf interval (lower) rate
		 *
		 */
		double getAgeAdjustedCI_Lower() {
			return age_adjusted_rate_ci[0];
		}

		/**
		 * Set age adjusted cancer conf interval (lower) 
		 *
		 * @param double ci_l
		 *
		 */
		void setAgeAdjustedCI_Lower(double ci_l) {
			age_adjusted_rate_ci[0] = ci_l;
		}
		/*
		 * Get the expected cancer rate confidence interval(upper), 
		 *	adjusted for age of participants.
		 *
		 * @return cancer conf interval (lower) rate
		 *
		 */
		double getAgeAdjustedCI_Upper() {
			return age_adjusted_rate_ci[1];
		}

		/**
		 * Set age adjusted cancer conf interval (upper) 
		 *
		 * @param double ci_u
		 *
		 */
		void setAgeAdjustedCI_Upper(double ci_u) {
			age_adjusted_rate_ci[1] = ci_u;
		}
				
		/*
		 * Get the cancer rate, adjusted for population
		 *
		 * @return crude cancer rate
		 */
		double getCrudeRate() {
			return crude_rate;
		}
		/** 
		 * Set cancer rate, adjusted for population
		 *
		 * @param double cr
		 */
		void setCrudeRate(double cr) {
			crude_rate = cr;
		}
		/*
		 * Get the expected cancer crude rate confidence interval(lower), 
		 * adjusted for age of participants.
		 *
		 * @return cancer conf interval (lower) rate
		 *
		 */
		double getCrudeRate_CI_Lower() {
			return crude_rate_ci[0];
		}

		/**
		 * Set age adjusted cancer crude conf interval (lower) 
		 *
		 * @param double cr_l
		 *
		 */
		void setCrudeRate_CI_Lower(double cr_l) {
			crude_rate_ci[0] = cr_l;
		}
		/*
		 * Get the expected cancer crude rate confidence interval(upper), 
		 * adjusted for age of participants.
		 *
		 * @return cancer crude rate CI (upper) rate
		 *
		 */
		double getCrudeRate_CI_Upper() {
			return crude_rate_ci[1];
		}

		/**
		 * Set crude rate CI (upper) 
		 *
		 * @param double cr_u
		 *
		 */
		void setCrudeRate_CI_Upper(double cr_u) {
			crude_rate_ci[1] = cr_u;
		}

		/*
		 * Get the year of this cancer record
		 *
		 * @return year
		 */
		int getYear() {
			return year;
		}

		/*
		 * Set the year of this cancer record
		 *
		 * @param y  year 
		 */
		void setYear(int y) {
			year = y;
		}
		/*
		 * Get the gender of the group
		 *
		 * @return gender (male, female, male and female)
		 */
		string getGender() {
			return gender;
		}
		/** 
		 * Set gender
		 *
		 * @param g 
		 */
		void setGender(string g) {
			gender = g;
		}

		/*
		 * Get the race of the group
		 *
		 * @return race (All Races, etc)
		 */
		string getRace() {
			return race;
		}
		/** 
		 * Set race
		 *
		 * @param string r 
		 */
		void setRace(string r) {
			race = r;
		}

		/*
		 * Get the event type (incidence, mortality, etc)
		 *
		 * @return event (string)
		 */
		string getEventType() {
			return event_type;
		}
		/** 
		 * Set event type
		 *
		 * @param event (string) 
		 */
		void setEventType(string et) {
			event_type = et;
		}

		/*
		 * Get the population size
		 *
		 * @return population (int)
		 */
		int getPopulation() {
			return population;
		}
		/** 
		 * Set population size
		 *
		 * @param pop (int) 
		 */
		void setPopulation(int pop) {
			population = pop;
		}

		/*
		 * Get the cancer incidence area (state, region, etc)
		 *
		 * @return area (string)
		 */
		string getAffectedArea() {
			return affected_area;
		}
		/** 
		 * Set cancer incidenc area 
		 *
		 * @param area (string) 
		 */
		void setAffectedArea(string area) {
			affected_area = area;
		}

		/*
		 * Get the number of people affected in this group
		 *
		 * @return incidence count (int)
		 */
		int getCount() {
			return count;
		}
		/** 
		 * Set cancer incidence count
		 *
		 * @param c (int) 
		 */
		void setCount(int c) {
			count = c;
		}

		/*
		 * Get the X coordinate of location
		 *
		 * @return x coordinate
		 */
		double getLocationX() {
			return loc[0];
		}
		/**
		 *	Set location (X coord)
		 *
		 *	@param locX  X coordinate of location 
		 *
		 */
		 void setLocationX (double locX) {
			loc[0] = locX;
		}

		/*
		 * Get the Y coordinate of location
		 *
		 * @return y coordinate
		 */
		double getLocationY() {
			return loc[1];
		}
		/**
		 *	Set location (Y coord)
		 *
		 *	@param locX  Y coordinate of location 
		 *
		 */
		 void setLocationY (double locY) {
			loc[1] = locY;
		}
};

}	// namespace bridges

#endif
