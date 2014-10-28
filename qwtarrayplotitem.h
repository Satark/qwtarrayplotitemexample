#ifndef _QWTARRAYPLOTITEM_H_
#define _QWTARRAYPLOTITEM_H_

#include <qglobal.h>


#include "qwt_plot_item.h"
#include "qwt_scale_map.h"


class QwtArrayPlotItem : public QwtPlotItem
{

public:
	QwtArrayPlotItem(const QwtText &title = QwtText());
	~QwtArrayPlotItem();

	virtual int rtti() const
    {
        return QwtPlotItem::Rtti_PlotUserItem+1;
    }
 
    void draw( QPainter *painter,
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        const QRectF &canvasRect ) const;
	QRectF boundingRect() const;

	void setData(double* data, quint32 size, qreal dt = 1.0);
	void setColor(QColor &color){m_plotColor = color;}
	QColor color(){return m_plotColor;}
  

private:	
	double* m_data;
	double m_dt;
	quint32 m_size;

	QColor m_plotColor;
	mutable QRectF m_boundingRect;

};

#endif // _QWTARRAYPLOTITEM_H_
