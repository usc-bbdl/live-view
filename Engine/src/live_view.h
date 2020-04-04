/*! \mainpage Live-View
*  
* <b>INTRODUCTION</b>
* \n 
* The Live-View library employs functionalities of DISLIN, which is a high level plotting library developed by Max Planck Institute. \n Leveraging this along with multithreading 
* in C, the library enables the user to define various parameters for the output such as \n number of plots and scales, upper and lower limits, buffer size, update interval, etc.
* By doing so Live-View provides real-time \n graphical presentation of information that is desired.
*
* <b>EXAMPLE OUTPUT</b>
*
* \image html ex_op.png "" width = 700cm
* \image latex ex_op.png width=10cm
*
*
*<b>LEGAL</b>
*   * Live_View is distributed under the MIT license.
*		
*/

/*! \page page1 Tutorial Page
* 
* <b>PROCEDURE</b>
* \n
*	  1. Include the header file <em>"live_view.h"</em> in your program.
*	  2. Call <em>lv_gauge_init()</em> (max 20) and <em>lv_plot_init()</em> (max 6) to assign memory accordingly.
*	  3. Define gauge outline using <em> lv_gauge_par("Gauge Name", " Gauge ID", "Lower Limit", "Upper Limit", "Unit", "Update Frequency");</em>.
*	  4. Define plot outline using <em> lv_plot_par("X label", "Y label", "Plot ID", "Update Frequency");</em>
*     5. Now the real-time output can be obtained by invoking <em>lv_update()</em>.
*	  6. Quit the execution by clicking the "QUIT" button in the gauge window.
*	  7. Remember to call the functions <em>lv_gauge_close()</em> and <em>lv_plot_close()</em> to unassign and release the memory used.\n
*
*
*<b>EXECUTION EXAMPLE</b>
* \n
*@code
#include "live_view.h"
#include<Windows.h>
#include<stdio.h>

int main()
{
	lv_gauge_init(14);
	lv_gauge_par("Motor", 1, 5, 30, "cm", 1);

	lv_plot_init(7, 50);
	lv_plot_par("Time", "Stress", 0, 5000);

	lv_update();

	lv_gauge_close();
	lv_plot_close();

	return 0;
}
*@endcode
*
*/


/**
*  @file live_view.h
*  @brief Function prototypes for the live-view driver
*
*  This contains the function prototypes for the
*  live-view driver and structures for the gauges and plots.
*
*
*  @author Suraj Chakravarthi Raja 
*  @author Ashwin Sivakumar
*  @date 26 Aug 2019
*  @bug no known bugs
*/

#pragma once

/** @struct lv_gauge_data
*	@brief This structure holds the parameters for gauge depiction.
*	@var lv_gauge_data::name
*	Member 'name' contains the label to be given to a gauge.
*	@var lv_gauge_data::gid
*	Member 'gid' contains the ID associated with a gauge.
*	@var lv_gauge_data::ll
*	Member 'll' is used to specify the lower limit of a gauge.
*	@var lv_gauge_data::ul
*	Member 'ul' is used to specify the upper limit of a gauge.
*	@var lv_gauge_data::unit
*	Member 'unit' is used to specify the unit associated with a gauge.
*	@var lv_gauge_data::value
*	Member 'value' is the value of the reading displayed on the gauge.
*/

struct lv_gauge_data
{
	char name[20];
	int ll;
	double value;
	double ul;
	char unit[5];
	int gid; 
};

/** @struct lv_plot_data
*	@brief This structure holds the parameters for gauge depiction.
*	@var lv_plot_data::xlabl
*	Member 'xlabl' contains the X axis label to be given to a plot.
*	@var lv_plot_data::ylabl
*	Member 'ylabl' contains the Y axis label to be given to a plot.
*	@var lv_plot_data::plid
*	Member 'plid' contains the ID associated with a plot.
*/

struct lv_plot_data
{
	char xlabl[20];
	char ylabl[20];
	int plid;
};

/** @brief Used to read the number of gauges required to be displayed.
*
*
*	Memory is allocated in accordance with the value passed to this function and 
*	a pointer is assigned to the 1st location in memory. It also assigns  
*	default values to the the gauge_data members. 
*
*
*/
void lv_gauge_init(int);

/** @brief Assigns respective gauges with user defined parameter names &
*		   values.
*	
*
*	The function is used to assign custom values to a specific gauge 
*	generated by lv_gauge_init() by referencing the gauge ID as one of the parameter
*	to this.
*
*
*/
void lv_gauge_par(char[], int, int, double, char[], int);


/** @brief Used to read the number of plots required to be displayed.
*
*
*	Memory is allocated in accordance with the value passed to this function and
*	a pointer is assigned to the 1st location in memory. It also assigns
*	default values to the the plot_data members.
*
*
*/
void lv_plot_init(int, int);

/** @brief Assigns respective plots with user defined parameter names.
*
*
*	The function is used to assign custom axis names to a specific plot
*	generated by lv_plot_init() by referencing the plot ID as one of the parameter.
*
*
*/
void lv_plot_par(char[], char[], int, int);

/**	@brief Initiates the threads and displays the necessary gauges and
*		   plots.
*
*	A call to this function invokes the worker function which initiates the threads to display
*	the gauges and plots in real-time as specified by the user. It also performs a check, if memory has been
*	allocated for the creation of gauges and plots. If not the the execution fails.
*
*
*/
void lv_update();

/**	@brief Deallocates the memory assigned for the gauges.
*	
*	The function deallocates and assigns NULL to the memory locations held for the creation 
*	of gauges.
*
*
*/
void lv_gauge_close();

/**	@brief Deallocates the memory assigned for the plots.
*
*
*	The function deallocates and assigns NULL to the memory locations held for the creation
*	of plots.
*
*
*/
void lv_plot_close();




