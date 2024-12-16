//
// Created by Сергей Перлин on 10.12.2024.
//

#ifndef ANIMATEDELLIPSE_H
#define ANIMATEDELLIPSE_H

#include <QPropertyAnimation>
#include <QGraphicsEllipseItem>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>

// Прокси-объект для анимации графических элементов
class AnimatedEllipse : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_PROPERTY(QRectF rect READ rect WRITE setRect)
public:
    AnimatedEllipse(qreal x, qreal y, qreal width, qreal height)
        : QGraphicsEllipseItem(x, y, width, height) {}

    QRectF rect() const { return QGraphicsEllipseItem::rect(); }
    void setRect(const QRectF &newRect) { QGraphicsEllipseItem::setRect(newRect); }
};


#endif //ANIMATEDELLIPSE_H
