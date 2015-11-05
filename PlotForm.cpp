/*
 * File:   PlotForm.cpp
 * Author: Ivan
 *
 * Created on 27 Октябрь 2011 г., 17:14
 */

#include "PlotForm.h"
#include <math.h>
#include <qwt/qwt_plot_layout.h>
#include <qwt/qwt_scale_draw.h>

PlotForm::PlotForm() {
    m_data[0] = 0;
    m_data[1] = 0;
    m_data[2] = 0;
    m_data_len = 0;
    x_axis_type = 0;
    widget.setupUi(this);

    curve[0].setColor(Qt::yellow);
    curve[0].attach(widget.qwtPlot);
    curve[0].setVisible(true);
    curve[1].setColor(Qt::green);
    curve[1].attach(widget.qwtPlot);
    curve[1].setVisible(true);
    setDataLen(512);
    noise();

    // grid 
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->enableXMin(true);
    grid->setMajorPen(QPen(Qt::white, 0, Qt::DotLine));
    grid->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
    grid->attach(widget.qwtPlot);

    //scale
    widget.qwtPlot->setCanvasBackground(QColor(Qt::black));
    
    QwtPlotPicker *d_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn, widget.qwtPlot->canvas());
    d_picker->setStateMachine(new QwtPickerDragPointMachine());
    d_picker->setRubberBandPen(QColor(Qt::green));
    d_picker->setRubberBand(QwtPicker::CrossRubberBand);
    d_picker->setTrackerPen(QColor(Qt::green));
    
    QwtPlotZoomer* zoomer = new QwtPlotZoomer( widget.qwtPlot->canvas() );
    zoomer->setRubberBandPen( QColor( Qt::white ) );
    zoomer->setTrackerPen( QColor( Qt::white ) );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3, Qt::RightButton );

    mr_center.setLineStyle(QwtPlotMarker::VLine);
    mr_center.setLinePen(QPen(Qt::darkRed, 0, Qt::SolidLine));
    mr_center.setXValue(840.0);
    mr_center.attach(widget.qwtPlot);
    mr_center.setVisible(false);
    mr_left.setLineStyle(QwtPlotMarker::VLine);
    mr_left.setLinePen(QPen(Qt::darkRed, 0, Qt::DotLine));
    mr_left.setXValue(830.0);
    mr_left.attach(widget.qwtPlot);
    mr_left.setVisible(false);
    mr_right.setLineStyle(QwtPlotMarker::VLine);
    mr_right.setLinePen(QPen(Qt::darkRed, 0, Qt::DotLine));
    mr_right.setXValue(850.0);
    mr_right.attach(widget.qwtPlot);
    mr_right.setVisible(false);
    

    QwtPlotPanner *panner = new QwtPlotPanner( widget.qwtPlot->canvas() );
    panner->setMouseButton( Qt::MidButton );
    widget.qwtPlot->plotLayout()->setAlignCanvasToScales(true);

    dvalidator = new QDoubleValidator();
    widget.leMin->setValidator(dvalidator);
    widget.leMax->setValidator(dvalidator);
    
    connect(widget.btnYAxisLog, SIGNAL(clicked(bool)), this, SLOT(setScaleEngineY(bool)));
    connect(widget.btnAutoScale, SIGNAL(clicked(bool)), this, SLOT(setAutoScale(bool)));
    connect(widget.btnSave, SIGNAL(clicked()), this, SLOT(save()));
    connect(widget.btnZoomIn , SIGNAL(clicked()), this, SLOT(zoomIn ()));
    connect(widget.btnZoomOut, SIGNAL(clicked()), this, SLOT(zoomOut()));
//    connect(widget.leMin, SIGNAL(valueChanged(double)), this, SLOT(rescale(double)));
//    connect(widget.leMax, SIGNAL(valueChanged(double)), this, SLOT(rescale(double)));
}

PlotForm::~PlotForm() {

}

void PlotForm::setDataLen(int value) {
    if (value < 1) return;
    if (m_data[0] != 0) delete m_data[0];
    if (m_data[1] != 0) delete m_data[1];
    if (m_data[2] != 0) delete m_data[2];
    m_data_len = value;
    m_data[0] = new double[m_data_len];
    m_data[1] = new double[m_data_len];
    m_data[2] = new double[m_data_len];
    noise();
}

void PlotForm::setData(float **data, int len) {
    
//    FILE *f;
//    f = fopen("d:/tmp/ndata.csv", "a");
    for (int i = 0; i < len && i < m_data_len; ++i) {
        m_data[1][i] = (double)(data[0][i]);
        m_data[2][i] = (double)(data[1][i]);
//        fprintf(f, "%lf\t%lf\n", m_data[1][i], m_data[2][i]);
    }
//    fclose(f);
    
    curve[0].setRawSamples(m_data[0], m_data[1], m_data_len);
//    widget.qwtPlot->setAxisScale(QwtPlot::xBottom, curve.minXValue(), curve.maxXValue());
    widget.qwtPlot->replot();
}

void PlotForm::noise() {
    for (int i = 0; i < m_data_len; ++i) {
        m_data[0][i] = (double)i;
        m_data[1][i] = (double)(rand() % 100 - 50);
        m_data[2][i] = (double)(rand() % 100 - 50);
    }
    curve[0].setRawSamples(m_data[0], m_data[1], m_data_len);
    curve[1].setRawSamples(m_data[0], m_data[2], m_data_len);
    widget.qwtPlot->replot();
}

void PlotForm::setScaleEngineY(bool checked) {
    if (checked) widget.qwtPlot->setAxisScaleEngine(QwtPlot::yLeft, new QwtLogScaleEngine(10));
    else widget.qwtPlot->setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine());
    widget.qwtPlot->setAxisScale(QwtPlot::yLeft, curve[0].minYValue(), curve[0].maxYValue());
    widget.qwtPlot->setAxisScale(QwtPlot::yLeft, curve[0].minYValue(), curve[0].maxYValue());
    widget.qwtPlot->replot();
}

void PlotForm::setAutoScale(bool checked) {
    widget.qwtPlot->setAxisAutoScale(QwtPlot::yLeft, checked);
    widget.qwtPlot->setAxisScale(QwtPlot::xBottom, curve[0].minXValue(), curve[0].maxXValue());
    if (!checked) {
//        widget.sbMin->setValue(curve.minYValue());
//        widget.sbMax->setValue(curve.maxYValue());
        rescale(0);
    }
    widget.qwtPlot->replot();
}

void PlotForm::rescale(double value) {
    bool ok;
    widget.qwtPlot->setAxisScale(QwtPlot::yLeft, widget.leMin->text().toDouble(&ok), widget.leMax->text().toDouble(&ok));
}

void PlotForm::setAxisXType(int type) {
    x_axis_type = type;
    switch (x_axis_type) {
        case AxisXDefault:
        default:
            for (int i = 0; i < m_data_len; ++i)
                m_data[0][i] = i;
            mr_center.setVisible(false);
            mr_left.setVisible(false);
            mr_right.setVisible(false);
            break;
        case AxisXFrequency:
            for (int i = 0; i < m_data_len; ++i)
                m_data[0][i] = (double)i*1820.0/(double)m_data_len;
            mr_center.setVisible(true);
            mr_left.setVisible(true);
            mr_right.setVisible(true);
            break;
        case AxisXTime:
            for (int i = 0; i < m_data_len; ++i)
                m_data[0][i] = i;
            mr_center.setVisible(false);
            mr_left.setVisible(false);
            mr_right.setVisible(false);
            break;
    }
}

void PlotForm::save() {
    FILE *f;
    f = fopen("d:/tmp/plot.csv", "w");
    for (int i = 0; i < m_data_len; i++) {
        fprintf(f, "%lf\t%lf\n", m_data[1][i], m_data[2][i]);
    }
    fclose(f);
}


void PlotForm::zoomIn() {
    bool ok;
    double min = widget.leMin->text().toDouble(&ok) * 0.5;
    double max = widget.leMax->text().toDouble(&ok) * 0.5;
    widget.qwtPlot->setAxisAutoScale(QwtPlot::yLeft, false);
    widget.leMin->setText(QString::number(min));
    widget.leMax->setText(QString::number(max));
    rescale(0);
    widget.qwtPlot->replot();
}

void PlotForm::zoomOut() {
    bool ok;
    double min = widget.leMin->text().toDouble(&ok) * 2.0;
    double max = widget.leMax->text().toDouble(&ok) * 2.0;
    widget.qwtPlot->setAxisAutoScale(QwtPlot::yLeft, false);
    widget.leMin->setText(QString::number(min));
    widget.leMax->setText(QString::number(max));
    rescale(0);
    widget.qwtPlot->replot();
}
