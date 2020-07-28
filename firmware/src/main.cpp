#include <config.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Matrix.h>
#include <animation.h>
#include <PubSubClient.h>
#include <animation.pb.h>
#include <brightness.pb.h>
#include <icon.pb.h>
#include <pb_decode.h>

/************************* Matrix *********************************/

Matrix matrix = Matrix();
Animation animation = Animation(&matrix);

/************************* MQTT Setup *********************************/

WiFiClient espClient;
PubSubClient client(espClient);

void brightnessHandler (byte *payload, unsigned int length) {
  SetBrightnessArg message = SetBrightnessArg_init_zero;
  pb_istream_t stream = pb_istream_from_buffer(payload, length);

  if (!pb_decode(&stream, SetBrightnessArg_fields, &message))
  {
    printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
    animation.errorAnimation(50, 5);
    return;
  }
  matrix.setBrightness(message.level);
}

void iconHandler (byte *payload, unsigned int length) {
  IconArg message = IconArg_init_zero;
  pb_istream_t stream = pb_istream_from_buffer(payload, length);

  if (!pb_decode(&stream, IconArg_fields, &message))
  {
    printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
    animation.errorAnimation(50, 5);
    return;
  }
  Serial.println(message.icon_id);
}


void animationHandler (byte *payload, unsigned int length) {
  AnimationArg message = AnimationArg_init_zero;
  pb_istream_t stream = pb_istream_from_buffer(payload, length);

  if (!pb_decode(&stream, AnimationArg_fields, &message))
  {
    printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
    animation.errorAnimation(50, 5);
    return;
  }
  if (message.animation_id == AnimationID_SUCCESS)
  {
    animation.successAnimation(message.duration, 5);
  }
  else if (message.animation_id == AnimationID_ERROR)
  {
    animation.errorAnimation(message.duration, 5);
  }
  else if (message.animation_id == AnimationID_LOADING)
  {
    animation.loadingAnimation(message.duration);
  }
  else if (message.animation_id == AnimationID_STROBE) {
    animation.strobe(random(255), random(255), random(255), 10, 50, 1000);
  }
  else if (message.animation_id == AnimationID_CYLON_BOUNCE) {
    for(int i = 2; i > 0; i--) {
      animation.cylonBounce(3, 10, 50);
    }
  }
  else if (message.animation_id == AnimationID_SPARKLE) {
    for(int i = NUM_LEDS * 5; i > 0; i--) {
      animation.sparkle(random(255), random(255), random(255), random(50));
    }
  }
  FastLED.clear(true);
}

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
  if (strcmp(topic, "notification-matrix/animation") == 0)
  {
    animationHandler(payload, length);
  } else if (strcmp(topic, "notification-matrix/brightness") == 0)
  {
    brightnessHandler(payload, length);
  } else if (strcmp(topic, "notification-matrix/icon") == 0)
  {
    iconHandler(payload, length);
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
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      client.subscribe("notification-matrix/animation", 0);
      client.subscribe("notification-matrix/brightness", 0);
      client.subscribe("notification-matrix/icon", 0);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

/************************* Main *********************************/

void setup()
{
  Serial.begin(115200);
  delay(10);
  // setup matrix
  matrix.setup();

  // Setup Wifi
  WiFi.disconnect();
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  Serial.println("Connectiing to wifi!");

  while (WiFi.status() != WL_CONNECTED)
  {
    animation.loadingAnimation(10);
  }

  Serial.println("Wifi connectected!");

  animation.successAnimation(50, 3);

  // Setup MQTT
  client.setServer(MQTT_BROKER_ADDRESS, MQTT_BROKER_PORT);
  client.setCallback(mqttCallback);
}

void loop()
{
  if (!client.connected())
  {
    reconnectMqtt();
  }
  client.loop();
}