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
#include "usdMaya/functorPrimReader.h"

PXR_NAMESPACE_OPEN_SCOPE

PxrUsdMayaFunctorPrimReader::PxrUsdMayaFunctorPrimReader(
    const PxrUsdMayaPrimReaderArgs& args, 
    ReaderFn readerFn)
    : PxrUsdMayaPrimReader(args), _readerFn(readerFn)
{
}

bool
PxrUsdMayaFunctorPrimReader::Read(PxrUsdMayaPrimReaderContext* context)
{
    TF_VERIFY(context);
    return _readerFn(_GetArgs(), context);
}

/* static */
PxrUsdMayaPrimReaderPtr
PxrUsdMayaFunctorPrimReader::Create(
        const PxrUsdMayaPrimReaderArgs& args, 
        ReaderFn readerFn)
{
    return std::make_shared<PxrUsdMayaFunctorPrimReader>(args, readerFn);
}

/* static */
std::function< PxrUsdMayaPrimReaderPtr(
        const PxrUsdMayaPrimReaderArgs&) >
PxrUsdMayaFunctorPrimReader::CreateFactory(ReaderFn readerFn)
{
    return std::bind(
            Create,
            std::placeholders::_1,
            readerFn);
}

PXR_NAMESPACE_CLOSE_SCOPE
