#include <WiFi.h>
#include <WebServer.h>

// -------- WIFI AP -------- 
const char* ssid = "Murugesh_Car";
const char* password = "12344321";

WebServer server(80);

// -------- Motor Pins --------
#define ENA 4
#define IN1 1
#define IN2 2

#define ENB 5
#define IN3 9
#define IN4 10

unsigned long lastCommandTime = 0;

// -------- MOTOR CONTROL --------
void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void setMotor(int leftSpeed, int rightSpeed) {

  if (leftSpeed == 0 && rightSpeed == 0) {
    stopMotor();
    return;
  }

  // LEFT MOTOR
  if (leftSpeed > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    leftSpeed = -leftSpeed;
  }

  // RIGHT MOTOR
  if (rightSpeed > 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } else {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    rightSpeed = -rightSpeed;
  }

  analogWrite(ENA, constrain(leftSpeed, 0, 255));
  analogWrite(ENB, constrain(rightSpeed, 0, 255));
}

// -------- WEB PAGE --------
String webpage = R"====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body { background:#111; color:white; text-align:center; }

.joystick {
  width:160px; height:160px;
  background:#333; border-radius:50%;
  position:relative; margin:20px;
}

.stick {
  width:50px; height:50px;
  background:red; border-radius:50%;
  position:absolute;
  left:55px; top:55px;
}

.container {
  display:flex;
  justify-content:space-around;
}
</style>
</head>

<body>
<h2>Murugesh Car Controller</h2>

<div class="container">
  <div>
    <p>Forward / Back</p>
    <div class="joystick" id="joyY">
      <div class="stick" id="stickY"></div>
    </div>
  </div>

  <div>
    <p>Left / Right</p>
    <div class="joystick" id="joyX">
      <div class="stick" id="stickX"></div>
    </div>
  </div>
</div>

<script>

let yVal = 0;
let xVal = 0;

function clamp(x, y) {
  let d = Math.sqrt(x*x + y*y);
  if (d > 50) {
    x = x * 50 / d;
    y = y * 50 / d;
  }
  return {x, y};
}

function send(l, r) {
  fetch(`/move?l=${l}&r=${r}`).catch(()=>{});
}

function STOP() {
  fetch("/stop").catch(()=>{});
}

function setup(joyId, stickId, isY) {

  const joy = document.getElementById(joyId);
  const stick = document.getElementById(stickId);

  function move(e) {
    let rect = joy.getBoundingClientRect();
    let t = e.touches ? e.touches[0] : e;

    let x = t.clientX - rect.left - 80;
    let y = t.clientY - rect.top - 80;

    let p = clamp(x, y);

    stick.style.left = (p.x + 55) + "px";
    stick.style.top  = (p.y + 55) + "px";

    if (isY) yVal = -p.y;
    else xVal = p.x;

    let L = yVal + xVal;
    let R = yVal - xVal;

    L = Math.max(-100, Math.min(100, L));
    R = Math.max(-100, Math.min(100, R));

    send(L, R);
  }

  function release() {
    stick.style.left = "55px";
    stick.style.top = "55px";

    yVal = 0;
    xVal = 0;

    STOP();
  }

  joy.addEventListener("touchmove", move);
  joy.addEventListener("touchend", release);
  joy.addEventListener("touchcancel", release);

  joy.addEventListener("mousemove", move);
  joy.addEventListener("mouseup", release);
  joy.addEventListener("mouseleave", release);
}

setup("joyY","stickY",true);
setup("joyX","stickX",false);

</script>
</body>
</html>
)====";

// -------- HTTP --------
void handleRoot() {
  server.send(200, "text/html", webpage);
}

void handleMove() {
  lastCommandTime = millis();

  int l = server.arg("l").toInt();
  int r = server.arg("r").toInt();

  int pwmL = map(l, -100, 100, -255, 255);
  int pwmR = map(r, -100, 100, -255, 255);

  setMotor(pwmL, pwmR);

  server.send(200, "text/plain", "OK");
}

void handleStop() {
  stopMotor();
  server.send(200, "text/plain", "STOP");
}

// -------- SETUP --------
void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Start AP
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();

  Serial.println("\n==============================");
  Serial.println("Murugesh Car WiFi Started");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  Serial.print("Open URL: http://");
  Serial.println(IP);
  Serial.println("==============================");

  server.on("/", handleRoot);
  server.on("/move", handleMove);
  server.on("/stop", handleStop);

  server.begin();
}

// -------- LOOP --------
void loop() {
  server.handleClient();

  // FAILSAFE STOP
  if (millis() - lastCommandTime > 100) {
    stopMotor();
  }
}