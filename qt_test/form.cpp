#include "form.h"
 
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_series_data.h>
 
 
MyForm::MyForm(QWidget *parent) : QWidget(parent)
{
  setupUi(this);
 
  QwtPlot *myPlot = new QwtPlot(this);
 
  QwtPlotCurve *curve1 = new QwtPlotCurve("Curve 1");
 
  QwtPointSeriesData* myData = new QwtPointSeriesData;
 
  QVector<QPointF>* samples = new QVector<QPointF>;
  
  samples->push_back(QPointF(1.0,1.0));
  samples->push_back(QPointF(2.0,4.0));
  samples->push_back(QPointF(3.0,9.0));
  samples->push_back(QPointF(4.0,16.0));
  samples->push_back(QPointF(5.0,25.0));
  samples->push_back(QPointF(6.0,36.0));
  
  myData->setSamples(*samples);
  
  curve1->setData(myData);
 
  curve1->attach(myPlot);
 
  myPlot->replot();
}
