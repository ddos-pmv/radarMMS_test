#ifndef STATUSBLOCKGRAPHICS_H
#define STATUSBLOCKGRAPHICS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QResizeEvent>
#include <QColor>
#include <QString>

/**
 * @class StatusBlockGraphics
 * @brief Displays a status block with an image, header, status, and additional information.
 */
class StatusBlockGraphics : public QGraphicsView {
    Q_OBJECT

public:
    /**
     * @brief Constructor for StatusBlockGraphics.
     * @param header The header text.
     * @param powerIsOn Initial power state.
     * @param info Additional information text.
     * @param imgSrc Path to the image source.
     * @param parent Parent widget.
     */
    explicit StatusBlockGraphics(const QString &header, bool powerIsOn, const QString &info, const QString &imgSrc, QWidget *parent = nullptr);

    /**
     * @brief Updates the power status text.
     * @param isPowerOn New power state.
     */
    void updatePower(bool isPowerOn);

    /**
     * @brief Updates the additional information text.
     * @param info New information text.
     */
    void updateInfoText(const QString &info);

protected:
    /**
     * @brief Handles the resize event.
     * @param event Resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    QGraphicsScene *scene; ///< The graphics scene.
    QGraphicsRectItem *background; ///< Background rectangle item.
    QGraphicsPixmapItem *fanPixmapItem; ///< Fan image item.
    QGraphicsTextItem *cpuText; ///< CPU header text item.
    QGraphicsTextItem *statusText; ///< Status text item.
    QGraphicsTextItem *infoText; ///< Additional information text item.

    /**
     * @brief Resizes and repositions the elements.
     */
    void resizeElements();

    /**
     * @brief Creates a rectangle item.
     * @param color Fill color.
     * @return Pointer to the created rectangle item.
     */
    QGraphicsRectItem* createRectItem(const QColor &color);

    /**
     * @brief Creates a pixmap item.
     * @param imgSrc Path to the image source.
     * @return Pointer to the created pixmap item.
     */
    QGraphicsPixmapItem* createPixmapItem(const QString &imgSrc);

    /**
     * @brief Creates a text item.
     * @param color Text color.
     * @return Pointer to the created text item.
     */
    QGraphicsTextItem* createTextItem(const QColor &color);

    /**
     * @brief Updates the font and position of a text item.
     * @param textItem Pointer to the text item.
     * @param fontFactor Font size factor.
     * @param x X position.
     * @param y Y position.
     */
    void updateText(QGraphicsTextItem *textItem, qreal fontFactor, qreal x, qreal y);
};

#endif // STATUSBLOCKGRAPHICS_H