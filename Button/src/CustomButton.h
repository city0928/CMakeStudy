#pragma once

#include <QObject>
#include <QGuiApplication>
#include <QScreen>
#include <QPushButton>
#include <QGraphicsEffect>
#include <QPainter>
#include <QPainterPath>
#include <QDir>
#include <QHBoxLayout>

#include "custombutton_global.h"


class CUSTOMBUTTON_EXPORT Shadow : public QGraphicsEffect
{
	Q_OBJECT;
public:
	qreal blurRadius = 40;
	int distance = 7;
	float strength = 1.0;
	qreal angle = 45;

	[[nodiscard]] QRectF boundingRectFor(const QRectF& rect) const override;

	void draw(QPainter* painter) override;

};


class CUSTOMBUTTON_EXPORT CustomButton : public QWidget
{
	Q_OBJECT;
public:
	QRect screen_rect;
	QPushButton* button1{ nullptr };
	QPushButton* button2{ nullptr };
    QHBoxLayout *m_Hlayer{nullptr};
	explicit CustomButton(int i, QWidget* parent = nullptr);
	~CustomButton();

	void buttonOperation();

	void customUi();
};