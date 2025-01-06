import cv2

# Initialize camera
camera = cv2.VideoCapture(0)  # 0 for the first camera connected

# Capture image
ret, frame = camera.read()

# Save the image
cv2.imwrite('arena_layout.jpg', frame)

# Release the camera
camera.release()
cv2.destroyAllWindows()
