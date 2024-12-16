// src/TapButton.cpp
#include "../include/TapButton.h"
#include <QDebug>

/**
 * @brief Constructor for TapButton.
 * @param parent Parent widget.
 */
TapButton::TapButton(QWidget *parent) : QPushButton(parent) {}

/**
 * @brief Sets the image for the button.
 * @param imgSrc Path to the image.
 */
void TapButton::setImage(const QString &imgSrc) {
    currentImage.load(imgSrc);
    setIcon(QIcon(currentImage));
}

/**
 * @brief Sets the padding for the button.
 * @param newPadding Padding value.
 */
void TapButton::setPadding(int newPadding) {
    m_padding = newPadding;
}

/**
 * @brief Gets the current padding of the button.
 * @return Padding value.
 */
int TapButton::padding() const {
    return m_padding;
}

/**
 * @brief Handles the resize event.
 * @param event Resize event.
 */
void TapButton::resizeEvent(QResizeEvent *event) {
    QPushButton::resizeEvent(event);

    int newSize = qMin(height(), width()) - m_padding;
    setIconSize(QSize(newSize, newSize));
}