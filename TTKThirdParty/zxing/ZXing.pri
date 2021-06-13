# =================================================
# * This file is part of the TTK Tiny Tools project
# * Copyright (C) 2015 - 2021 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
#
# * You should have received a copy of the GNU General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# =================================================

INCLUDEPATH += $$PWD

win32: {
HEADERS += \
    $$PWD/win32/zxing/iconv.h \
    $$PWD/win32/zxing/stdint.h

SOURCES += \
    $$PWD/win32/zxing/win_iconv.c
}

HEADERS += \
    $$PWD/bigint/BigInteger.hh \
    $$PWD/bigint/BigIntegerAlgorithms.hh \
    $$PWD/bigint/BigIntegerLibrary.hh \
    $$PWD/bigint/BigIntegerUtils.hh \
    $$PWD/bigint/BigUnsigned.hh \
    $$PWD/bigint/BigUnsignedInABase.hh \
    $$PWD/bigint/NumberlikeArray.hh \
    $$PWD/zxing/BarcodeFormat.h \
    $$PWD/zxing/Binarizer.h \
    $$PWD/zxing/BinaryBitmap.h \
    $$PWD/zxing/ChecksumException.h \
    $$PWD/zxing/DecodeHints.h \
    $$PWD/zxing/Exception.h \
    $$PWD/zxing/FormatException.h \
    $$PWD/zxing/IllegalStateException.h \
    $$PWD/zxing/InvertedLuminanceSource.h \
    $$PWD/zxing/LuminanceSource.h \
    $$PWD/zxing/MultiFormatReader.h \
    $$PWD/zxing/NotFoundException.h \
    $$PWD/zxing/Reader.h \
    $$PWD/zxing/ReaderException.h \
    $$PWD/zxing/Result.h \
    $$PWD/zxing/ResultPoint.h \
    $$PWD/zxing/ResultPointCallback.h \
    $$PWD/zxing/ZXing.h \
    $$PWD/zxing/aztec/AztecDetectorResult.h \
    $$PWD/zxing/aztec/AztecReader.h \
    $$PWD/zxing/aztec/decoder/Decoder.h \
    $$PWD/zxing/aztec/detector/Detector.h \
    $$PWD/zxing/common/Array.h \
    $$PWD/zxing/common/BitArray.h \
    $$PWD/zxing/common/BitMatrix.h \
    $$PWD/zxing/common/BitSource.h \
    $$PWD/zxing/common/CharacterSetECI.h \
    $$PWD/zxing/common/Counted.h \
    $$PWD/zxing/common/DecoderResult.h \
    $$PWD/zxing/common/DetectorResult.h \
    $$PWD/zxing/common/GlobalHistogramBinarizer.h \
    $$PWD/zxing/common/GreyscaleLuminanceSource.h \
    $$PWD/zxing/common/GreyscaleRotatedLuminanceSource.h \
    $$PWD/zxing/common/GridSampler.h \
    $$PWD/zxing/common/HybridBinarizer.h \
    $$PWD/zxing/common/IllegalArgumentException.h \
    $$PWD/zxing/common/PerspectiveTransform.h \
    $$PWD/zxing/common/Point.h \
    $$PWD/zxing/common/Str.h \
    $$PWD/zxing/common/StringUtils.h \
    $$PWD/zxing/common/detector/JavaMath.h \
    $$PWD/zxing/common/detector/MathUtils.h \
    $$PWD/zxing/common/detector/MonochromeRectangleDetector.h \
    $$PWD/zxing/common/detector/WhiteRectangleDetector.h \
    $$PWD/zxing/common/reedsolomon/GenericGF.h \
    $$PWD/zxing/common/reedsolomon/GenericGFPoly.h \
    $$PWD/zxing/common/reedsolomon/ReedSolomonDecoder.h \
    $$PWD/zxing/common/reedsolomon/ReedSolomonException.h \
    $$PWD/zxing/datamatrix/DataMatrixReader.h \
    $$PWD/zxing/datamatrix/Version.h \
    $$PWD/zxing/datamatrix/decoder/BitMatrixParser.h \
    $$PWD/zxing/datamatrix/decoder/DataBlock.h \
    $$PWD/zxing/datamatrix/decoder/DecodedBitStreamParser.h \
    $$PWD/zxing/datamatrix/decoder/Decoder.h \
    $$PWD/zxing/datamatrix/detector/CornerPoint.h \
    $$PWD/zxing/datamatrix/detector/Detector.h \
    $$PWD/zxing/datamatrix/detector/DetectorException.h \
    $$PWD/zxing/multi/ByQuadrantReader.h \
    $$PWD/zxing/multi/GenericMultipleBarcodeReader.h \
    $$PWD/zxing/multi/MultipleBarcodeReader.h \
    $$PWD/zxing/multi/qrcode/QRCodeMultiReader.h \
    $$PWD/zxing/multi/qrcode/detector/MultiDetector.h \
    $$PWD/zxing/multi/qrcode/detector/MultiFinderPatternFinder.h \
    $$PWD/zxing/oned/CodaBarReader.h \
    $$PWD/zxing/oned/Code128Reader.h \
    $$PWD/zxing/oned/Code39Reader.h \
    $$PWD/zxing/oned/Code93Reader.h \
    $$PWD/zxing/oned/EAN13Reader.h \
    $$PWD/zxing/oned/EAN8Reader.h \
    $$PWD/zxing/oned/ITFReader.h \
    $$PWD/zxing/oned/MultiFormatOneDReader.h \
    $$PWD/zxing/oned/MultiFormatUPCEANReader.h \
    $$PWD/zxing/oned/OneDReader.h \
    $$PWD/zxing/oned/OneDResultPoint.h \
    $$PWD/zxing/oned/UPCAReader.h \
    $$PWD/zxing/oned/UPCEANReader.h \
    $$PWD/zxing/oned/UPCEReader.h \
    $$PWD/zxing/pdf417/PDF417Reader.h \
    $$PWD/zxing/pdf417/decoder/BitMatrixParser.h \
    $$PWD/zxing/pdf417/decoder/DecodedBitStreamParser.h \
    $$PWD/zxing/pdf417/decoder/Decoder.h \
    $$PWD/zxing/pdf417/decoder/ec/ErrorCorrection.h \
    $$PWD/zxing/pdf417/decoder/ec/ModulusGF.h \
    $$PWD/zxing/pdf417/decoder/ec/ModulusPoly.h \
    $$PWD/zxing/pdf417/detector/Detector.h \
    $$PWD/zxing/pdf417/detector/LinesSampler.h \
    $$PWD/zxing/qrcode/ErrorCorrectionLevel.h \
    $$PWD/zxing/qrcode/FormatInformation.h \
    $$PWD/zxing/qrcode/QRCodeReader.h \
    $$PWD/zxing/qrcode/Version.h \
    $$PWD/zxing/qrcode/decoder/BitMatrixParser.h \
    $$PWD/zxing/qrcode/decoder/DataBlock.h \
    $$PWD/zxing/qrcode/decoder/DataMask.h \
    $$PWD/zxing/qrcode/decoder/DecodedBitStreamParser.h \
    $$PWD/zxing/qrcode/decoder/Decoder.h \
    $$PWD/zxing/qrcode/decoder/Mode.h \
    $$PWD/zxing/qrcode/detector/AlignmentPattern.h \
    $$PWD/zxing/qrcode/detector/AlignmentPatternFinder.h \
    $$PWD/zxing/qrcode/detector/Detector.h \
    $$PWD/zxing/qrcode/detector/FinderPattern.h \
    $$PWD/zxing/qrcode/detector/FinderPatternFinder.h \
    $$PWD/zxing/qrcode/detector/FinderPatternInfo.h

    
SOURCES += \
    $$PWD/bigint/BigInteger.cc \
    $$PWD/bigint/BigIntegerAlgorithms.cc \
    $$PWD/bigint/BigIntegerUtils.cc \
    $$PWD/bigint/BigUnsigned.cc \
    $$PWD/bigint/BigUnsignedInABase.cc \
    $$PWD/zxing/BarcodeFormat.cpp \
    $$PWD/zxing/Binarizer.cpp \
    $$PWD/zxing/BinaryBitmap.cpp \
    $$PWD/zxing/ChecksumException.cpp \
    $$PWD/zxing/DecodeHints.cpp \
    $$PWD/zxing/Exception.cpp \
    $$PWD/zxing/FormatException.cpp \
    $$PWD/zxing/InvertedLuminanceSource.cpp \
    $$PWD/zxing/LuminanceSource.cpp \
    $$PWD/zxing/MultiFormatReader.cpp \
    $$PWD/zxing/Reader.cpp \
    $$PWD/zxing/Result.cpp \
    $$PWD/zxing/ResultIO.cpp \
    $$PWD/zxing/ResultPoint.cpp \
    $$PWD/zxing/ResultPointCallback.cpp \
    $$PWD/zxing/aztec/AztecDetectorResult.cpp \
    $$PWD/zxing/aztec/AztecReader.cpp \
    $$PWD/zxing/aztec/decoder/Decoder1.cpp \
    $$PWD/zxing/aztec/detector/Detector1.cpp \
    $$PWD/zxing/common/BitArray.cpp \
    $$PWD/zxing/common/BitArrayIO.cpp \
    $$PWD/zxing/common/BitMatrix.cpp \
    $$PWD/zxing/common/BitSource.cpp \
    $$PWD/zxing/common/CharacterSetECI.cpp \
    $$PWD/zxing/common/DecoderResult.cpp \
    $$PWD/zxing/common/DetectorResult.cpp \
    $$PWD/zxing/common/GlobalHistogramBinarizer.cpp \
    $$PWD/zxing/common/GreyscaleLuminanceSource.cpp \
    $$PWD/zxing/common/GreyscaleRotatedLuminanceSource.cpp \
    $$PWD/zxing/common/GridSampler.cpp \
    $$PWD/zxing/common/HybridBinarizer.cpp \
    $$PWD/zxing/common/IllegalArgumentException.cpp \
    $$PWD/zxing/common/PerspectiveTransform.cpp \
    $$PWD/zxing/common/Str.cpp \
    $$PWD/zxing/common/StringUtils.cpp \
    $$PWD/zxing/common/detector/MonochromeRectangleDetector.cpp \
    $$PWD/zxing/common/detector/WhiteRectangleDetector.cpp \
    $$PWD/zxing/common/reedsolomon/GenericGF.cpp \
    $$PWD/zxing/common/reedsolomon/GenericGFPoly.cpp \
    $$PWD/zxing/common/reedsolomon/ReedSolomonDecoder.cpp \
    $$PWD/zxing/common/reedsolomon/ReedSolomonException.cpp \
    $$PWD/zxing/datamatrix/DataMatrixReader.cpp \
    $$PWD/zxing/datamatrix/Version1.cpp \
    $$PWD/zxing/datamatrix/decoder/BitMatrixParser1.cpp \
    $$PWD/zxing/datamatrix/decoder/DataBlock1.cpp \
    $$PWD/zxing/datamatrix/decoder/DecodedBitStreamParser1.cpp \
    $$PWD/zxing/datamatrix/decoder/Decoder2.cpp \
    $$PWD/zxing/datamatrix/detector/CornerPoint.cpp \
    $$PWD/zxing/datamatrix/detector/Detector2.cpp \
    $$PWD/zxing/datamatrix/detector/DetectorException.cpp \
    $$PWD/zxing/multi/ByQuadrantReader.cpp \
    $$PWD/zxing/multi/GenericMultipleBarcodeReader.cpp \
    $$PWD/zxing/multi/MultipleBarcodeReader.cpp \
    $$PWD/zxing/multi/qrcode/QRCodeMultiReader.cpp \
    $$PWD/zxing/multi/qrcode/detector/MultiDetector.cpp \
    $$PWD/zxing/multi/qrcode/detector/MultiFinderPatternFinder1.cpp \
    $$PWD/zxing/oned/CodaBarReader.cpp \
    $$PWD/zxing/oned/Code128Reader.cpp \
    $$PWD/zxing/oned/Code39Reader.cpp \
    $$PWD/zxing/oned/Code93Reader.cpp \
    $$PWD/zxing/oned/EAN13Reader.cpp \
    $$PWD/zxing/oned/EAN8Reader.cpp \
    $$PWD/zxing/oned/ITFReader.cpp \
    $$PWD/zxing/oned/MultiFormatOneDReader.cpp \
    $$PWD/zxing/oned/MultiFormatUPCEANReader.cpp \
    $$PWD/zxing/oned/OneDReader.cpp \
    $$PWD/zxing/oned/OneDResultPoint.cpp \
    $$PWD/zxing/oned/UPCAReader.cpp \
    $$PWD/zxing/oned/UPCEANReader.cpp \
    $$PWD/zxing/oned/UPCEReader.cpp \
    $$PWD/zxing/pdf417/PDF417Reader.cpp \
    $$PWD/zxing/pdf417/decoder/BitMatrixParser2.cpp \
    $$PWD/zxing/pdf417/decoder/DecodedBitStreamParser2.cpp \
    $$PWD/zxing/pdf417/decoder/Decoder3.cpp \
    $$PWD/zxing/pdf417/decoder/ec/ErrorCorrection.cpp \
    $$PWD/zxing/pdf417/decoder/ec/ModulusGF.cpp \
    $$PWD/zxing/pdf417/decoder/ec/ModulusPoly.cpp \
    $$PWD/zxing/pdf417/detector/Detector3.cpp \
    $$PWD/zxing/pdf417/detector/LinesSampler.cpp \
    $$PWD/zxing/qrcode/ErrorCorrectionLevel.cpp \
    $$PWD/zxing/qrcode/FormatInformation.cpp \
    $$PWD/zxing/qrcode/QRCodeReader.cpp \
    $$PWD/zxing/qrcode/Version2.cpp \
    $$PWD/zxing/qrcode/decoder/BitMatrixParser3.cpp \
    $$PWD/zxing/qrcode/decoder/DataBlock2.cpp \
    $$PWD/zxing/qrcode/decoder/DataMask.cpp \
    $$PWD/zxing/qrcode/decoder/DecodedBitStreamParser3.cpp \
    $$PWD/zxing/qrcode/decoder/Decoder4.cpp \
    $$PWD/zxing/qrcode/decoder/Mode.cpp \
    $$PWD/zxing/qrcode/detector/AlignmentPattern.cpp \
    $$PWD/zxing/qrcode/detector/AlignmentPatternFinder.cpp \
    $$PWD/zxing/qrcode/detector/Detector4.cpp \
    $$PWD/zxing/qrcode/detector/FinderPattern.cpp \
    $$PWD/zxing/qrcode/detector/FinderPatternFinder2.cpp \
    $$PWD/zxing/qrcode/detector/FinderPatternInfo.cpp
