# Introduction #

[Protocol Buffers](http://code.google.com/apis/protocolbuffers/) are a language-neutral, platform-neutral, extensible mechanism for serializing structured data.

The module incorporates the protobuf library and adds a BlitzMax compiler which generates pure BlitzMax type structures that are ready to use in your own code.
Since the protobuf library is included you can also optionally generate Java and Python interfaces, therefore providing a possible end-to-end interface for your data.

You can find out more about protocol buffers and the .proto file format from the [Developer Guide](http://code.google.com/apis/protocolbuffers/docs/overview.html).

# How do I use it ? #

## Make the .proto ##

Either write your own, or get one for an architecture you need access to.

## Generating the code ##

_TODO_

## Integrating into your app ##

All you need to do is import the generated .bmx file. For example
```
Import "addressbook.pb.bmx"
```
That gives you access to all the generated Types and enumerations, which you can just start using :
```
Local address_book:AddressBook = New AddressBook.Create()

...

If Not address_book.ParseFromFile(AppArgs[1]) Then
	Print "Failed to parse address book."
	End
End If

...
```

The BaH.protobuf module supports BlitzMax TStreams as well as serializing of String and raw Byte arrays.
