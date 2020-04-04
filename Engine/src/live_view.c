/**
MIT License

Copyright (c) 2019 Ashwin Sivakumar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

The copyrights of all included third-party software belong to their respective
copyright holders.
**/


/**	@file live_view.c
*	@brief The live-view driver.
*
*
*	Live-view is a real-time, customizable library used to display gauges and 
*	plots for the data presented by the user. The library can display upto 6 plots at 
*	a time and a maximum of 20 gauge outputs.
*
*
*/

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "live_view.h"

#include<stdio.h>

#include<windows.h>
#include<process.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<dislin.h>
#include<ctype.h>
#include<string.h>

/*!  \var struct lv_gauge_data *lv_gd
*-
*/

/*!  \var struct lv_plot_data *lv_p
*-
*/
struct lv_gauge_data *lv_gd;
struct lv_plot_data *lv_p;

/*!  \var int lv_i1
*-
*/

/*!
*@var int lv_ip2
*-
*/

/*!
*@var int lv_ival
*-
*/
/*!
*@var int lv_flag
*-
*/
/*!
*@var int lv_mem
*-
*/
/*!
*@var int lv_i
*-
*/
/*!
*@var int lv_m
*-
*/
/*!
*@var int lv_n
*-
*/
/*!
*@var int lv_j
*-
*/
/*!
*@var int lv_j2
*-
*/
/*!
*@var int lv_pdelay
*-
*/
/*!
*@var int lv_gdelay
*-
*/
/*!
*@var float 
*-
*/
/*!
*@var float lv_xray
*-
*/
/*!
*@var int lv_f1
*-
*/
/*!
*@var int lv_idtext
*-
*/
/*!
*@var char lv_ulim
*-
*/
/*!
*@var char lv_ll
*-
*/
/*!
*@var int *ptf1
*-
*/
/*!
*@var int lv_n_gauges
*-
*/
/*!
*@var int lv_n_plots
*-
*/
/*!
*@var HANDLE lv_hMutex
*-
*/
/*!
*@def lv_NUM_THREADS
*-
*/


int lv_i1, lv_ip2, lv_ival, lv_flag = 0, lv_mem = 0;
int lv_i, lv_m, lv_n, lv_j = 1, lv_j2 = 1, lv_n = 100, lv_pdelay, lv_gdelay;
float lv_y1ray[100], lv_xray[100];

int lv_f1[20], lv_idtext[20];
char lv_ulim[10], lv_ll[10];

int *ptf1 = lv_f1;
int *pttxt = lv_idtext;

int lv_n_gauges, lv_n_plots;

HANDLE lv_hMutex;


#define lv_NUM_THREADS 3  

/**
* \brief Worker function that initiates multithreading  
*/
void worker(LPTHREAD_START_ROUTINE func, LPTHREAD_START_ROUTINE func1, LPTHREAD_START_ROUTINE func2)
{
	HANDLE hThreadArray[lv_NUM_THREADS];
	DWORD  dwThreadIdArray[lv_NUM_THREADS];

	lv_hMutex = CreateMutex(
		NULL,
		FALSE,
		NULL);

	hThreadArray[0] = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)func,
		NULL,
		0,
		&dwThreadIdArray[0]);

	hThreadArray[1] = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)func1,
		NULL,
		0,
		&dwThreadIdArray[1]);	
	hThreadArray[2] = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)func2,
		NULL,
		0,
		&dwThreadIdArray[2]);

	WaitForMultipleObjects(lv_NUM_THREADS, hThreadArray, TRUE, INFINITE);

	CloseHandle(hThreadArray[0]);
	CloseHandle(hThreadArray[1]);
	CloseHandle(hThreadArray[2]);

	CloseHandle(lv_hMutex);
}

/**
* \brief Handles graph plotting.
*/
DWORD WINAPI grPlt(LPVOID lpParam)
{
	int i1;
	metafl("cons");
	setpag("da4p");
	scrmod("REVERSE");
	winsiz(870, 2000);
	page(6000, 5500);
	disini();
	pagera();
	simplx();

	while (lv_j2)
	{
		if ((lv_j2 % 5 == 0 || lv_j2 == 1))
		{
			WaitForSingleObject(lv_hMutex, INFINITE);
			color("WHITE");
			pagera();
			if (lv_n_plots >= 1)
			{
				name((lv_p + 0)->xlabl, "x");
				name((lv_p + 0)->ylabl, "y");
				axspos(300, 1500);
				axslen(2350, 1350);
				ticks(15, "Y");
				setscl(lv_y1ray, lv_n, "Y");
				setscl(lv_xray, lv_n, "X");
				graf(0.0, 100, 0.0, 10.0, -1.0, 1.0, -1.0, 0.5);
				setrgb(0.7, 0.7, 0.7);
				grid(1, 1);
				color("white");
				curve(lv_xray, lv_y1ray, lv_n);
				endgrf();
				if (lv_n_plots >= 2)
				{
					name((lv_p + 1)->xlabl, "x");
					name((lv_p + 1)->ylabl, "y");
					axspos(3550, 1500);
					axslen(2350, 1350);
					graf(0.0, 100.0, 0.0, 10.0, -1.0, 1.0, -1.0, 0.5);
					setrgb(0.7, 0.7, 0.7);
					grid(1, 1);
					color("white");
					curve(lv_xray, lv_y1ray, lv_n);
					endgrf();
					if (lv_n_plots >= 3)
					{
						name((lv_p + 2)->xlabl, "x");
						name((lv_p + 2)->ylabl, "y");
						color("fore");
						axspos(300, 3300);
						axslen(2350, 1350);
						graf(0.0, 100.0, 0.0, 10.0, -1.0, 1.0, -1.0, 0.5);
						setrgb(0.7, 0.7, 0.7);
						grid(1, 1);
						color("white");
						curve(lv_xray, lv_y1ray, lv_n);
						endgrf();
						if (lv_n_plots >= 4)
						{
							name((lv_p + 3)->xlabl, "x");
							name((lv_p + 3)->ylabl, "y");
							color("fore");
							axspos(3550, 3300);
							axslen(2350, 1350);
							graf(0.0, 100.0, 0.0, 10.0, -1.0, 1.0, -1.0, 0.5);
							setrgb(0.7, 0.7, 0.7);
							grid(1, 1);
							color("white");
							curve(lv_xray, lv_y1ray, lv_n);
							endgrf();
							if (lv_n_plots >= 5)
							{
								name((lv_p + 4)->xlabl, "x");
								name((lv_p + 4)->ylabl, "y");
								color("fore");
								axspos(300, 5100);
								axslen(2350, 1350);
								graf(0.0, 100.0, 0.0, 10.0, -1.0, 1.0, -1.0, 0.5);
								setrgb(0.7, 0.7, 0.7);
								grid(1, 1);
								color("white");
								curve(lv_xray, lv_y1ray, lv_n);
								endgrf();
								if (lv_n_plots >= 6)
								{
									name((lv_p + 5)->xlabl, "x");
									name((lv_p + 5)->ylabl, "y");
									color("fore");
									axspos(3550, 5100);
									axslen(2350, 1350);
									graf(0.0, 100.0, 0.0, 10.0, -1.0, 1.0, -1.0, 0.5);
									setrgb(0.7, 0.7, 0.7);
									grid(1, 1);
									color("white");
									curve(lv_xray, lv_y1ray, lv_n);
									endgrf();
								}
							}
						}
					}
				}
			}
			sendbf();
			ReleaseMutex(lv_hMutex);
			Sleep(lv_pdelay);
			erase();
		}
		for (lv_i = 0; lv_i < lv_n; lv_i++)
		{
			lv_y1ray[lv_i] = lv_y1ray[lv_i + 1];
			lv_xray[lv_i] = lv_xray[lv_i + 1];
		}
		lv_xray[lv_n-1] = lv_n + lv_j2;
		lv_y1ray[lv_n-1] = rand() % 30 + 1;
		lv_j2++;
	}
	disfin();
	return 0;
}

/**
* \brief Handles scale value depiction.
*/

DWORD WINAPI scPlt(LPVOID lpParam)
{
	int i1;
	char f1s[20][10];
	while (lv_j)
	{
		if (lv_flag == 1)
		{

			WaitForSingleObject(lv_hMutex, INFINITE);

			for (i1 = 0; i1 < lv_n_gauges; i1++)
			{
				swgval(*(ptf1 + i1), (lv_gd + i1)->value);
				_gcvt((lv_gd + i1)->value, 3, f1s[i1]);
			}

			for (i1 = 0; i1 < lv_n_gauges; i1++)
			{
				swgtxt(*(pttxt + i1), f1s[i1]);
			}

			ReleaseMutex(lv_hMutex);
			Sleep(lv_gdelay);
		}

		for (lv_i = 0; lv_i < lv_n_gauges; lv_i++)
		{
			(lv_gd + lv_i)->value = ((float)rand() / (float)(RAND_MAX)) * ((lv_gd + lv_i)->ul);
		}

	}
	return 0;
}

/**
* \brief Handles creating template for the scale depiction.
*/

DWORD WINAPI template(LPVOID lpParam) 
{
	WaitForSingleObject(lv_hMutex, INFINITE);
	int ix;

	swgtit("FORCE AND LENGTH READINGS");
	swgpos(0, 0);

	lv_i1 = wgini("form");
	swgwin(4, 4, 100, 20);
	lv_ival = wgquit(lv_i1);
	swgwin(4, 5, 100, 30);
	lv_ip2 = wgbas(lv_i1, "form");

	swgclr(0.1, 0.1, 0.9, "PBAR");

	for (ix = 0; ix < lv_n_gauges; ix++)
	{
		if (ix % 2 == 0)
		{
			swgclr(0.1, 0.1, 0.9, "PBAR");
		}
		else
		{
			swgclr(0.1, 0.9, 0.1, "PBAR");
		}
		swgwin(5, 40 * (ix + 1) + 5, 55, 25);
		wglab(lv_ip2, (lv_gd + ix)->name);

		swgwin(80, 40 * (ix + 1) + 5, 20, 25);
		_itoa((lv_gd + ix)->ll, lv_ll, 10);
		wglab(lv_ip2, lv_ll);

		swgwin(110, 40 * (ix + 1), 400, 25);
		*(ptf1 + ix) = wgpbar(lv_ip2, 0, 30, 1);

		_gcvt((lv_gd + ix)->ul, 2, lv_ulim);

		swgwin(520, 40 * (ix + 1) + 5, 20, 25);
		wglab(lv_ip2, lv_ulim);

		swgwin(565, 40 * (ix + 1), 32, 25);
		*(pttxt + ix) = wgtxt(lv_ip2, " ");

		swgwin(600, 40 * (ix + 1) + 5, 25, 25);
		wglab(lv_ip2, (lv_gd + ix)->unit);
	}
	lv_flag = 1;
	ReleaseMutex(lv_hMutex);
	wgfin(); // Encountering this makes the dislin widgets are visible to the user.
	return 0;
}
 
void lv_gauge_par(char name[], int id, int l, double u,  char unit[], int gdly)
{
	
	(lv_gd + id)->ll = l;
	strcpy((lv_gd + id)->name, name);
	strcpy((lv_gd + id)->unit, unit);
	(lv_gd + id)->ul = u; 
	lv_gdelay = gdly;
	
}

void lv_gauge_init(int ng)
{
	
	int i;
	char nm[10] = "Value", nm1[10];
	float ulm = 30;
	lv_n_gauges = ng;
	lv_gd = (struct lv_gauge_data*) malloc(lv_n_gauges * sizeof(struct lv_gauge_data));
	
	for (i = 0; i < lv_n_gauges; i++)
	{	
		strcpy(nm, "Value");
		(lv_gd + i)->gid = i;
		_itoa(i, nm1, 10);
		strcpy((lv_gd+i)->name, strcat(nm, nm1));
		(lv_gd + i)->ll = 0;
		strcpy((lv_gd + i)->unit, "N");
		(lv_gd + i)->ul = 30;
		lv_gdelay = 10;
	}

	lv_mem++;
}

void lv_plot_par(char xl[], char yl[], int idp, int pdly)
{
	
	strcpy((lv_p + idp)->xlabl, xl);
	strcpy((lv_p + idp)->ylabl, yl);
	lv_pdelay = pdly;
}

void lv_plot_init(int np, int npts)
{
	
	int i;
	lv_n_plots = np;
	lv_n = npts;
	lv_pdelay = 5000;
	lv_p = (struct lv_plot_data*) malloc(np * sizeof(struct lv_plot_data));
	for (i = 0; i < lv_n_plots; i++)
	{
		strcpy((lv_p + i)->xlabl, "Time");
		strcpy((lv_p + i)->ylabl, "Force");
	}
	lv_mem++;
}

void lv_gauge_close()
{
	free(lv_gd);
	lv_gd = NULL;

}

void lv_plot_close()
{
	free(lv_p);
	lv_p = NULL;
}



void lv_update()
{
	if (lv_mem != 2)
	{
		printf("***Output failed!!***, Memory not assigned for the gauges and(or) the plots");
	}

	else
	{
		int run = 0;
		for (lv_i = 0; lv_i < lv_n_gauges; lv_i++)
		{
			(lv_gd + lv_i)->value = ((float)rand() / (float)(RAND_MAX)) * ((lv_gd + lv_i)->ul);
		}

		for (lv_i = 0; lv_i < lv_n; lv_i++)
		{
			lv_y1ray[lv_i] = (5 + rand() / (RAND_MAX / (30 - 5 + 1) + 1));
			lv_xray[lv_i] = lv_i;
		}

		if (run == 0)
		{
			worker(template, scPlt, grPlt);
			run = 1;
		}
	}
}



