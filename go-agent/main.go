package main

import (
	"flag"

	mqtt "github.com/eclipse/paho.mqtt.golang"
	"github.com/golang/protobuf/proto"

	"notificationmatrixagent/internal/animation"
)

func main() {

	var animationName string
	flag.StringVar(&animationName, "animation", "success", "name of the animation")

	var brokerAddress string
	flag.StringVar(&brokerAddress, "brokerAddress", "broker.mqtt-dashboard.com:1883", "MQTT broker address")

	var clientID string
	flag.StringVar(&clientID, "clientID", "matrix-notification-matrix-agent", "Client ID")

	flag.Parse()

	opts := mqtt.NewClientOptions()
	opts.AddBroker(brokerAddress)
	opts.SetClientID(clientID)
	client := mqtt.NewClient(opts)
	if token := client.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}

	qos := 0
	topic := "notification-matrix/animation"

	var animationID animation.AnimationID

	switch animationName {
	case "success":
		animationID = animation.AnimationID_SUCCESS
	case "error":
		animationID = animation.AnimationID_ERROR
	case "loading":
		animationID = animation.AnimationID_LOADING
	}

	successAnimationArg := &animation.AnimationArg{
		AnimationId: animationID,
		Duration:    100,
	}

	payload, err := proto.Marshal(successAnimationArg)
	if err != nil {
		panic(err)
	}

	token := client.Publish(topic, byte(qos), false, payload)
	token.Wait()
	client.Disconnect(250)
}
