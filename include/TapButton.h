// include/TapButton.h
#ifndef TAPBUTTON_H
#define TAPBUTTON_H

#include <QWidget>
#include <QPushButton>

/**
 * @class TapButton
 * @brief A custom button that supports setting an image and padding.
 */
class TapButton : public QPushButton {
    Q_OBJECT

public:
    /**
     * @brief Constructor for TapButton.
     * @param parent Parent widget.
     */
    explicit TapButton(QWidget *parent = nullptr);

    /**
     * @brief Sets the image for the button.
     * @param imgSrc Path to the image.
     */
    void setImage(const QString &imgSrc);

    /**
     * @brief Sets the padding for the button.
     * @param padding Padding value.
     */
    void setPadding(int padding);

    /**
     * @brief Gets the current padding of the button.
     * @return Padding value.
     */
    int padding() const;

protected:
    /**
     * @brief Handles the resize event.
     * @param event Resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    QPixmap currentImage; ///< Current image for the button.
    QSize fixedIconSize = QSize(30, 30); ///< Fixed size for the icon.
    int m_padding = 60; ///< Padding for the button.
};

#endif // TAPBUTTON_H