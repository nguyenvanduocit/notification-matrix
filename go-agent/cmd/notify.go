package cmd

import (
	"errors"
	"github.com/spf13/cobra"
	"github.com/spf13/viper"
	"google.golang.org/protobuf/proto"
	"matrixnotifier/internal/animation"
)

// notifyCmd represents the notify command
var notifyCmd = &cobra.Command{
	Use:   "notify",
	Short: "send a notification",
	RunE: func(cmd *cobra.Command, args []string) error {
		animationID, err := cmd.Flags().GetUint32("animation")
		if err != nil {
			return err
		}

		speed, err := cmd.Flags().GetUint32("speed")
		if err != nil {
			return err
		}

		color, err := cmd.Flags().GetUint32("color")
		if err != nil {
			return err
		}

		duration, err := cmd.Flags().GetUint32("duration")
		if err != nil {
			return err
		}

		brightness, err := cmd.Flags().GetUint32("brightness")
		if err != nil {
			return err
		}

		successAnimationArg := &animation.AnimationArg{
			AnimationId: animationID,
			Duration:    duration,
			Speed:       speed,
			ColorId:     color,
			Brightness:     brightness,
		}

		animationTopic := viper.GetString(animationTopicConfigName)

		payload, err := proto.Marshal(successAnimationArg)
		if err != nil {
			return err
		}
		token := mqttClient.Publish(animationTopic, 0, false, payload)
		if !token.Wait() {
			return errors.New("failed to wait for token finish")
		}
		return nil
	},
}

func init() {
	rootCmd.AddCommand(notifyCmd)
	notifyCmd.Flags().Uint32P("animation", "a", 22, "the Animation ID (0-62)")
	notifyCmd.Flags().Uint32P("speed", "s", 100, "speed of the animation(0-65535)")
	notifyCmd.Flags().Uint32P("color", "c", 0xFFF000, "animation primary color")
	notifyCmd.Flags().Uint32P("duration", "d", 1000, "duration of the animation")
	notifyCmd.Flags().Uint32P("brightness", "b", 1, "the brightness(0-255)")
}
