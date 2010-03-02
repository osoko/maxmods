// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// http://code.google.com/p/protobuf/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: kenton@google.com (Kenton Varda)
//  Based on original Protocol Buffers design by
//  Sanjay Ghemawat, Jeff Dean, and others.

#ifndef BAH_PROTOBUF_COMPILER_BMX_MESSAGE_H__
#define BAH_PROTOBUF_COMPILER_BMX_MESSAGE_H__

#include <string>
#include <google/protobuf/stubs/common.h>
#include <bah/protobuf/compiler/blitzmax/bmx_field.h>

namespace google {
namespace protobuf {
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace bmx {

class EnumGenerator;           // enum.h
class ExtensionGenerator;      // extension.h

class MessageGenerator {
 public:
  // See generator.cc for the meaning of dllexport_decl.
  explicit MessageGenerator(const Descriptor* descriptor,
                            const string& dllexport_decl);
  ~MessageGenerator();

  void GenerateType(io::Printer* printer); 
  void GenerateEnumDefinitions(io::Printer* printer);
  void GenerateEnumExterns(io::Printer* printer);
  void GenerateFieldAccessorDefinitions(io::Printer* printer);
  void GenerateInlineMethods(io::Printer* printer);
  void GenerateFieldAccessorExterns(io::Printer* printer);
  void GenerateExterns(io::Printer* printer); 
  void GenerateDeclarations(io::Printer* printer); 
  void GenerateGlue(io::Printer* printer); 
  void GenerateFieldAccessorDeclarations(io::Printer* printer);
  void GenerateFieldAccessorGlue(io::Printer* printer);
  
 private:

  const Descriptor* descriptor_;
  string classname_;
  string dllexport_decl_;
  FieldGeneratorMap field_generators_;
  scoped_array<scoped_ptr<MessageGenerator> > nested_generators_;
  scoped_array<scoped_ptr<EnumGenerator> > enum_generators_;
  scoped_array<scoped_ptr<ExtensionGenerator> > extension_generators_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageGenerator);
};

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // BAH_PROTOBUF_COMPILER_BMX_MESSAGE_H__
