#include   "ViewerWidget.h"
#include <QtMath>

ViewerWidget::ViewerWidget(QString viewerName, QSize imgSize, QWidget* parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
	setMouseTracking(true);
	name = viewerName;
	if (imgSize != QSize(0, 0)) {
		img = new QImage(imgSize, QImage::Format_ARGB32);
		img->fill(Qt::white);
		resizeWidget(img->size());
		setPainter();
	}
}
ViewerWidget::~ViewerWidget()
{
	delete painter;
	delete img;
}
void ViewerWidget::resizeWidget(QSize size)
{
	this->resize(size);
	this->setMinimumSize(size);
	this->setMaximumSize(size);
}

//Image functions
bool ViewerWidget::setImage(const QImage& inputImg)
{
	if (img != nullptr) {
		delete img;
	}
	img = new QImage(inputImg);
	if (!img) {
		return false;
	}
	resizeWidget(img->size());
	setPainter();
	update();

	return true;
}
bool ViewerWidget::isEmpty()
{
	if (img->size() == QSize(0, 0)) {
		return true;
	}
	return false;
}

//Draw functions
void ViewerWidget::freeDraw(QPoint end, QPen pen)
{
	painter->setPen(pen);
	painter->drawLine(freeDrawBegin, end);

	update();
}

void ViewerWidget::clear()
{
	img->fill(Qt::white);
	update();
}

//Slots
void ViewerWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QRect area = event->rect();
	painter.drawImage(area, *img, area);
}

//dorobene

void ViewerWidget::nakresliOsi(int a) {
	QPen pen;
	painter->setPen(pen);
	int w = img->width();
	int h = img->height();
	QPoint xs(5,h/2), xk(w-5,h/2), ys(w/2,5), yk(w/2, h - 5);
	painter->drawLine(xs, xk);
	painter->drawLine(ys, yk);
	
	double dielikx = (w - 10.)/ a;
	double dieliky = (h - 10.) / a;
	int i;

	
	for (i = 0; i < a+1; i++) {
		//qDebug() << i * dielikx + 5;
		painter->drawLine(i * dielikx + 5, h / 2 + 5, i * dielikx + 5, h / 2 - 5);
		painter->drawLine(w / 2 - 5, i * dieliky + 5, w / 2 + 5, i * dieliky + 5);
	}

	/*for (i = 0; i < a/2; i++) {
		x1 += dielik;
		x2 += -dielik;
		y1 += dieliky;
		y2 += -dieliky;
		painter->drawLine(x1, h / 2 + 5, x1, h / 2 - 5);
		painter->drawLine(x2, h / 2 + 5, x2, h / 2 - 5);
		painter->drawLine(w / 2 - 5, y1, w / 2 + 5, y1);
		painter->drawLine(w / 2 - 5, y2, w / 2 + 5, y2);
	};*/
}

void ViewerWidget::nakresliCosinus(int N, int dieliky, int typ) {
	clear();
	nakresliOsi(dieliky);

	QPen pen;
	pen.setWidth(2);
	pen.setColor("red");
	painter->setPen(pen);

	double a = (N* M_PI)/(dieliky/2);
	int i;
	double dielik = (img->width() - 10.) / dieliky, x1 = img->width() / 2., x2 = img->width() / 2.;

	if (typ == 0) {
		double a = (N * M_PI) / (dieliky / 2.);
		pen.setWidth(5);
		painter->setPen(pen);
		if (dieliky % 2 == 0) {
			for (i = 0; i < dieliky / 2 + 1; i++) {
				painter->drawPoint(x1, -(img->height() - 5) / 2 * qCos(i * a) + img->height() / 2);
				painter->drawPoint(x2, -(img->height() - 5) / 2 * qCos(-i * a) + img->height() / 2);
				x1 += dielik;
				x2 += -dielik;
			}
		}
		if (dieliky % 2 == 1) {
			double a = (N * M_PI) / ((dieliky) / 2.);
			x1 += dielik / 2.;
			x2 += -dielik / 2.;
			for (i = 0; i < dieliky / 2 + 1; i++) {
				painter->drawPoint(x1, -(img->height() - 5) / 2 * qCos(i * a + a / 2.) + img->height() / 2);
				painter->drawPoint(x2, -(img->height() - 5) / 2 * qCos(-i * a - a / 2.) + img->height() / 2);
				x1 += dielik;
				x2 += -dielik;
			}
		}
	}
	if (typ == 1) {
		QPoint A, B, C, D;
		if (dieliky % 2 == 0) {
			for (i = 0; i < dieliky / 2 + 1; i++) {
				if (i == 0) {
					A.setX(x1);
					A.setY(-(img->height() - 5) / 2 * qCos(i * a) + img->height() / 2);
					B.setX(x2);
					B.setY(-(img->height() - 5) / 2 * qCos(-i * a) + img->height() / 2);
					x1 += dielik;
					x2 += -dielik;
				}
				else {
					C.setX(A.x());
					C.setY(A.y());
					D.setX(B.x());
					D.setY(B.y());
					A.setX(x1);
					A.setY(-(img->height() - 5) / 2 * qCos(i * a) + img->height() / 2);
					B.setX(x2);
					B.setY(-(img->height() - 5) / 2 * qCos(-i * a) + img->height() / 2);
					painter->drawLine(A, C);
					painter->drawLine(B, D);
					x1 += dielik;
					x2 += -dielik;
				}
			}
		}
		if (dieliky % 2 == 1) {
			double a = (N * M_PI) / ((dieliky) / 2.);
			x1 += dielik / 2.;
			x2 += -dielik / 2.;
			for (i = 0; i < dieliky / 2 + 1; i++) {
				if (i == 0) {
					A.setX(x1);
					A.setY(-(img->height() - 5) / 2 * qCos(i * a + a / 2.) + img->height() / 2);
					B.setX(x2);
					B.setY(-(img->height() - 5) / 2 * qCos(-i * a - a / 2.) + img->height() / 2);
					painter->drawLine(A, B);
					x1 += dielik;
					x2 += -dielik;
				}
				else {
					C.setX(A.x());
					C.setY(A.y());
					D.setX(B.x());
					D.setY(B.y());
					A.setX(x1);
					A.setY(-(img->height() - 5) / 2 * qCos(i * a + a / 2.) + img->height() / 2);
					B.setX(x2);
					B.setY(-(img->height() - 5) / 2 * qCos(-i * a - a / 2.) + img->height() / 2);
					painter->drawLine(A, C);
					painter->drawLine(B, D);
					x1 += dielik;
					x2 += -dielik;
				}
			}
		}
	}
	if( typ==2 ) {
		x1 = img->width() / 2 - dielik / 2;
		x2 = img->width() / 2 - dielik / 2;
		for (i = 0; i < dieliky / 2 + 1; i++) {
			painter->fillRect(x1, img->height() / 2, dielik, -(img->height() - 5) / 2 * qCos(i * a), Qt::red);
			painter->fillRect(x2, img->height() / 2, dielik, -(img->height() - 5) / 2 * qCos(-i * a), Qt::red);
			painter->drawRect(x1, img->height() / 2, dielik, -(img->height() - 5) / 2 * qCos(i * a));
			painter->drawRect(x2, img->height() / 2, dielik, -(img->height() - 5) / 2 * qCos(-i * a));
			x1 += dielik;
			x2 += -dielik;
		}
	}
	update();
}

void ViewerWidget::nakresliSinus(int N, int dieliky, int typ) {
	clear();
	nakresliOsi(dieliky);

	QPen pen;
	pen.setWidth(2);
	pen.setColor("red");
	painter->setPen(pen);

	double a = (N * M_PI) / (dieliky / 2.);
	int i;
	double dielik = (img->width() - 10.) / dieliky, x1 = img->width() / 2., x2 = img->width() / 2.;


	if (typ == 0) {
		double a = (N * M_PI) / (dieliky / 2.);
		pen.setWidth(5);
		painter->setPen(pen);
		if (dieliky % 2 == 0) {
			for (i = 0; i < dieliky / 2 + 1; i++) {
				painter->drawPoint(x1, -(img->height() - 5) / 2 * qSin(i * a) + img->height() / 2);
				painter->drawPoint(x2, -(img->height() - 5) / 2 * qSin(-i * a) + img->height() / 2);
				x1 += dielik;
				x2 += -dielik;
			}
		}
		if (dieliky % 2 == 1) {
			double a = (N * M_PI ) / (( dieliky  )/ 2.);
			x1 += dielik / 2.;
			x2 += -dielik / 2.;
			for (i = 0; i < dieliky / 2 + 1; i++) {
				painter->drawPoint(x1, -(img->height() - 5) / 2 * qSin(i * a + a/2. ) + img->height() / 2);
				painter->drawPoint(x2, -(img->height() - 5) / 2 * qSin(-i * a - a / 2.) + img->height() / 2);
				x1 += dielik;
				x2 += -dielik;
			}
		}
	}
	if (typ == 1) {
		QPoint A, B, C, D;
		if (dieliky % 2 == 0) {
			for (i = 0; i < dieliky / 2 + 1; i++) {
				if (i == 0) {
					A.setX(x1);
					A.setY(-(img->height() - 5) / 2 * qSin(i * a) + img->height() / 2);
					B.setX(x2);
					B.setY(-(img->height() - 5) / 2 * qSin(-i * a) + img->height() / 2);
					x1 += dielik;
					x2 += -dielik;
				}
				else {
					C.setX(A.x());
					C.setY(A.y());
					D.setX(B.x());
					D.setY(B.y());
					A.setX(x1);
					A.setY(-(img->height() - 5) / 2 * qSin(i * a) + img->height() / 2);
					B.setX(x2);
					B.setY(-(img->height() - 5) / 2 * qSin(-i * a) + img->height() / 2);
					painter->drawLine(A, C);
					painter->drawLine(B, D);
					x1 += dielik;
					x2 += -dielik;
				}
			}
		}
		if (dieliky % 2 == 1) {
			double a = (N * M_PI) / ((dieliky) / 2.);
			x1 += dielik / 2.;
			x2 += -dielik / 2.;
			for (i = 0; i < dieliky / 2 + 1; i++) {
				if (i == 0) {
					A.setX(x1);
					A.setY(-(img->height() - 5) / 2 * qSin(i * a + a / 2.) + img->height() / 2);
					B.setX(x2);
					B.setY(-(img->height() - 5) / 2 * qSin(-i * a - a / 2.) + img->height() / 2);
					painter->drawLine(A, B);
					x1 += dielik;
					x2 += -dielik;
				}
				else {
					C.setX(A.x());
					C.setY(A.y());
					D.setX(B.x());
					D.setY(B.y());
					A.setX(x1);
					A.setY(-(img->height() - 5) / 2 * qSin(i * a + a / 2.) + img->height() / 2);
					B.setX(x2);
					B.setY(-(img->height() - 5) / 2 * qSin(-i * a - a / 2.) + img->height() / 2);
					painter->drawLine(A, C);
					painter->drawLine(B, D);
					x1 += dielik;
					x2 += -dielik;
				}
			}
		}
	}
	if( typ==2 ) {
		x1 = img->width() / 2 - dielik / 2;
		x2 = img->width() / 2 - dielik / 2;
		for (i = 0; i < dieliky / 2 + 1; i++) {
			painter->fillRect(x1, img->height() / 2, dielik, -(img->height() - 5) / 2 * qSin(i * a), Qt:: red);
			painter->fillRect(x2, img->height() / 2, dielik, -(img->height() - 5) / 2 * qSin(-i * a), Qt:: red);
			painter->drawRect(x1, img->height() / 2, dielik, -(img->height() - 5) / 2 * qSin(i * a));
			painter->drawRect(x2, img->height() / 2, dielik, -(img->height() - 5) / 2 * qSin(-i * a));
			x1 += dielik;
			x2 += -dielik;
		}
	}
	update();
}