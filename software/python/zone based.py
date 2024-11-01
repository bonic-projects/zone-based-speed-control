import time
import bonic_cloud
import cv2
from ultralytics import YOLO

# Initialize Bonic Cloud and get data reference
bonic_cloud.init()
data_ref = bonic_cloud.get_data_ref()
stream = "http://192.168.29.19/stream"

# Load the YOLO model
model = YOLO("zonebased.pt")

# Dictionary mapping speed limit strings to integer values
speed_limits = {
    "Speed_limit_30km": 30,
    "Speed_limit_40km": 40,
    "Speed_limit_50km": 50,
    "Speed_limit_60km": 60,
    "Speed_limit_70km": 70,
    "Speed_limit_80km": 80,
    "Speed_limit_90km": 90,
    "Speed_limit_100km": 100,
    "Speed_limit_110km": 110,
    "Speed_limit_120km": 120
}

# Open the camera stream
cap = cv2.VideoCapture(stream)
if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    # Resize the frame for better performance (optional)
    resized_frame = cv2.resize(frame, (640, 480))

    # Use YOLO to make predictions
    results = model.predict(resized_frame)

    # Iterate through the predictions
    for result in results:
        boxes = result.boxes  # Box information
        for box in boxes:
            # Extract coordinates
            x1, y1, x2, y2 = map(int, box.xyxy[0])  # (xmin, ymin, xmax, ymax)
            conf = box.conf[0]  # Confidence
            label = model.names[int(box.cls[0])]  # Class label

            if conf > 0.5:  # Confidence threshold
                # Draw bounding box and label on the frame
                cv2.rectangle(frame, (x1, y1), (x2, y2), (255, 0, 0), 2)
                cv2.putText(frame, f'{label} {conf:.2f}', (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (255, 0, 0), 2)

                # Convert label to speed limit value and update Bonic Cloud
                speed_limit_value = speed_limits.get(label, None)
                if speed_limit_value is not None:
                    data_ref.update({'speed': speed_limit_value})
                    print(f"Updated Bonic Cloud with speed: {speed_limit_value}")

    # Show the frame with detections
    cv2.imshow('YOLO Webcam Detection', frame)

    # Break the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the webcam and close the window
cap.release()
cv2.destroyAllWindows()
