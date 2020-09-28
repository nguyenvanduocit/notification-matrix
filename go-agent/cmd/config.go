package cmd

import (
	"errors"
	"github.com/spf13/cobra"
	"github.com/spf13/viper"
	"google.golang.org/protobuf/proto"
	"matrixnotifier/internal/animation"
)

// configCmd represents the config command
var configCmd = &cobra.Command{
	Use:   "config",
	Short: "Just to see the config",
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

		brightness, err := cmd.Flags().GetUint32("brightness")
		if err != nil {
			return err
		}

		successAnimationArg := &animation.IdleAnimationArg{
			AnimationId: animationID,
			Speed:       speed,
			ColorId:     color,
			Brightness:     brightness,
		}

		animationTopic := viper.GetString(idleAnimationTopicConfigName)

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
	rootCmd.AddCommand(configCmd)
	configCmd.Flags().Uint32P("animation", "a", 22, "the Animation ID (0-62)")
	configCmd.Flags().Uint32P("speed", "s", 100, "speed of the animation(0-65535)")
	configCmd.Flags().Uint32P("color", "c", 0xFFF000, "animation primary color")
	configCmd.Flags().Uint32P("brightness", "b", 1, "the brightness(0-255)")
}
