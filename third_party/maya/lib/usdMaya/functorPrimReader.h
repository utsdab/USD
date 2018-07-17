//
// Copyright 2018 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PXRUSDMAYA_FUNCTORPRIMREADER_H
#define PXRUSDMAYA_FUNCTORPRIMREADER_H

/// \file functorPrimReader.h

#include "pxr/pxr.h"
#include "usdMaya/api.h"
#include "usdMaya/primReader.h"
#include "usdMaya/primReaderArgs.h"
#include "usdMaya/primReaderContext.h"

#include <functional>

PXR_NAMESPACE_OPEN_SCOPE

/// \class PxrUsdMayaFunctorPrimReader
/// \brief This class is scaffolding to hold bare prim reader functions.
/// It is used by the PXRUSDMAYA_DEFINE_READER macro.
///
/// This class can be used as a base for plugins that read USD prims into
/// Maya shapes, as long as you only need a single Read step and not the
/// PostReadSubtree step.
class PxrUsdMayaFunctorPrimReader : public PxrUsdMayaPrimReader
{
public:
    typedef std::function< bool (
            const PxrUsdMayaPrimReaderArgs&,
            PxrUsdMayaPrimReaderContext*) > ReaderFn;

    PXRUSDMAYA_API
    PxrUsdMayaFunctorPrimReader(
            const PxrUsdMayaPrimReaderArgs&,
            ReaderFn);

    PXRUSDMAYA_API
    bool Read(PxrUsdMayaPrimReaderContext* context) override;

    PXRUSDMAYA_API
    static PxrUsdMayaPrimReaderPtr Create(
            const PxrUsdMayaPrimReaderArgs&,
            ReaderFn readerFn);

    PXRUSDMAYA_API
    static std::function< PxrUsdMayaPrimReaderPtr(
            const PxrUsdMayaPrimReaderArgs&) >
            CreateFactory(ReaderFn readerFn);

private:
    ReaderFn _readerFn;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXRUSDMAYA_FUNCTORPRIMREADER_H
