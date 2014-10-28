#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <qwt_plot_zoomer.h>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_text.h>
#include <qwt_math.h>

#include "qwtarrayplotitem.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = 0 );
	~MainWindow();



private:
	QPushButton* m_btnGenerate;
	QwtPlot* m_plot;
	QwtPlotZoomer* m_zoomer; 
	QwtPlotGrid* m_grid; 
	QwtArrayPlotItem* m_item;
	double* m_dataBuffer;

private slots:
	void btnGenerateClick();

};
