#include "chart.h"

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QChart(QChart::ChartTypeCartesian, parent, wFlags)
{
    series = new QSplineSeries(this);

    this->legend()->hide();
    this->addSeries(series);
    this->createDefaultAxes();

    xrange = 20;
    this->axes(Qt::Horizontal).first()->setRange(0, xrange);
    this->axes(Qt::Vertical).first()->setRange(0, 10);
}

Chart::~Chart()
{
    delete series;
}

void Chart::appendPoint(double x, double y)
{
    series->append(x, y);

    if (y < ymin) ymin = y;
    if (y > ymax) ymax = y;
    this->axes(Qt::Vertical).first()->setRange(ymin, ymax);

    if (x + 2 > xrange) this->axes(Qt::Horizontal).first()->setRange(x + 2 - xrange, x + 2);
}
