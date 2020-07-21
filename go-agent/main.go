package main

import (
	mqtt "github.com/eclipse/paho.mqtt.golang"
	"github.com/golang/protobuf/proto"

	"notificationmatrixagent/internal/animation"
)

func main() {
	opts := mqtt.NewClientOptions()
	opts.AddBroker("broker.mqtt-dashboard.com:1883")
	opts.SetClientID("matrix-notification-matrix-agent")
	client := mqtt.NewClient(opts)
	if token := client.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}
	qos := 0
	topic := "notification-matrix/animation"

	successAnimationArg := &animation.AnimationArg{
		AnimationId: animation.AnimationID_SUCCESS,
		Duration:    500,
	}

	payload, err := proto.Marshal(successAnimationArg)
	if err != nil {
		panic(err)
	}

	token := client.Publish(topic, byte(qos), false, payload)
	token.Wait()
	client.Disconnect(250)
}
