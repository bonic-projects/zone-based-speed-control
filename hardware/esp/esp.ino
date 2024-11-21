#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "Autobonics_4G"
#define WIFI_PASSWORD "autobonics@27"
#define API_KEY "AIzaSyC4uQFOCeyl83Q-zehh5CNX7nDsH91su_c"
#define DATABASE_URL "https://zone-based-speed-control-default-rtdb.firebaseio.com/"
#define USER_EMAIL "device@gmail.com"
#define USER_PASSWORD "12345678"

// Firebase and motor control objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseData stream;

String uid;
int spd = 100;  // Default speed
int mappedSpeed = 0 ;

// Motor control pins
int en1 = 27;
int in1 = 26;  // Motor 1
int in2 = 25;  // Motor 1
int in3 = 33;  // Motor 2
int in4 = 32;  // Motor 2
int en2 = 13;

void setupPWM() {
  // Initialize PWM for motor speed control
  ledcAttach(en1, 12000, 8); 
  ledcAttach(en2, 12000, 8); 
}

// void updateMotorSpeed() {
//   ledcWrite(0, spd);  // Motor 1 speed
//   ledcWrite(1, spd);  // Motor 2 speed
// }
void updateMotorSpeed() {
  mappedSpeed = map(spd, 0, 100, 0, 255);  // Map speed to range 0-255
  ledcWrite(en1, mappedSpeed);  // Motor 1 speed
  ledcWrite(en2, mappedSpeed);  // Motor 2 speed
  Serial.println(mappedSpeed);
}

// void streamCallback(StreamData data) {
//   Serial.println("NEW DATA!");
//   String p = data.dataPath();
//   Serial.println(p);
//   printResult(data);


//   FirebaseJson jVal = data.jsonObject();
//   // FirebaseJsonData direction, speed;
//   FirebaseJsonData direction;
//   FirebaseJsonData speed;
//   jVal.get(direction, "direction");
//   jVal.get(speed, "speed");

  

//   // if (direction.success) {
//   //   Serial.println("Succes data direction");
//   //   String value = direction.to<String>();

//   //   if (value == "F") forward();
//   //   if (value == "B") backward();
//   //   if (value == "L") left();
//   //   if (value == "R") right();
//   //   if (value == "S") stop();
//   // }
//   if (direction.success) {
//     Serial.println("Success data direciton");
//     String value = direction.to<String>();
//     Serial.print(value);
//     if (value == "F") {
//     forward();
//     }
//     if (value == "B") {
//       backward();
//     }
//     if (value == "R") {
//       right();
//     }
//     if (value == "L") {
//       left();
//     }
//     if (value == "S") {
//       stop();
//     }
//   }
//   if (speed.success) {
//     spd = speed.to<int>();
//     updateMotorSpeed();
//   }
// }

// void streamCallback(StreamData data) {
//   Serial.println("NEW DATA!");

//   String p = data.dataPath();
//   Serial.println(p);

//   // Extracting data directly based on the current path
//   if (p == "/direction") {
//     String value = data.stringData();
//     value.trim();
//     value.toUpperCase();
//     Serial.println("Direction Value: " + value);

//     if (value == "F") {
//       Serial.println("Triggering Forward Function");
//       forward();
//     } else if (value == "B") {
//       Serial.println("Triggering Backward Function");
//       backward();
//     } else if (value == "R") {
//       Serial.println("Triggering Right Function");
//       right();
//     } else if (value == "L") {
//       Serial.println("Triggering Left Function");
//       left();
//     } else if (value == "S") {
//       Serial.println("Triggering Stop Function");
//       stop();
//     }
//   } else if (p == "speed") {
//     int speedValue = data.intData();
//     spd = speedValue;
//     updateMotorSpeed();
//   }
// }

void streamCallback(StreamData data) {
  Serial.println("NEW DATA!");
  String p = data.dataPath();
  Serial.println("Data Path: " + p);
  FirebaseJson jVal = data.jsonObject();
  FirebaseJsonData speed;
  jVal.get(speed, "speed");

  // Handling the direction updates
  if (p == "/direction") {
    String value = data.stringData();
    value.trim();
    value.toUpperCase();
    Serial.println("Direction Value: " + value);

    if (value == "F") {
      Serial.println("Triggering Forward Function");
      forward();
    } else if (value == "B") {
      Serial.println("Triggering Backward Function");
      backward();
    } else if (value == "R") {
      Serial.println("Triggering Right Function");
      right();
    } else if (value == "L") {
      Serial.println("Triggering Left Function");
      left();
    } else if (value == "S") {
      Serial.println("Triggering Stop Function");
      stop();
    }
  } 

  if (speed.success) {
    spd = speed.to<int>();
     updateMotorSpeed();
   }

  // Handling the speed updates
  // else if (p.endsWith("/speed")) {
  //   // Extract speed value and ensure it’s updated properly
  //   if (data.dataTypeEnum() == fb_esp_rtdb_data_type_integer || data.dataTypeEnum() == fb_esp_rtdb_data_type_float) {
  //     spd = data.intData();  // or use data.floatData() if speed is float
  //     Serial.printf("Speed received from Firebase: %d\n", spd);
  //     updateMotorSpeed();  // Call the original function to update the speed
  //   } else {
  //     Serial.println("Invalid data type for speed. Expected integer or float.");
  //   }
  // }
}


void streamTimeoutCallback(bool timeout) {
  if (timeout) Serial.println("Stream timed out, resuming...");
  if (!stream.httpConnected())
    Serial.printf("Error code: %d, reason: %s\n", stream.httpCode(), stream.errorReason().c_str());
}

void backward() {
  Serial.println("Moving forward");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  updateMotorSpeed();
}

void forward() {
  Serial.println("Moving Backward");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  updateMotorSpeed();
}

void left() {
  Serial.println("Moving left");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  updateMotorSpeed();
}

void right() {
  Serial.println("Moving right");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  updateMotorSpeed();
}

void stop() {
  Serial.println(" stopped");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void setup() {
  Serial.begin(115200);

  // Initialize motor control pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  setupPWM();  // Initialize PWM for motor control

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Firebase setup
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;

  // Assign the user sign-in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  // Assign the callback function for the long running token generation task
  config.token_status_callback = tokenStatusCallback;

  // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  // Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);

  // Stream setup
  if (!Firebase.beginStream(stream, "devices/" + uid + "/data"))
    Serial.printf("stream begin error, %s\n\n", stream.errorReason().c_str());

  Firebase.setStreamCallback(stream, streamCallback, streamTimeoutCallback);
}

void loop() {
  // Motor control logic is handled in stream callback
}
