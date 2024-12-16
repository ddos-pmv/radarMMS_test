// src/CustomButton.cpp
#include "../include/CustomButton.h"

/**
 * @brief Constructor for CustomButton.
 * @param parent Parent widget.
 */
CustomButton::CustomButton(QWidget *parent) : QPushButton(parent), isSelected(false) {
    setProperty("selected", "false");
    connect(this, &QPushButton::clicked, this, &CustomButton::changeColor);
}

/**
 * @brief Sets the images for the unselected and selected states.
 * @param unselectedImgSrc Path to the image for the unselected state.
 * @param selectedImgSrc Path to the image for the selected state.
 */
void CustomButton::setImage(const QString &unselectedImgSrc, const QString &selectedImgSrc) {
    unselectedImage.load(unselectedImgSrc);
    selectedImage.load(selectedImgSrc);

    if (unselectedImage.isNull()) qDebug() << "Failed to load unselected img";
    if (selectedImage.isNull()) qDebug() << "Failed to load selected img";

    updateButtonContent();
}

/**
 * @brief Handles the resize event.
 * @param event Resize event.
 */
void CustomButton::resizeEvent(QResizeEvent *event) {
    QPushButton::resizeEvent(event);

    int newSize = qMin(height(), width()) - padding;
    setIconSize(QSize(newSize, newSize));
}

/**
 * @brief Slot to change the color and image of the button when clicked.
 */
void CustomButton::changeColor() {
    isSelected = !isSelected;

    updateButtonContent();

    setProperty("selected", isSelected ? "true" : "false");

    style()->unpolish(this);
    style()->polish(this);
}

/**
 * @brief Updates the button content based on the selected state.
 */
void CustomButton::updateButtonContent() {
    if (isSelected && !selectedImage.isNull()) {
        setIcon(selectedImage);
    } else if (!isSelected && !unselectedImage.isNull()) {
        setIcon(unselectedImage);
    }
}