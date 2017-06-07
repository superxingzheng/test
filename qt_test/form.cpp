#include "form.h"

MyForm::MyForm(QWidget *parent) :
		QWidget(parent) {

	setupUi(this);
	
	plot_k = 0;
}

void MyForm::plot(void) {
	
	curve[0] = new QwtPlotCurve("Curve 1");
	curve[1] = new QwtPlotCurve("Curve 2");
	curve[2] = new QwtPlotCurve("Curve 3");
	curve[3] = new QwtPlotCurve("Curve 4");
	curve[4] = new QwtPlotCurve("Curve 5");
	curve[5] = new QwtPlotCurve("Curve 6");
	curve[6] = new QwtPlotCurve("Curve 7");
	curve[7] = new QwtPlotCurve("Curve 8");
	curve[8] = new QwtPlotCurve("Curve 9");
	curve[9] = new QwtPlotCurve("Curve 10");

	myData[plot_k] = new QwtPointSeriesData;
	myPlot[plot_k] = new QwtPlot(this);
	samples[plot_k] = new QVector<QPointF>;

	for (int i = 0; i < 179; i++) {
		if (price[plot_k][i] == 0.0 && i > 0) {
			price[plot_k][i] = price[plot_k][i - 1];
		}
		if (price[plot_k][0] == 0.0) {
			price[plot_k][0] = price[plot_k][1];
		}
		samples[plot_k]->push_back(QPointF(float(i + 1), price[plot_k][i]));
	}

	myData[plot_k]->setSamples(*samples[plot_k]);

	curve[plot_k]->setData(myData[plot_k]);
	curve[plot_k]->attach(myPlot[plot_k]);

	myPlot[plot_k]->replot();
}
