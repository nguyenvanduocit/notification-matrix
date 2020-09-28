#include <config.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <PubSubClient.h>
#include <animation.pb.h>
#include <pb_decode.h>

/* #region  Animation Config */
#include <WS2812FX.h>
#include <TwinkleFox.h>
#include <profitSky.h>

#define LED_COUNT 192
#define LED_PIN D7

#define DEFAULT_ANIMATION_DURATION 5000

unsigned long last_change = 0;
unsigned long now = 0;
unsigned long animationDuration = 5000;

IdleAnimationArg idleAnimationArg = {FX_MODE_CUSTOM_1, GREEN, 2000, 1};
boolean isIdle = false;
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

void saveIdleAnimation(IdleAnimationArg message){
  EEPROM.put(0, idleAnimationArg);
  EEPROM.commit();
}

void loadIdleAnimation(IdleAnimationArg &message){
  EEPROM.get(0, message);
}

void resetIdleAnimation()
{
  isIdle = true;
  animationDuration = DEFAULT_ANIMATION_DURATION;
  ws2812fx.setSpeed(idleAnimationArg.speed);
  ws2812fx.setColor(idleAnimationArg.color_id);
  ws2812fx.setBrightness(idleAnimationArg.brightness);
  ws2812fx.setMode(idleAnimationArg.animation_id);
}

/* #endregion */

/* #region  Rotary Config */
#include <ESPRotary.h>

#define LEFT_ROTARY_PIN1 D1 // => DT
#define LEFT_ROTARY_PIN2 D2

#define RIGHT_ROTARY_PIN1 D5 // => DT
#define RIGHT_ROTARY_PIN2 D6

#define CLICKS_PER_STEP 4

#define ROTARY_MODE_CHANGE_BRIGHTNESS 1
#define ROTARY_MODE_CHANGE_SPEED 2
#define ROTARY_MODE_CHANGE_ANIMATION 3
#define ROTARY_MODE_CHANGE_COLOR 4

#define ROTARY_SPEED_MULTIPLE 100

uint leftRotaryMode = ROTARY_MODE_CHANGE_COLOR;
uint rightRotaryMode = ROTARY_MODE_CHANGE_ANIMATION;

ESPRotary leftRotary = ESPRotary(LEFT_ROTARY_PIN1, LEFT_ROTARY_PIN2, CLICKS_PER_STEP);
ESPRotary rightRotary = ESPRotary(RIGHT_ROTARY_PIN1, RIGHT_ROTARY_PIN2, CLICKS_PER_STEP);

// on change
void leftRotate(ESPRotary &r)
{
  int position = r.getPosition();
  if (leftRotaryMode == ROTARY_MODE_CHANGE_BRIGHTNESS) {
    if (position < 0) {
      position = 0;
      r.resetPosition(0);
    } else if (position > 255) {
      position = 255;
      r.resetPosition(255);
    }
    idleAnimationArg.brightness = position;
    ws2812fx.setBrightness(idleAnimationArg.brightness);
  } else if (leftRotaryMode == ROTARY_MODE_CHANGE_COLOR) {
    idleAnimationArg.color_id = ws2812fx.color_wheel(ws2812fx.random8());
    ws2812fx.setColor(idleAnimationArg.color_id);
  }
}

void rightRotate(ESPRotary &r)
{
  int position = r.getPosition();
  if (rightRotaryMode == ROTARY_MODE_CHANGE_ANIMATION) {
    if (position < 0) {
      position = 0;
      r.resetPosition(0);
    } else if (position > MODE_COUNT - 1) {
      position = MODE_COUNT - 1;
      r.resetPosition(MODE_COUNT - 1);
    }
    idleAnimationArg.animation_id = position;
    ws2812fx.setMode(idleAnimationArg.animation_id);
  } else if (rightRotaryMode == ROTARY_MODE_CHANGE_SPEED) {
    if (position < SPEED_MIN) {
      position = SPEED_MIN;
      r.resetPosition(SPEED_MIN);
    } else if (position > SPEED_MAX) {
      position = SPEED_MAX;
      r.resetPosition(SPEED_MAX);
    }
    idleAnimationArg.speed = position * ROTARY_SPEED_MULTIPLE;
    ws2812fx.setSpeed(idleAnimationArg.speed);
  }
}
/* #endregion */

/* #region  Button config */
#include <Button2.h>

#define LEFT_BUTTON_PIN D3
#define RIGHT_BUTTON_PIN D4

Button2 leftButton = Button2(LEFT_BUTTON_PIN);
Button2 rightButton = Button2(RIGHT_BUTTON_PIN);

void changeLeftRotaryMode(Button2 &btn)
{
  if (leftRotaryMode == ROTARY_MODE_CHANGE_BRIGHTNESS) {
    leftRotaryMode = ROTARY_MODE_CHANGE_COLOR;
    leftRotary.resetPosition(0);
  } else if (leftRotaryMode == ROTARY_MODE_CHANGE_COLOR) {
    leftRotaryMode = ROTARY_MODE_CHANGE_BRIGHTNESS;
    leftRotary.resetPosition(idleAnimationArg.brightness);
  }
}

void changeRightRotaryMode(Button2 &btn)
{
  if (rightRotaryMode == ROTARY_MODE_CHANGE_ANIMATION) {
    rightRotaryMode = ROTARY_MODE_CHANGE_SPEED;
    rightRotary.resetPosition(idleAnimationArg.speed / ROTARY_SPEED_MULTIPLE);
  } else if (rightRotaryMode == ROTARY_MODE_CHANGE_SPEED) {
    rightRotaryMode = ROTARY_MODE_CHANGE_ANIMATION;
    rightRotary.resetPosition(idleAnimationArg.animation_id);
  }
}
/* #endregion */

/* #region  MQTT Config */
WiFiClient espClient;
PubSubClient client(espClient);

void animationHandler(byte *payload, unsigned int length)
{
  AnimationArg message = AnimationArg_init_zero;
  pb_istream_t stream = pb_istream_from_buffer(payload, length);

  if (!pb_decode(&stream, AnimationArg_fields, &message))
  {
    Serial.printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
    ws2812fx.setMode(FX_MODE_COLOR_WIPE);
    return;
  }

  if (message.duration > 0)
  {
    animationDuration = message.duration;
  }

  if (message.speed > 0)
  {
    ws2812fx.setSpeed(message.speed);
  }


  if (message.brightness > 0)
  {
    ws2812fx.setBrightness(message.brightness);
  }

  if (message.color_id > 0)
  {
    ws2812fx.setColor(message.color_id);
  }

  last_change = millis();
  isIdle = false;
  ws2812fx.setMode(message.animation_id);
  Serial.printf("play animation %u for %lums\n", message.animation_id, animationDuration);
}

void idleAnimationHandler(byte *payload, unsigned int length)
{
  IdleAnimationArg message = IdleAnimationArg_init_zero;
  pb_istream_t stream = pb_istream_from_buffer(payload, length);

  if (!pb_decode(&stream, IdleAnimationArg_fields, &message))
  {
    Serial.printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
    return;
  }

  idleAnimationArg = message;
  saveIdleAnimation(idleAnimationArg);
  if (isIdle) {
    resetIdleAnimation();
  }
  skyStars[message.brightness] = true;
}

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
  if (strcmp(topic, "nguyenvanduocit/feeds/matrix-notification.animation") == 0)
  {
    animationHandler(payload, length);
  } else if (strcmp(topic, "nguyenvanduocit/feeds/matrix-notification.idle-animation") == 0)
  {
    idleAnimationHandler(payload, length);
  }
}

void reconnectMqtt()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
#ifdef MQTT_USER
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD))
#else
    if (client.connect(clientId.c_str()))
#endif
    {
      Serial.println("connected");
      client.subscribe("nguyenvanduocit/feeds/matrix-notification.animation", 0);
      client.subscribe("nguyenvanduocit/feeds/matrix-notification.idle-animation", 0);
      Serial.println("Subscribed");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
    ws2812fx.service();
  }
}
/* #endregion */

void setup()
{
  Serial.begin(115200);
  delay(100);
  EEPROM.begin(512);

 /* #region  Setup Rotaty */
  leftRotary.setChangedHandler(leftRotate);
  rightRotary.setChangedHandler(rightRotate);
  /* #endregion */

  /* #region  Settup Buttons */
  leftButton.setTapHandler(changeLeftRotaryMode);
  rightButton.setTapHandler(changeRightRotaryMode);
  /* #endregion */

  /* #region  Settup Animation */
  loadIdleAnimation(idleAnimationArg);
  ws2812fx.init();
  ws2812fx.setCustomMode(F("twinkleFox"), twinkleFox);
  ws2812fx.setCustomMode(F("profitSky"),profitSky);
  resetIdleAnimation();
  ws2812fx.start();
  /* #endregion */

  /* #region  Setup Wifi */
  WiFi.disconnect();
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  Serial.println("Connectiing to wifi!");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    ws2812fx.service();
  }

  Serial.println("Wifi connectected!");
  Serial.println(WiFi.localIP());
  /* #endregion */

  /* #region  Setup MQTT */
  client.setServer(MQTT_BROKER_ADDRESS, MQTT_BROKER_PORT);
  client.setCallback(mqttCallback);
  last_change = millis();
  /* #endregion */

}

void loop()
{
  /* #region  Mqtt Loop */
  if (!client.connected())
  {
    reconnectMqtt();
  }
  client.loop();
  /* #endregion */

  /* #region  Button Loop */
  leftButton.loop();
  rightButton.loop();
  /* #endregion */

  /* #region  Rotaty loop */
  leftRotary.loop();
  rightRotary.loop();
  /* #endregion */

  /* #region  Animation Loop */

  if (millis() - last_change > animationDuration && !isIdle)
  {
    resetIdleAnimation();
  }
  ws2812fx.service();
  /* #endregion */
}