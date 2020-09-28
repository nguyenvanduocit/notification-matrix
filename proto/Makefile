firmware:
	mkdir -p ../firmware/lib/animation
	protoc --nanopb_out=../firmware/lib/animation ./animation.proto
go:
	mkdir -p ../go-agent/internal/animation
	protoc -I . --go_out=plugins=grpc:../go-agent/internal/animation ./animation.proto
all: firmware go
