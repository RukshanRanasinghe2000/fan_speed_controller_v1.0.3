import cv2
import cvzone
from cvzone.HandTrackingModule import HandDetector
import serial

# Initialize Serial Communication
ser = serial.Serial('COM3', 9600)

# Initialize Video Capture
cap = cv2.VideoCapture(0)
cap.set(3, 1280)
cap.set(4, 720)

# Initialize Hand Detector
detector = HandDetector(detectionCon=0.7)

# Initialize Finger Count
total_fingers = 0
previous_fingers = -1

try:
    while True:
        success, img = cap.read()
        if not success:
            break

        # Detect Hands
        hands, img = detector.findHands(img)
        if hands:
            # Process only the first detected hand (left or right)
            hand = hands[0]
            list_finger = detector.fingersUp(hand)
            total_fingers = sum(list_finger)

            # Check if the total fingers have changed
            if total_fingers != previous_fingers:
                ser.write(str(total_fingers).encode())
                previous_fingers = total_fingers

            # Display appropriate message based on total fingers
            if total_fingers == 1:
                cv2.putText(img, "Fan - ON", (50, 100), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 0), 3)
            elif total_fingers == 2:
                cv2.putText(img, "Fan - Speed 2", (50, 100), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 0), 3)
            elif total_fingers == 3:
                cv2.putText(img, "Fan - Speed 3", (50, 100), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 0), 3)
            elif total_fingers == 4:
                cv2.putText(img, "Fan - Rotation ON", (50, 100), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 0), 3)
            elif total_fingers == 5:
                cv2.putText(img, "Fan - Rotation OFF", (50, 100), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 0), 3)
            elif total_fingers == 0:
                cv2.putText(img, "Fan - OFF", (50, 100), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 0), 3)

        # Display the image
        cv2.imshow("Capture Objects", img)
        key = cv2.waitKey(1)
        if key == 27:  # ESC key to break
            break

finally:
    # Cleanup
    cap.release()
    cv2.destroyAllWindows()
