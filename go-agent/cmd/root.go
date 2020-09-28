/*
Copyright © 2020 NAME HERE <EMAIL ADDRESS>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
package cmd

import (
	"fmt"
	mqtt "github.com/eclipse/paho.mqtt.golang"
	"github.com/spf13/cobra"
	"log"
	"os"

	homedir "github.com/mitchellh/go-homedir"
	"github.com/spf13/viper"
)

const animationTopicConfigName = "animationTopic"
const idleAnimationTopicConfigName = "idleAnimationTopic"

var cfgFile string
var mqttClient mqtt.Client
// rootCmd represents the base command when called without any subcommands
var rootCmd = &cobra.Command{
	Use:   "matrixnotifier",
	Short: "Golang Agent for the Matrix Notification",
	PersistentPreRunE: func(cmd *cobra.Command, args []string) error {
		if mqttClient != nil && mqttClient.IsConnected() {
			return nil
		}

		opts := mqtt.NewClientOptions()

		brokerAddress:= viper.GetString("brokerAddress")
		opts.AddBroker(brokerAddress)

		clientID := viper.GetString("clientID")
		opts.SetClientID(clientID)

		mqttClient = mqtt.NewClient(opts)
		if token := mqttClient.Connect(); token.Wait() && token.Error() != nil {
			return token.Error()
		}

		return nil
	},
	PersistentPostRunE: func(cmd *cobra.Command, args []string) error {
		mqttClient.Disconnect(250)
		return nil
	},
}

func Execute() {
	if err := rootCmd.Execute(); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}

func init() {
	cobra.OnInitialize(initConfig)
	rootCmd.PersistentFlags().StringVar(&cfgFile, "config", "", "config file (default is $HOME/.matrixnotifier.yaml)")
	rootCmd.PersistentFlags().String( "brokerAddress", "broker.hivemq.com:1883", "broker address")
	rootCmd.PersistentFlags().String( "clientID", "matrix-notification-matrix-agent", "client ID")
	rootCmd.PersistentFlags().String(animationTopicConfigName, "nguyenvanduocit/feeds/matrix-notification.animation", "Topic that control the animation")
	rootCmd.PersistentFlags().String( idleAnimationTopicConfigName, "nguyenvanduocit/feeds/matrix-notification.idle-animation", "Topic that control the idle animation")
	if err := viper.BindPFlags(rootCmd.PersistentFlags()); err != nil {
		log.Fatal(err)
	}
}

func initConfig() {
	if cfgFile != "" {
		// Use config file from the flag.
		viper.SetConfigFile(cfgFile)
	} else {
		// Find home directory.
		home, err := homedir.Dir()
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		viper.AddConfigPath("./")
		viper.AddConfigPath(home)
		viper.SetConfigName(".matrixnotifier")
	}

	viper.AutomaticEnv()

	if err := viper.ReadInConfig(); err == nil {
		//fmt.Println("Using config file:", viper.ConfigFileUsed())
	}
}
