import cv2
import serial

ArduinoSerial = serial.Serial('com4', 9600, timeout=0.1)
captureDevice = cv2.VideoCapture(0, cv2.CAP_DSHOW)  # captureDevice = camera

face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
buzzer = 0

while True:
    ret, frame = captureDevice.read()
    frame = cv2.flip(frame, 1)
    print(frame.shape)

    # Convert to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect the faces
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)

    # camera frame

    # cameraX = 240 + 45
    # cameraY = 320 - 110
    # cameraX = int(frame.shape[0] / 2 + 45)
    # cameraY = int(frame.shape[1] / 2 - 110)
    cameraMiddleX = int(frame.shape[0] * 0.59375)
    cameraMiddleY = int(frame.shape[1] * 0.328125)
    cv2.rectangle(frame, (cameraMiddleX, cameraMiddleY), (cameraMiddleX + 60, cameraMiddleY + 60), (255, 255, 255), 2)

    cv2.rectangle(frame, (10, 10), (210, 35), (255, 255, 255), -1)
    font = cv2.FONT_HERSHEY_DUPLEX
    fontsize = 0.7
    position = (10, 30)

    if buzzer == 1:
        color = (0, 0, 255)  # red
        text = "Buzzer mode: on"
    else:
        color = (0, 0, 0)  # black
        text = "Buzzer mode: off"

    cv2.putText(frame, text, position, font, fontsize, color=color)

    for (x, y, w, h) in faces:

        # sending data to Arduino
        string = 'x{0}y{1}t{2}f{3}'.format(int(x + w / 2), int(y + h // 2), buzzer, len(faces))
        print(string)
        ArduinoSerial.write(string.encode('utf-8'))

        # plot the center of the face
        cv2.circle(frame, (x + w // 2, y + h // 2), 2, (0, 255, 0), 2)

        # plot the point
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
    # Display
    cv2.imshow('my frame', frame)

    key = cv2.waitKey(33)
    if key == 27 or key == 113:  # Esc or q to stop
        break
    elif key == 98:  # switch buzzer mode
        if buzzer == 1:
            buzzer = 0
        else:
            buzzer = 1

ArduinoSerial.close()
captureDevice.release()
cv2.destroyAllWindows()
