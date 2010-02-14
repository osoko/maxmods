/*
 *  MultiFormatBarcodeReader.cpp
 *  ZXing
 *
 *  Created by Lukasz Warchol on 10-01-26.
 *  Copyright 2010 ZXing authors All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "MultiFormatReader.h"
#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/oned/MultiFormatUPCEANReader.h>
#include <zxing/oned/MultiFormatOneDReader.h>
#include <zxing/ReaderException.h>

namespace zxing {
	MultiFormatReader::MultiFormatReader(){
		readers = new std::vector<Reader*>();

#ifndef WIN32
		readers->push_back(new zxing::qrcode::QRCodeReader());
#endif
		readers->push_back(new zxing::oned::MultiFormatUPCEANReader());
		readers->push_back(new zxing::oned::MultiFormatOneDReader());
	}
	
	Ref<Result> MultiFormatReader::decode(Ref<BinaryBitmap> image){
		int size = readers->size();
		for (int i = 0; i < size; i++) {
			Reader* reader = (*readers)[i];
			try {
				return reader->decode(image);
			} catch (ReaderException re) {
				// continue
			}
		}
		throw ReaderException("No code detected");
	}
	MultiFormatReader::~MultiFormatReader(){
		delete readers;
	}
}