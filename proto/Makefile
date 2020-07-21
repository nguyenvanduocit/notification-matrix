firmware:
	protoc --nanopb_out=../firmware/lib/animation ./*.proto
go:
	protoc -I . --go_out=plugins=grpc:./../go-agent/internal/animation ./*.proto
all: firmware go
