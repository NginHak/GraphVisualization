#include "visualization.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>
#include <QtCore/QtMath>
#include <QtGui/QImage>
#include"ReadFile/readfile.h"
#include<iostream>
Visualization::Visualization(QWidget *parent)
    :QWidget(parent){

    layout=new QGridLayout;
    view = new QChartView(createPiChart());
    layout->addWidget(view);
    setLayout(layout);
    view->chart()->setTheme(QChart::ChartThemeBlueCerulean);
}

QChart *Visualization::createBarChart() const
{
    QChart *chart = new QChart();

    chart->setTitle("Bar chart");
    QBarSet *set0 = new QBarSet("Jane");
    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    QBarSeries *series = new QBarSeries();
    series->append(set0);
    chart->addSeries(series);
    chart->setTitle("Simple barchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTheme(
                QChart::ChartThemeBlueCerulean);
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    return chart;
}

QChart *Visualization::createPiChart() const
{
    QPieSeries *series = new QPieSeries();
        series->append("Jane", 1);
        series->append("Joe", 2);
        series->append("Andy", 3);
        series->append("Barbara", 4);
        series->append("Axel", 5);

        QPieSlice *slice = series->slices().at(1);
        slice->setExploded();
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkGreen, 2));
        slice->setBrush(Qt::green);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Simple piechart example");
        chart->legend()->hide();
        return chart;
}

QChart *Visualization::createScatterChart() const
{
    QScatterSeries *series0 = new QScatterSeries();
    series0->setName("scatter1");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(15.0);

    QScatterSeries *series1 = new QScatterSeries();
    series1->setName("scatter2");
    series1->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series1->setMarkerSize(20.0);

    QScatterSeries *series2 = new QScatterSeries();
    series2->setName("scatter3");
    series2->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series2->setMarkerSize(30.0);

    series0->append(0, 6);
    series0->append(2, 4);
    series0->append(3, 8);
    series0->append(7, 4);
    series0->append(10, 5);

    *series1 << QPointF(1, 1) << QPointF(3, 3) << QPointF(7, 6) << QPointF(8, 3) << QPointF(10, 2);
    *series2 << QPointF(1, 5) << QPointF(4, 6) << QPointF(6, 3) << QPointF(9, 5);

    QPainterPath starPath;
    starPath.moveTo(28, 15);
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(14 + 14 * qCos(0.8 * i * M_PI),
                        15 + 14 * qSin(0.8 * i * M_PI));
    }
    starPath.closeSubpath();

    QImage star(30, 30, QImage::Format_ARGB32);
    star.fill(Qt::transparent);

    QPainter painter(&star);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QRgb(0xf6a625));
    painter.setBrush(painter.pen().color());
    painter.drawPath(starPath);

    series2->setBrush(star);
    series2->setPen(QColor(Qt::transparent));
    QChart*chart=new QChart;
    chart->addSeries(series0);
    chart->addSeries(series1);
    chart->addSeries(series2);

    chart->setTitle("Simple scatterchart example");
    chart->createDefaultAxes();
    chart->setDropShadowEnabled(false);
    chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);

    return chart;

}

QChart *Visualization::createAreaChart() const
{


}

QChart *Visualization::createSlineChart() const
{
    QSplineSeries *series = new QSplineSeries();
    series->setName("spline");
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) <<
               QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("Simple spline chart example");
    chart->createDefaultAxes();
    chart->axisY()->setRange(0, 10);
    return chart;
}

QChart *Visualization::createLineChart() const
{
      QLineSeries *series = new QLineSeries();
      series->append(0, 6);
        series->append(2, 4);
        series->append(3, 8);
        series->append(7, 4);
        series->append(10, 5);
        *series << QPointF(11, 1)
                << QPointF(13, 3)
                << QPointF(17, 6)
                << QPointF(18, 3)
                << QPointF(20, 2);
        QChart *chart = new QChart();
            chart->legend()->hide();
            chart->addSeries(series);
            chart->createDefaultAxes();
            chart->setTitle("Simple line chart example");
            return chart;
}

void Visualization::createChart(int index)
{
    QChartView *viewer;
    if(index==0)
    {
        layout->removeWidget(view);
        viewer = new QChartView(createPiChart());
        view = viewer;
        layout->addWidget(view);

    } else if(index==1)
    {
        layout->removeWidget(view);
        viewer = new QChartView(createBarChart());
        view = viewer;
        layout->addWidget(view);
    } else if(index==2)
    {
        layout->removeWidget(view);
        viewer = new QChartView(createScatterChart());
        view = viewer;
        layout->addWidget(view);
    }else if(index==3)
    {
        layout->removeWidget(view);
        viewer = new QChartView(createLineChart());
        view = viewer;
        layout->addWidget(view);
    }else if(index==4)
    {
        layout->removeWidget(view);
        viewer = new QChartView(createSlineChart());
        view = viewer;
        layout->addWidget(view);
    }

}
void Visualization::openFile(const QString &fileName)
{
    ReadFIle *file=new ReadFIle();
    file->openFile(fileName);

}

void Visualization::setTheme(int  index)
{
    if(index==0)
        view->chart()->setTheme(QChart::ChartThemeBlueCerulean);
    else
    if(index==1)
        view->chart()->setTheme(QChart::ChartThemeLight);
    else
    if(index==2)
        view->chart()->setTheme(QChart::ChartThemeDark);
    else
     if(index==3)
        view->chart()->setTheme(QChart::ChartThemeBrownSand);
    else
     if(index==4)
        view->chart()->setTheme(QChart::ChartThemeBlueNcs);
    else
     if(index==5)
        view->chart()->setTheme(QChart::ChartThemeHighContrast);
    else
     if(index==6)
        view->chart()->setTheme(QChart::ChartThemeBlueIcy);
    else
     if(index==7)
        view->chart()->setTheme(QChart::ChartThemeQt);

}
