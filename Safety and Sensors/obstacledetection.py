import cv2
import numpy as np

# Load the captured image
image = cv2.imread('arena_layout.jpg')

# Convert to grayscale
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Apply GaussianBlur to reduce noise and improve edge detection
blurred = cv2.GaussianBlur(gray, (5, 5), 0)

# Perform edge detection
edges = cv2.Canny(blurred, 50, 150)

# Find contours
contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Draw contours on the image
for contour in contours:
    cv2.drawContours(image, [contour], -1, (0, 255, 0), 2)

# Save the processed image with detected obstacles
cv2.imwrite('arena_with_obstacles.jpg', image)
