# ***************************************************************************
# * This file is part of the TTK Tiny Tools project
# * Copyright (C) 2015 - 2025 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU Lesser General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU Lesser General Public License for more details.
#
# * You should have received a copy of the GNU Lesser General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# ***************************************************************************

cmake_minimum_required(VERSION 3.18.0)

project(TTKThirdParty)

set(HEADER_FILES
  qrencode/bitstream.h
  qrencode/config.h
  qrencode/mask.h
  qrencode/mmask.h
  qrencode/mqrspec.h
  qrencode/qrencode_inner.h
  qrencode/qrencode.h
  qrencode/qrinput.h
  qrencode/qrspec.h
  qrencode/rscode.h
  qrencode/rsecc.h
  qrencode/split.h
  zxing/bigint/BigInteger.hh
  zxing/bigint/BigIntegerAlgorithms.hh
  zxing/bigint/BigIntegerLibrary.hh
  zxing/bigint/BigIntegerUtils.hh
  zxing/bigint/BigUnsigned.hh
  zxing/bigint/BigUnsignedInABase.hh
  zxing/bigint/NumberlikeArray.hh
  zxing/zxing/BarcodeFormat.h
  zxing/zxing/Binarizer.h
  zxing/zxing/BinaryBitmap.h
  zxing/zxing/ChecksumException.h
  zxing/zxing/DecodeHints.h
  zxing/zxing/Exception.h
  zxing/zxing/FormatException.h
  zxing/zxing/IllegalStateException.h
  zxing/zxing/InvertedLuminanceSource.h
  zxing/zxing/LuminanceSource.h
  zxing/zxing/MultiFormatReader.h
  zxing/zxing/NotFoundException.h
  zxing/zxing/Reader.h
  zxing/zxing/ReaderException.h
  zxing/zxing/Result.h
  zxing/zxing/ResultPoint.h
  zxing/zxing/ResultPointCallback.h
  zxing/zxing/ZXing.h
  zxing/zxing/aztec/AztecDetectorResult.h
  zxing/zxing/aztec/AztecReader.h
  zxing/zxing/aztec/decoder/Decoder.h
  zxing/zxing/aztec/detector/Detector.h
  zxing/zxing/common/Array.h
  zxing/zxing/common/BitArray.h
  zxing/zxing/common/BitMatrix.h
  zxing/zxing/common/BitSource.h
  zxing/zxing/common/CharacterSetECI.h
  zxing/zxing/common/Counted.h
  zxing/zxing/common/DecoderResult.h
  zxing/zxing/common/DetectorResult.h
  zxing/zxing/common/GlobalHistogramBinarizer.h
  zxing/zxing/common/GreyscaleLuminanceSource.h
  zxing/zxing/common/GreyscaleRotatedLuminanceSource.h
  zxing/zxing/common/GridSampler.h
  zxing/zxing/common/HybridBinarizer.h
  zxing/zxing/common/IllegalArgumentException.h
  zxing/zxing/common/PerspectiveTransform.h
  zxing/zxing/common/Point.h
  zxing/zxing/common/Str.h
  zxing/zxing/common/StringUtils.h
  zxing/zxing/common/detector/JavaMath.h
  zxing/zxing/common/detector/MathUtils.h
  zxing/zxing/common/detector/MonochromeRectangleDetector.h
  zxing/zxing/common/detector/WhiteRectangleDetector.h
  zxing/zxing/common/reedsolomon/GenericGF.h
  zxing/zxing/common/reedsolomon/GenericGFPoly.h
  zxing/zxing/common/reedsolomon/ReedSolomonDecoder.h
  zxing/zxing/common/reedsolomon/ReedSolomonException.h
  zxing/zxing/datamatrix/DataMatrixReader.h
  zxing/zxing/datamatrix/Version.h
  zxing/zxing/datamatrix/decoder/BitMatrixParser.h
  zxing/zxing/datamatrix/decoder/DataBlock.h
  zxing/zxing/datamatrix/decoder/DecodedBitStreamParser.h
  zxing/zxing/datamatrix/decoder/Decoder.h
  zxing/zxing/datamatrix/detector/CornerPoint.h
  zxing/zxing/datamatrix/detector/Detector.h
  zxing/zxing/datamatrix/detector/DetectorException.h
  zxing/zxing/multi/ByQuadrantReader.h
  zxing/zxing/multi/GenericMultipleBarcodeReader.h
  zxing/zxing/multi/MultipleBarcodeReader.h
  zxing/zxing/multi/qrcode/QRCodeMultiReader.h
  zxing/zxing/multi/qrcode/detector/MultiDetector.h
  zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.h
  zxing/zxing/oned/CodaBarReader.h
  zxing/zxing/oned/Code128Reader.h
  zxing/zxing/oned/Code39Reader.h
  zxing/zxing/oned/Code93Reader.h
  zxing/zxing/oned/EAN13Reader.h
  zxing/zxing/oned/EAN8Reader.h
  zxing/zxing/oned/ITFReader.h
  zxing/zxing/oned/MultiFormatOneDReader.h
  zxing/zxing/oned/MultiFormatUPCEANReader.h
  zxing/zxing/oned/OneDReader.h
  zxing/zxing/oned/OneDResultPoint.h
  zxing/zxing/oned/UPCAReader.h
  zxing/zxing/oned/UPCEANReader.h
  zxing/zxing/oned/UPCEReader.h
  zxing/zxing/pdf417/PDF417Reader.h
  zxing/zxing/pdf417/decoder/BitMatrixParser.h
  zxing/zxing/pdf417/decoder/DecodedBitStreamParser.h
  zxing/zxing/pdf417/decoder/Decoder.h
  zxing/zxing/pdf417/decoder/ec/ErrorCorrection.h
  zxing/zxing/pdf417/decoder/ec/ModulusGF.h
  zxing/zxing/pdf417/decoder/ec/ModulusPoly.h
  zxing/zxing/pdf417/detector/Detector.h
  zxing/zxing/pdf417/detector/LinesSampler.h
  zxing/zxing/qrcode/ErrorCorrectionLevel.h
  zxing/zxing/qrcode/FormatInformation.h
  zxing/zxing/qrcode/QRCodeReader.h
  zxing/zxing/qrcode/Version.h
  zxing/zxing/qrcode/decoder/BitMatrixParser.h
  zxing/zxing/qrcode/decoder/DataBlock.h
  zxing/zxing/qrcode/decoder/DataMask.h
  zxing/zxing/qrcode/decoder/DecodedBitStreamParser.h
  zxing/zxing/qrcode/decoder/Decoder.h
  zxing/zxing/qrcode/decoder/Mode.h
  zxing/zxing/qrcode/detector/AlignmentPattern.h
  zxing/zxing/qrcode/detector/AlignmentPatternFinder.h
  zxing/zxing/qrcode/detector/Detector.h
  zxing/zxing/qrcode/detector/FinderPattern.h
  zxing/zxing/qrcode/detector/FinderPatternFinder.h
  zxing/zxing/qrcode/detector/FinderPatternInfo.h
)

set(SOURCE_FILES
  qrencode/bitstream.c
  qrencode/mask.c
  qrencode/mmask.c
  qrencode/mqrspec.c
  qrencode/qrencode.c
  qrencode/qrinput.c
  qrencode/qrspec.c
  qrencode/rscode.c
  qrencode/rsecc.c
  qrencode/split.c
  zxing/bigint/BigInteger.cc
  zxing/bigint/BigIntegerAlgorithms.cc
  zxing/bigint/BigIntegerUtils.cc
  zxing/bigint/BigUnsigned.cc
  zxing/bigint/BigUnsignedInABase.cc
  zxing/zxing/BarcodeFormat.cpp
  zxing/zxing/Binarizer.cpp
  zxing/zxing/BinaryBitmap.cpp
  zxing/zxing/ChecksumException.cpp
  zxing/zxing/DecodeHints.cpp
  zxing/zxing/Exception.cpp
  zxing/zxing/FormatException.cpp
  zxing/zxing/InvertedLuminanceSource.cpp
  zxing/zxing/LuminanceSource.cpp
  zxing/zxing/MultiFormatReader.cpp
  zxing/zxing/Reader.cpp
  zxing/zxing/Result.cpp
  zxing/zxing/ResultIO.cpp
  zxing/zxing/ResultPoint.cpp
  zxing/zxing/ResultPointCallback.cpp
  zxing/zxing/aztec/AztecDetectorResult.cpp
  zxing/zxing/aztec/AztecReader.cpp
  zxing/zxing/aztec/decoder/Decoder1.cpp
  zxing/zxing/aztec/detector/Detector1.cpp
  zxing/zxing/common/BitArray.cpp
  zxing/zxing/common/BitArrayIO.cpp
  zxing/zxing/common/BitMatrix.cpp
  zxing/zxing/common/BitSource.cpp
  zxing/zxing/common/CharacterSetECI.cpp
  zxing/zxing/common/DecoderResult.cpp
  zxing/zxing/common/DetectorResult.cpp
  zxing/zxing/common/GlobalHistogramBinarizer.cpp
  zxing/zxing/common/GreyscaleLuminanceSource.cpp
  zxing/zxing/common/GreyscaleRotatedLuminanceSource.cpp
  zxing/zxing/common/GridSampler.cpp
  zxing/zxing/common/HybridBinarizer.cpp
  zxing/zxing/common/IllegalArgumentException.cpp
  zxing/zxing/common/PerspectiveTransform.cpp
  zxing/zxing/common/Str.cpp
  zxing/zxing/common/StringUtils.cpp
  zxing/zxing/common/detector/MonochromeRectangleDetector.cpp
  zxing/zxing/common/detector/WhiteRectangleDetector.cpp
  zxing/zxing/common/reedsolomon/GenericGF.cpp
  zxing/zxing/common/reedsolomon/GenericGFPoly.cpp
  zxing/zxing/common/reedsolomon/ReedSolomonDecoder.cpp
  zxing/zxing/common/reedsolomon/ReedSolomonException.cpp
  zxing/zxing/datamatrix/DataMatrixReader.cpp
  zxing/zxing/datamatrix/Version1.cpp
  zxing/zxing/datamatrix/decoder/BitMatrixParser1.cpp
  zxing/zxing/datamatrix/decoder/DataBlock1.cpp
  zxing/zxing/datamatrix/decoder/DecodedBitStreamParser1.cpp
  zxing/zxing/datamatrix/decoder/Decoder2.cpp
  zxing/zxing/datamatrix/detector/CornerPoint.cpp
  zxing/zxing/datamatrix/detector/Detector2.cpp
  zxing/zxing/datamatrix/detector/DetectorException.cpp
  zxing/zxing/multi/ByQuadrantReader.cpp
  zxing/zxing/multi/GenericMultipleBarcodeReader.cpp
  zxing/zxing/multi/MultipleBarcodeReader.cpp
  zxing/zxing/multi/qrcode/QRCodeMultiReader.cpp
  zxing/zxing/multi/qrcode/detector/MultiDetector.cpp
  zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder1.cpp
  zxing/zxing/oned/CodaBarReader.cpp
  zxing/zxing/oned/Code128Reader.cpp
  zxing/zxing/oned/Code39Reader.cpp
  zxing/zxing/oned/Code93Reader.cpp
  zxing/zxing/oned/EAN13Reader.cpp
  zxing/zxing/oned/EAN8Reader.cpp
  zxing/zxing/oned/ITFReader.cpp
  zxing/zxing/oned/MultiFormatOneDReader.cpp
  zxing/zxing/oned/MultiFormatUPCEANReader.cpp
  zxing/zxing/oned/OneDReader.cpp
  zxing/zxing/oned/OneDResultPoint.cpp
  zxing/zxing/oned/UPCAReader.cpp
  zxing/zxing/oned/UPCEANReader.cpp
  zxing/zxing/oned/UPCEReader.cpp
  zxing/zxing/pdf417/PDF417Reader.cpp
  zxing/zxing/pdf417/decoder/BitMatrixParser2.cpp
  zxing/zxing/pdf417/decoder/DecodedBitStreamParser2.cpp
  zxing/zxing/pdf417/decoder/Decoder3.cpp
  zxing/zxing/pdf417/decoder/ec/ErrorCorrection.cpp
  zxing/zxing/pdf417/decoder/ec/ModulusGF.cpp
  zxing/zxing/pdf417/decoder/ec/ModulusPoly.cpp
  zxing/zxing/pdf417/detector/Detector3.cpp
  zxing/zxing/pdf417/detector/LinesSampler.cpp
  zxing/zxing/qrcode/ErrorCorrectionLevel.cpp
  zxing/zxing/qrcode/FormatInformation.cpp
  zxing/zxing/qrcode/QRCodeReader.cpp
  zxing/zxing/qrcode/Version2.cpp
  zxing/zxing/qrcode/decoder/BitMatrixParser3.cpp
  zxing/zxing/qrcode/decoder/DataBlock2.cpp
  zxing/zxing/qrcode/decoder/DataMask.cpp
  zxing/zxing/qrcode/decoder/DecodedBitStreamParser3.cpp
  zxing/zxing/qrcode/decoder/Decoder4.cpp
  zxing/zxing/qrcode/decoder/Mode.cpp
  zxing/zxing/qrcode/detector/AlignmentPattern.cpp
  zxing/zxing/qrcode/detector/AlignmentPatternFinder.cpp
  zxing/zxing/qrcode/detector/Detector4.cpp
  zxing/zxing/qrcode/detector/FinderPattern.cpp
  zxing/zxing/qrcode/detector/FinderPatternFinder2.cpp
  zxing/zxing/qrcode/detector/FinderPatternInfo.cpp
)

if(WIN32)
  list(APPEND HEADER_FILES zxing/win32/zxing/iconv.h zxing/win32/zxing/stdint.h ${PROJECT_NAME}.rc)
  list(APPEND SOURCE_FILES zxing/win32/zxing/win_iconv.c)
endif()

if(TTK_QT_VERSION VERSION_EQUAL "4")
  qt4_wrap_cpp(MOC_FILES ${HEADER_FILES})

  list(APPEND QT_LINK_LIBS ${QT_QTCORE_LIBRARY})
elseif(TTK_QT_VERSION VERSION_EQUAL "5")
  qt5_wrap_cpp(MOC_FILES ${HEADER_FILES})

  list(APPEND QT_LINK_LIBS Qt5::Core)
elseif(TTK_QT_VERSION VERSION_EQUAL "6")
  qt6_wrap_cpp(MOC_FILES ${HEADER_FILES})

  list(APPEND QT_LINK_LIBS Qt6::Core)
endif()

if(TTK_BUILD_SHARED)
  add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_FILES})
else()
  add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_FILES})
endif()
target_link_libraries(${PROJECT_NAME} ${QT_LINK_LIBS})
