#include "mainwindow.h"
#include <QDateTime>
#include <qwt_scale_engine.h>



MainWindow::MainWindow( QWidget *parent ):
    QMainWindow( parent ),
	m_dataBuffer(0)
{
	QWidget* cWidget = new QWidget(this);
	QGridLayout* layout = new QGridLayout(cWidget);
	this->setCentralWidget(cWidget);
	
	//plot
	m_plot = new QwtPlot(this);
	m_plot->setAxisAutoScale(QwtPlot::xBottom,true);
	m_plot->setAxisAutoScale(QwtPlot::yLeft,true);
	m_plot->axisScaleEngine(QwtPlot::xBottom)->setAttribute(QwtScaleEngine::Floating,true);
	m_plot->setToolTip ("Right: zoom in\nCtrl+Right: zoom out\nShift+Right: back to 0 zoom");

	//plot zoomer
	m_zoomer = new QwtPlotZoomer(m_plot->canvas());
	m_zoomer->setTrackerMode(QwtPicker::AlwaysOff);
	m_zoomer->setMousePattern(QwtEventPattern::MouseSelect1, Qt::RightButton); //select (zoom in)
	m_zoomer->setMousePattern(QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ShiftModifier); //go to zoom level 0
	m_zoomer->setMousePattern(QwtEventPattern::MouseSelect3, Qt::RightButton, Qt::ControlModifier); //one step back

	m_grid = new QwtPlotGrid();
	m_grid->setAxes(QwtPlot::xBottom,QwtPlot::yLeft);
	m_grid->setPen(QPen(Qt::gray,1.0, Qt::DashLine));
	m_grid->attach(m_plot);		
	
	
	//our plot item
	m_item = new QwtArrayPlotItem(QwtText("My item"));

	m_item->attach(m_plot);


	m_btnGenerate = new QPushButton(tr("Generate data"));
	connect(m_btnGenerate,SIGNAL(pressed()),this, SLOT(btnGenerateClick()));
	layout->addWidget(m_plot,0,0,1,2);
	layout->addWidget(m_btnGenerate,1,0);
	layout->setColumnStretch(1,1);
}

MainWindow::~MainWindow()
{
	if(m_dataBuffer)
	{
		delete m_dataBuffer;
		m_dataBuffer = 0;
	}
}

void MainWindow::btnGenerateClick()
{
	qsrand(QDateTime::currentMSecsSinceEpoch());
	//hide item to avoid redraw when data is in process of change
	m_item->hide();
	//data buffer size - 4M points
	const int size = 4*1024*1024;
	if(!m_dataBuffer)
	{
		m_dataBuffer = new double[size];
	}

	for(int i=0; i<size; ++i)
	{
		m_dataBuffer[i] = qrand();
	}

	m_item->setData(m_dataBuffer, size);
	m_item->show();

	m_zoomer->setZoomBase(m_item->boundingRect());
	m_zoomer->zoom(0);

	m_plot->replot();
	
}

