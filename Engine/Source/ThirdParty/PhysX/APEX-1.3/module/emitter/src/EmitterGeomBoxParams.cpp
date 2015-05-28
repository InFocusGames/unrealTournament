/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


// This file was generated by NxParameterized/scripts/GenParameterized.pl
// Created: 2015.01.18 19:26:20

#include "EmitterGeomBoxParams.h"
#include <string.h>
#include <stdlib.h>

using namespace NxParameterized;

namespace physx
{
namespace apex
{
namespace emitter
{

using namespace EmitterGeomBoxParamsNS;

const char* const EmitterGeomBoxParamsFactory::vptr =
    NxParameterized::getVptr<EmitterGeomBoxParams, EmitterGeomBoxParams::ClassAlignment>();

const physx::PxU32 NumParamDefs = 3;
static NxParameterized::DefinitionImpl* ParamDefTable; // now allocated in buildTree [NumParamDefs];


static const size_t ParamLookupChildrenTable[] =
{
	1, 2,
};

#define TENUM(type) physx::##type
#define CHILDREN(index) &ParamLookupChildrenTable[index]
static const NxParameterized::ParamLookupNode ParamLookupTable[NumParamDefs] =
{
	{ TYPE_STRUCT, false, 0, CHILDREN(0), 2 },
	{ TYPE_ENUM, false, (size_t)(&((ParametersStruct*)0)->emitterType), NULL, 0 }, // emitterType
	{ TYPE_VEC3, false, (size_t)(&((ParametersStruct*)0)->extents), NULL, 0 }, // extents
};


bool EmitterGeomBoxParams::mBuiltFlag = false;
NxParameterized::MutexType EmitterGeomBoxParams::mBuiltFlagMutex;

EmitterGeomBoxParams::EmitterGeomBoxParams(NxParameterized::Traits* traits, void* buf, PxI32* refCount) :
	NxParameters(traits, buf, refCount)
{
	//mParameterizedTraits->registerFactory(className(), &EmitterGeomBoxParamsFactoryInst);

	if (!buf) //Do not init data if it is inplace-deserialized
	{
		initDynamicArrays();
		initStrings();
		initReferences();
		initDefaults();
	}
}

EmitterGeomBoxParams::~EmitterGeomBoxParams()
{
	freeStrings();
	freeReferences();
	freeDynamicArrays();
}

void EmitterGeomBoxParams::destroy()
{
	// We cache these fields here to avoid overwrite in destructor
	bool doDeallocateSelf = mDoDeallocateSelf;
	NxParameterized::Traits* traits = mParameterizedTraits;
	physx::PxI32* refCount = mRefCount;
	void* buf = mBuffer;

	this->~EmitterGeomBoxParams();

	NxParameters::destroy(this, traits, doDeallocateSelf, refCount, buf);
}

const NxParameterized::DefinitionImpl* EmitterGeomBoxParams::getParameterDefinitionTree(void)
{
	if (!mBuiltFlag) // Double-checked lock
	{
		NxParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

const NxParameterized::DefinitionImpl* EmitterGeomBoxParams::getParameterDefinitionTree(void) const
{
	EmitterGeomBoxParams* tmpParam = const_cast<EmitterGeomBoxParams*>(this);

	if (!mBuiltFlag) // Double-checked lock
	{
		NxParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			tmpParam->buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

NxParameterized::ErrorType EmitterGeomBoxParams::getParameterHandle(const char* long_name, Handle& handle) const
{
	ErrorType Ret = NxParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

NxParameterized::ErrorType EmitterGeomBoxParams::getParameterHandle(const char* long_name, Handle& handle)
{
	ErrorType Ret = NxParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

void EmitterGeomBoxParams::getVarPtr(const Handle& handle, void*& ptr, size_t& offset) const
{
	ptr = getVarPtrHelper(&ParamLookupTable[0], const_cast<EmitterGeomBoxParams::ParametersStruct*>(&parameters()), handle, offset);
}


/* Dynamic Handle Indices */

void EmitterGeomBoxParams::freeParameterDefinitionTable(NxParameterized::Traits* traits)
{
	if (!traits)
	{
		return;
	}

	if (!mBuiltFlag) // Double-checked lock
	{
		return;
	}

	NxParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);

	if (!mBuiltFlag)
	{
		return;
	}

	for (physx::PxU32 i = 0; i < NumParamDefs; ++i)
	{
		ParamDefTable[i].~DefinitionImpl();
	}

	traits->free(ParamDefTable);

	mBuiltFlag = false;
}

#define PDEF_PTR(index) (&ParamDefTable[index])

void EmitterGeomBoxParams::buildTree(void)
{

	physx::PxU32 allocSize = sizeof(NxParameterized::DefinitionImpl) * NumParamDefs;
	ParamDefTable = (NxParameterized::DefinitionImpl*)(mParameterizedTraits->alloc(allocSize));
	memset(static_cast<void*>(ParamDefTable), 0, allocSize);

	for (physx::PxU32 i = 0; i < NumParamDefs; ++i)
	{
		NX_PARAM_PLACEMENT_NEW(ParamDefTable + i, NxParameterized::DefinitionImpl)(*mParameterizedTraits);
	}

	// Initialize DefinitionImpl node: nodeIndex=0, longName=""
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[0];
		ParamDef->init("", TYPE_STRUCT, "STRUCT", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=1, longName="emitterType"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[1];
		ParamDef->init("emitterType", TYPE_ENUM, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("defaultValue", "rate", true);
		ParamDefTable[1].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[3];
		static Hint* HintPtrTable[3] = { &HintTable[0], &HintTable[1], &HintTable[2], };
		HintTable[0].init("defaultValue", "rate", true);
		HintTable[1].init("longDescription", "rate - The emitter will emit at the rate specified by the asset's rateRange\\n\ndensityOnce - The emitter will fill the geometry according to the asset's densityRange\\n\ndensityBrush - As the emitter moves, the emitter will fill the volume that is not already covered by the previous position\\n\nfill - The emitter will fill the volume with particles based on the particle size\\n\n", true);
		HintTable[2].init("shortDescription", "Emitter Type", true);
		ParamDefTable[1].setHints((const NxParameterized::Hint**)HintPtrTable, 3);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */

		static const char* const EnumVals[] = { "rate", "densityOnce", "densityBrush", "fill" };
		ParamDefTable[1].setEnumVals((const char**)EnumVals, 4);




	}

	// Initialize DefinitionImpl node: nodeIndex=2, longName="extents"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[2];
		ParamDef->init("extents", TYPE_VEC3, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("gameScale", "true", true);
		ParamDefTable[2].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("gameScale", "true", true);
		HintTable[1].init("shortDescription", "Box Extents", true);
		ParamDefTable[2].setHints((const NxParameterized::Hint**)HintPtrTable, 2);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// SetChildren for: nodeIndex=0, longName=""
	{
		static Definition* Children[2];
		Children[0] = PDEF_PTR(1);
		Children[1] = PDEF_PTR(2);

		ParamDefTable[0].setChildren(Children, 2);
	}

	mBuiltFlag = true;

}
void EmitterGeomBoxParams::initStrings(void)
{
}

void EmitterGeomBoxParams::initDynamicArrays(void)
{
}

void EmitterGeomBoxParams::initDefaults(void)
{

	freeStrings();
	freeReferences();
	freeDynamicArrays();
	emitterType = (const char*)"rate";
	extents = physx::PxVec3(init(1, 1, 1));

	initDynamicArrays();
	initStrings();
	initReferences();
}

void EmitterGeomBoxParams::initReferences(void)
{
}

void EmitterGeomBoxParams::freeDynamicArrays(void)
{
}

void EmitterGeomBoxParams::freeStrings(void)
{
}

void EmitterGeomBoxParams::freeReferences(void)
{
}

} // namespace emitter
} // namespace apex
} // namespace physx
