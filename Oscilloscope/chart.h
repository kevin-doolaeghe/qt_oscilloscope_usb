#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>

QT_CHARTS_USE_NAMESPACE

class Chart : public QChart
{
public:
    Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~Chart();
    void appendPoint(double x, double y);
private:
    QSplineSeries *series;
    qreal xrange;
    qreal ymin;
    qreal ymax;
};

#endif // CHART_H
