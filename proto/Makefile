firmware:
	mkdir -p ../firmware/lib/animation
	protoc --nanopb_out=../firmware/lib/animation ./animation.proto

	mkdir -p ../firmware/lib/brightness
	protoc --nanopb_out=../firmware/lib/brightness ./brightness.proto

	mkdir -p ../firmware/lib/icon
	protoc --nanopb_out=../firmware/lib/icon ./icon.proto
go:
	mkdir -p ../go-agent/internal/animation
	protoc -I . --go_out=plugins=grpc:../go-agent/internal/animation ./animation.proto

	mkdir -p ../go-agent/internal/brightness
	protoc -I . --go_out=plugins=grpc:../go-agent/internal/brightness ./brightness.proto

	mkdir -p ../go-agent/internal/icon
	protoc -I . --go_out=plugins=grpc:../go-agent/internal/icon ./icon.proto
all: firmware go
