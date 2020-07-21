// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.25.0-devel
// 	protoc        v3.12.3
// source: animation.proto

package animation

import (
	proto "github.com/golang/protobuf/proto"
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	reflect "reflect"
	sync "sync"
)

const (
	// Verify that this generated code is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
	// Verify that runtime/protoimpl is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
)

// This is a compile-time assertion that a sufficiently up-to-date version
// of the legacy proto package is being used.
const _ = proto.ProtoPackageIsVersion4

type AnimationID int32

const (
	AnimationID_SUCCESS AnimationID = 0
	AnimationID_ERROR   AnimationID = 1
	AnimationID_LOADING AnimationID = 2
)

// Enum value maps for AnimationID.
var (
	AnimationID_name = map[int32]string{
		0: "SUCCESS",
		1: "ERROR",
		2: "LOADING",
	}
	AnimationID_value = map[string]int32{
		"SUCCESS": 0,
		"ERROR":   1,
		"LOADING": 2,
	}
)

func (x AnimationID) Enum() *AnimationID {
	p := new(AnimationID)
	*p = x
	return p
}

func (x AnimationID) String() string {
	return protoimpl.X.EnumStringOf(x.Descriptor(), protoreflect.EnumNumber(x))
}

func (AnimationID) Descriptor() protoreflect.EnumDescriptor {
	return file_animation_proto_enumTypes[0].Descriptor()
}

func (AnimationID) Type() protoreflect.EnumType {
	return &file_animation_proto_enumTypes[0]
}

func (x AnimationID) Number() protoreflect.EnumNumber {
	return protoreflect.EnumNumber(x)
}

// Deprecated: Use AnimationID.Descriptor instead.
func (AnimationID) EnumDescriptor() ([]byte, []int) {
	return file_animation_proto_rawDescGZIP(), []int{0}
}

type AnimationArg struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Duration    int32       `protobuf:"varint,1,opt,name=duration,proto3" json:"duration,omitempty"`
	AnimationId AnimationID `protobuf:"varint,2,opt,name=animation_id,json=animationId,proto3,enum=AnimationID" json:"animation_id,omitempty"`
}

func (x *AnimationArg) Reset() {
	*x = AnimationArg{}
	if protoimpl.UnsafeEnabled {
		mi := &file_animation_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *AnimationArg) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*AnimationArg) ProtoMessage() {}

func (x *AnimationArg) ProtoReflect() protoreflect.Message {
	mi := &file_animation_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use AnimationArg.ProtoReflect.Descriptor instead.
func (*AnimationArg) Descriptor() ([]byte, []int) {
	return file_animation_proto_rawDescGZIP(), []int{0}
}

func (x *AnimationArg) GetDuration() int32 {
	if x != nil {
		return x.Duration
	}
	return 0
}

func (x *AnimationArg) GetAnimationId() AnimationID {
	if x != nil {
		return x.AnimationId
	}
	return AnimationID_SUCCESS
}

var File_animation_proto protoreflect.FileDescriptor

var file_animation_proto_rawDesc = []byte{
	0x0a, 0x0f, 0x61, 0x6e, 0x69, 0x6d, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x70, 0x72, 0x6f, 0x74,
	0x6f, 0x22, 0x5b, 0x0a, 0x0c, 0x41, 0x6e, 0x69, 0x6d, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x41, 0x72,
	0x67, 0x12, 0x1a, 0x0a, 0x08, 0x64, 0x75, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x18, 0x01, 0x20,
	0x01, 0x28, 0x05, 0x52, 0x08, 0x64, 0x75, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x12, 0x2f, 0x0a,
	0x0c, 0x61, 0x6e, 0x69, 0x6d, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x5f, 0x69, 0x64, 0x18, 0x02, 0x20,
	0x01, 0x28, 0x0e, 0x32, 0x0c, 0x2e, 0x41, 0x6e, 0x69, 0x6d, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x49,
	0x44, 0x52, 0x0b, 0x61, 0x6e, 0x69, 0x6d, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x49, 0x64, 0x2a, 0x32,
	0x0a, 0x0b, 0x41, 0x6e, 0x69, 0x6d, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x49, 0x44, 0x12, 0x0b, 0x0a,
	0x07, 0x53, 0x55, 0x43, 0x43, 0x45, 0x53, 0x53, 0x10, 0x00, 0x12, 0x09, 0x0a, 0x05, 0x45, 0x52,
	0x52, 0x4f, 0x52, 0x10, 0x01, 0x12, 0x0b, 0x0a, 0x07, 0x4c, 0x4f, 0x41, 0x44, 0x49, 0x4e, 0x47,
	0x10, 0x02, 0x42, 0x0d, 0x5a, 0x0b, 0x2e, 0x3b, 0x61, 0x6e, 0x69, 0x6d, 0x61, 0x74, 0x69, 0x6f,
	0x6e, 0x62, 0x06, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x33,
}

var (
	file_animation_proto_rawDescOnce sync.Once
	file_animation_proto_rawDescData = file_animation_proto_rawDesc
)

func file_animation_proto_rawDescGZIP() []byte {
	file_animation_proto_rawDescOnce.Do(func() {
		file_animation_proto_rawDescData = protoimpl.X.CompressGZIP(file_animation_proto_rawDescData)
	})
	return file_animation_proto_rawDescData
}

var file_animation_proto_enumTypes = make([]protoimpl.EnumInfo, 1)
var file_animation_proto_msgTypes = make([]protoimpl.MessageInfo, 1)
var file_animation_proto_goTypes = []interface{}{
	(AnimationID)(0),     // 0: AnimationID
	(*AnimationArg)(nil), // 1: AnimationArg
}
var file_animation_proto_depIdxs = []int32{
	0, // 0: AnimationArg.animation_id:type_name -> AnimationID
	1, // [1:1] is the sub-list for method output_type
	1, // [1:1] is the sub-list for method input_type
	1, // [1:1] is the sub-list for extension type_name
	1, // [1:1] is the sub-list for extension extendee
	0, // [0:1] is the sub-list for field type_name
}

func init() { file_animation_proto_init() }
func file_animation_proto_init() {
	if File_animation_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_animation_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*AnimationArg); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_animation_proto_rawDesc,
			NumEnums:      1,
			NumMessages:   1,
			NumExtensions: 0,
			NumServices:   0,
		},
		GoTypes:           file_animation_proto_goTypes,
		DependencyIndexes: file_animation_proto_depIdxs,
		EnumInfos:         file_animation_proto_enumTypes,
		MessageInfos:      file_animation_proto_msgTypes,
	}.Build()
	File_animation_proto = out.File
	file_animation_proto_rawDesc = nil
	file_animation_proto_goTypes = nil
	file_animation_proto_depIdxs = nil
}
