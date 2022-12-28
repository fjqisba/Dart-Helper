#include "Object.h"
#include "../class_id.h"
#include "../globals.h"

Object::Object(const char* type, const char* name, bool isBase):type(type),name(name),isBase(isBase)
{
	
}

namespace Dart212
{
    const intptr_t
        element_size_table[14] = {
            1,   // kTypedDataInt8ArrayCid.
            1,   // kTypedDataUint8ArrayCid.
            1,   // kTypedDataUint8ClampedArrayCid.
            2,   // kTypedDataInt16ArrayCid.
            2,   // kTypedDataUint16ArrayCid.
            4,   // kTypedDataInt32ArrayCid.
            4,   // kTypedDataUint32ArrayCid.
            8,   // kTypedDataInt64ArrayCid.
            8,   // kTypedDataUint64ArrayCid.
            4,   // kTypedDataFloat32ArrayCid.
            8,   // kTypedDataFloat64ArrayCid.
            16,  // kTypedDataFloat32x4ArrayCid.
            16,  // kTypedDataInt32x4ArrayCid.
            16,  // kTypedDataFloat64x2ArrayCid,
    };

    intptr_t TypedDataBase::element_size(intptr_t index)
    {
        intptr_t size = element_size_table[index];
        return size;
    }

    intptr_t TypedDataBase::ElementType(int32_t cid)
    {
        if (cid == kByteDataViewCid) {
            return 0x1;
        }
        else if (IsTypedDataClassId(cid)) {
            const intptr_t index =
                (cid - kTypedDataInt8ArrayCid - kTypedDataCidRemainderInternal) / 3;
            return index;
        }
        else if (IsTypedDataViewClassId(cid)) {
            const intptr_t index =
                (cid - kTypedDataInt8ArrayCid - kTypedDataCidRemainderView) / 3;
            return index;
        }
        else {
            const intptr_t index =
                (cid - kTypedDataInt8ArrayCid - kTypedDataCidRemainderExternal) / 3;
            return index;
        }
        return 0x0;
    }

    intptr_t TypedDataBase::ElementSizeInBytes(int32_t cid)
    {
        return element_size(ElementType(cid));
    }
}

