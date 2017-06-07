#ifndef BUTTONFORM_H
#define BUTTONFORM_H

#include "ui_form.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_series_data.h>

class MyForm: public QWidget, private Ui::Form 
{
	Q_OBJECT

public:
	MyForm(QWidget *parent = 0);
	float price[10][180];
	
	QwtPlot *myPlot[10];

	QwtPlotCurve* curve[10];

	QwtPointSeriesData* myData[10];

	QVector < QPointF > *samples[10];
	
	int plot_k;
	
	void plot(void);

public slots:

};

#endif

