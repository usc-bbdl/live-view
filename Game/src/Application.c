#include "live_view.h"
#include<Windows.h>
#include<stdio.h>

int main()
{	
	lv_gauge_init(14);
	lv_gauge_par("Motor", 1, 5, 30, "cm", 1);
	
	lv_plot_init(7,50);
	lv_plot_par("Time" , "Stress", 0, 5000);

	lv_update();

	lv_gauge_close();
	lv_plot_close();

	return 0;
}