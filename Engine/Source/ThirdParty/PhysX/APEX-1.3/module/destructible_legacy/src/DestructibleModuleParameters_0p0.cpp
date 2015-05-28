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
// Created: 2015.01.18 19:26:28

#include "DestructibleModuleParameters_0p0.h"
#include <string.h>
#include <stdlib.h>

using namespace NxParameterized;

namespace physx
{
namespace apex
{

using namespace DestructibleModuleParameters_0p0NS;

const char* const DestructibleModuleParameters_0p0Factory::vptr =
    NxParameterized::getVptr<DestructibleModuleParameters_0p0, DestructibleModuleParameters_0p0::ClassAlignment>();

const physx::PxU32 NumParamDefs = 17;
static NxParameterized::DefinitionImpl* ParamDefTable; // now allocated in buildTree [NumParamDefs];


static const size_t ParamLookupChildrenTable[] =
{
	1, 11, 12, 13, 14, 15, 16, 2, 3, 4, 5, 6, 7, 8, 9, 10,
};

#define TENUM(type) physx::##type
#define CHILDREN(index) &ParamLookupChildrenTable[index]
static const NxParameterized::ParamLookupNode ParamLookupTable[NumParamDefs] =
{
	{ TYPE_STRUCT, false, 0, CHILDREN(0), 7 },
	{ TYPE_STRUCT, false, (size_t)(&((ParametersStruct*)0)->gpuRigidBodySettings), CHILDREN(7), 9 }, // gpuRigidBodySettings
	{ TYPE_I32, false, (size_t)(&((GRBSettings_Type*)0)->gpuDeviceOrdinal), NULL, 0 }, // gpuRigidBodySettings.gpuDeviceOrdinal
	{ TYPE_F32, false, (size_t)(&((GRBSettings_Type*)0)->meshCellSize), NULL, 0 }, // gpuRigidBodySettings.meshCellSize
	{ TYPE_F32, false, (size_t)(&((GRBSettings_Type*)0)->skinWidth), NULL, 0 }, // gpuRigidBodySettings.skinWidth
	{ TYPE_U32, false, (size_t)(&((GRBSettings_Type*)0)->nonPenSolverPosIterCount), NULL, 0 }, // gpuRigidBodySettings.nonPenSolverPosIterCount
	{ TYPE_U32, false, (size_t)(&((GRBSettings_Type*)0)->frictionSolverPosIterCount), NULL, 0 }, // gpuRigidBodySettings.frictionSolverPosIterCount
	{ TYPE_U32, false, (size_t)(&((GRBSettings_Type*)0)->frictionSolverVelIterCount), NULL, 0 }, // gpuRigidBodySettings.frictionSolverVelIterCount
	{ TYPE_F32, false, (size_t)(&((GRBSettings_Type*)0)->maxLinAcceleration), NULL, 0 }, // gpuRigidBodySettings.maxLinAcceleration
	{ TYPE_U32, false, (size_t)(&((GRBSettings_Type*)0)->gpuMemSceneSize), NULL, 0 }, // gpuRigidBodySettings.gpuMemSceneSize
	{ TYPE_U32, false, (size_t)(&((GRBSettings_Type*)0)->gpuMemTempDataSize), NULL, 0 }, // gpuRigidBodySettings.gpuMemTempDataSize
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->maxDynamicChunkIslandCount), NULL, 0 }, // maxDynamicChunkIslandCount
	{ TYPE_BOOL, false, (size_t)(&((ParametersStruct*)0)->sortFIFOByBenefit), NULL, 0 }, // sortFIFOByBenefit
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->validBoundsPadding), NULL, 0 }, // validBoundsPadding
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->maxChunkSeparationLOD), NULL, 0 }, // maxChunkSeparationLOD
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->maxActorCreatesPerFrame), NULL, 0 }, // maxActorCreatesPerFrame
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->maxChunkDepthOffset), NULL, 0 }, // maxChunkDepthOffset
};


bool DestructibleModuleParameters_0p0::mBuiltFlag = false;
NxParameterized::MutexType DestructibleModuleParameters_0p0::mBuiltFlagMutex;

DestructibleModuleParameters_0p0::DestructibleModuleParameters_0p0(NxParameterized::Traits* traits, void* buf, PxI32* refCount) :
	NxParameters(traits, buf, refCount)
{
	//mParameterizedTraits->registerFactory(className(), &DestructibleModuleParameters_0p0FactoryInst);

	if (!buf) //Do not init data if it is inplace-deserialized
	{
		initDynamicArrays();
		initStrings();
		initReferences();
		initDefaults();
	}
}

DestructibleModuleParameters_0p0::~DestructibleModuleParameters_0p0()
{
	freeStrings();
	freeReferences();
	freeDynamicArrays();
}

void DestructibleModuleParameters_0p0::destroy()
{
	// We cache these fields here to avoid overwrite in destructor
	bool doDeallocateSelf = mDoDeallocateSelf;
	NxParameterized::Traits* traits = mParameterizedTraits;
	physx::PxI32* refCount = mRefCount;
	void* buf = mBuffer;

	this->~DestructibleModuleParameters_0p0();

	NxParameters::destroy(this, traits, doDeallocateSelf, refCount, buf);
}

const NxParameterized::DefinitionImpl* DestructibleModuleParameters_0p0::getParameterDefinitionTree(void)
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

const NxParameterized::DefinitionImpl* DestructibleModuleParameters_0p0::getParameterDefinitionTree(void) const
{
	DestructibleModuleParameters_0p0* tmpParam = const_cast<DestructibleModuleParameters_0p0*>(this);

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

NxParameterized::ErrorType DestructibleModuleParameters_0p0::getParameterHandle(const char* long_name, Handle& handle) const
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

NxParameterized::ErrorType DestructibleModuleParameters_0p0::getParameterHandle(const char* long_name, Handle& handle)
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

void DestructibleModuleParameters_0p0::getVarPtr(const Handle& handle, void*& ptr, size_t& offset) const
{
	ptr = getVarPtrHelper(&ParamLookupTable[0], const_cast<DestructibleModuleParameters_0p0::ParametersStruct*>(&parameters()), handle, offset);
}


/* Dynamic Handle Indices */

void DestructibleModuleParameters_0p0::freeParameterDefinitionTable(NxParameterized::Traits* traits)
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

void DestructibleModuleParameters_0p0::buildTree(void)
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

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "This class is used for initializing the NxModuleDestructible.", true);
		ParamDefTable[0].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=1, longName="gpuRigidBodySettings"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[1];
		ParamDef->init("gpuRigidBodySettings", TYPE_STRUCT, "GRBSettings", true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "See the GRBParameters struct.  The user can enable/disable GPU rigid bodies, and set various parameters for them.", true);
		ParamDefTable[1].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=2, longName="gpuRigidBodySettings.gpuDeviceOrdinal"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[2];
		ParamDef->init("gpuDeviceOrdinal", TYPE_I32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "Leaving this field at its default value (-1) will disable GRB entirely.  Setting this field to -2 will allow GRB to use the default PhysX GPU as defined by the NVIDIA control panel.  Any other value will explicitly specify the GPU ordinal to use for all GRB scenes.", true);
		HintTable[1].init("shortDescription", "override automatic GPU detection and selection", true);
		ParamDefTable[2].setHints((const NxParameterized::Hint**)HintPtrTable, 2);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=3, longName="gpuRigidBodySettings.meshCellSize"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[3];
		ParamDef->init("meshCellSize", TYPE_F32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Size of grid cells used in mesh collision.", true);
		ParamDefTable[3].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=4, longName="gpuRigidBodySettings.skinWidth"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[4];
		ParamDef->init("skinWidth", TYPE_F32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Collision skin width, as in PhysX.", true);
		ParamDefTable[4].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=5, longName="gpuRigidBodySettings.nonPenSolverPosIterCount"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[5];
		ParamDef->init("nonPenSolverPosIterCount", TYPE_U32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Number of non-penetration solver iterations.", true);
		ParamDefTable[5].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=6, longName="gpuRigidBodySettings.frictionSolverPosIterCount"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[6];
		ParamDef->init("frictionSolverPosIterCount", TYPE_U32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Number of friction solver position iterations.", true);
		ParamDefTable[6].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=7, longName="gpuRigidBodySettings.frictionSolverVelIterCount"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[7];
		ParamDef->init("frictionSolverVelIterCount", TYPE_U32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Number of friction solver velocity iterations.", true);
		ParamDefTable[7].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=8, longName="gpuRigidBodySettings.maxLinAcceleration"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[8];
		ParamDef->init("maxLinAcceleration", TYPE_F32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Maximum linear acceleration", true);
		ParamDefTable[8].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=9, longName="gpuRigidBodySettings.gpuMemSceneSize"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[9];
		ParamDef->init("gpuMemSceneSize", TYPE_U32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Amount (in MB) of GPU memory to allocate for GRB scene data (shapes, actors etc)", true);
		ParamDefTable[9].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=10, longName="gpuRigidBodySettings.gpuMemTempDataSize"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[10];
		ParamDef->init("gpuMemTempDataSize", TYPE_U32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Amount (in MB) of GPU memory to allocate for GRB temporary data (broadphase pairs, contacts etc)", true);
		ParamDefTable[10].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=11, longName="maxDynamicChunkIslandCount"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[11];
		ParamDef->init("maxDynamicChunkIslandCount", TYPE_U32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "The maximum number of dynamic NxActors that will be allowed to be active per NxApexScene. A value of 0 (the default) is interpreted as no limit.", true);
		ParamDefTable[11].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=12, longName="sortFIFOByBenefit"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[12];
		ParamDef->init("sortFIFOByBenefit", TYPE_BOOL, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Instead of keeping the maxCount youngest, use maxCount largest benefit if this is true.", true);
		ParamDefTable[12].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=13, longName="validBoundsPadding"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[13];
		ParamDef->init("validBoundsPadding", TYPE_F32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "The padding applied to the combined scene valid bounds and NxDestructible actor bounds.  The final combined and passed bounds is used to cull NxActors and GrbActors", true);
		ParamDefTable[13].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=14, longName="maxChunkSeparationLOD"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[14];
		ParamDef->init("maxChunkSeparationLOD", TYPE_F32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("max", physx::PxU64(1), true);
		HintTable[1].init("min", physx::PxU64(0), true);
		ParamDefTable[14].setHints((const NxParameterized::Hint**)HintPtrTable, 2);

#else

		static HintImpl HintTable[4];
		static Hint* HintPtrTable[4] = { &HintTable[0], &HintTable[1], &HintTable[2], &HintTable[3], };
		HintTable[0].init("longDescription", "Chunk islands are destroyed after this time or separation from their origins.  This parameter sets the lifetimes and max separations within their min-max ranges.  The valid range is [0,1].  Default is 0.5.", true);
		HintTable[1].init("max", physx::PxU64(1), true);
		HintTable[2].init("min", physx::PxU64(0), true);
		HintTable[3].init("shortDescription", "Every destructible asset defines a min and max lifetime, and maximum separation distance for its chunks.", true);
		ParamDefTable[14].setHints((const NxParameterized::Hint**)HintPtrTable, 4);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=15, longName="maxActorCreatesPerFrame"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[15];
		ParamDef->init("maxActorCreatesPerFrame", TYPE_U32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("shortDescription", "Lets the user throttle the number of SDK actor creates per frame (per scene) due to destruction, as this can be quite costly. The default is 0xffffffff (unlimited).", true);
		ParamDefTable[15].setHints((const NxParameterized::Hint**)HintPtrTable, 1);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=16, longName="maxChunkDepthOffset"
	{
		NxParameterized::DefinitionImpl* ParamDef = &ParamDefTable[16];
		ParamDef->init("maxChunkDepthOffset", TYPE_U32, NULL, true);

#ifdef NX_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "If maxChunkDepthOffset = 0, all chunks can be fractured.  If maxChunkDepthOffset = 1, the highest level (smallest) chunks are eliminated, etc.  This prevents too many chunks from being formed.  In other words, the higher maxChunkDepthOffset, the lower the LOD.", true);
		HintTable[1].init("shortDescription", "Effectively eliminates the higher level (smaller) chunks from NxDestructibleAssets (see NxDestructibleAsset).", true);
		ParamDefTable[16].setHints((const NxParameterized::Hint**)HintPtrTable, 2);

#endif /* NX_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// SetChildren for: nodeIndex=0, longName=""
	{
		static Definition* Children[7];
		Children[0] = PDEF_PTR(1);
		Children[1] = PDEF_PTR(11);
		Children[2] = PDEF_PTR(12);
		Children[3] = PDEF_PTR(13);
		Children[4] = PDEF_PTR(14);
		Children[5] = PDEF_PTR(15);
		Children[6] = PDEF_PTR(16);

		ParamDefTable[0].setChildren(Children, 7);
	}

	// SetChildren for: nodeIndex=1, longName="gpuRigidBodySettings"
	{
		static Definition* Children[9];
		Children[0] = PDEF_PTR(2);
		Children[1] = PDEF_PTR(3);
		Children[2] = PDEF_PTR(4);
		Children[3] = PDEF_PTR(5);
		Children[4] = PDEF_PTR(6);
		Children[5] = PDEF_PTR(7);
		Children[6] = PDEF_PTR(8);
		Children[7] = PDEF_PTR(9);
		Children[8] = PDEF_PTR(10);

		ParamDefTable[1].setChildren(Children, 9);
	}

	mBuiltFlag = true;

}
void DestructibleModuleParameters_0p0::initStrings(void)
{
}

void DestructibleModuleParameters_0p0::initDynamicArrays(void)
{
}

void DestructibleModuleParameters_0p0::initDefaults(void)
{

	freeStrings();
	freeReferences();
	freeDynamicArrays();
	gpuRigidBodySettings.gpuDeviceOrdinal = physx::PxI32(-1);
	gpuRigidBodySettings.meshCellSize = physx::PxF32(0.25);
	gpuRigidBodySettings.skinWidth = physx::PxF32(0.01);
	gpuRigidBodySettings.nonPenSolverPosIterCount = physx::PxU32(9);
	gpuRigidBodySettings.frictionSolverPosIterCount = physx::PxU32(3);
	gpuRigidBodySettings.frictionSolverVelIterCount = physx::PxU32(3);
	gpuRigidBodySettings.maxLinAcceleration = physx::PxF32(PX_MAX_F32);
	gpuRigidBodySettings.gpuMemSceneSize = physx::PxU32(64);
	gpuRigidBodySettings.gpuMemTempDataSize = physx::PxU32(192);
	maxDynamicChunkIslandCount = physx::PxU32(0);
	sortFIFOByBenefit = bool(false);
	validBoundsPadding = physx::PxF32(0);
	maxChunkSeparationLOD = physx::PxF32(0.5);
	maxActorCreatesPerFrame = physx::PxU32(PX_MAX_U32);
	maxChunkDepthOffset = physx::PxU32(0);

	initDynamicArrays();
	initStrings();
	initReferences();
}

void DestructibleModuleParameters_0p0::initReferences(void)
{
}

void DestructibleModuleParameters_0p0::freeDynamicArrays(void)
{
}

void DestructibleModuleParameters_0p0::freeStrings(void)
{
}

void DestructibleModuleParameters_0p0::freeReferences(void)
{
}

} // namespace apex
} // namespace physx
