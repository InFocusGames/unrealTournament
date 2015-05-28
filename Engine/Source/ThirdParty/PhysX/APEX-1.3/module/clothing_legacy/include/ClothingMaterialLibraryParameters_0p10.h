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

#ifndef HEADER_ClothingMaterialLibraryParameters_0p10_h
#define HEADER_ClothingMaterialLibraryParameters_0p10_h

#include "NxParametersTypes.h"

#ifndef NX_PARAMETERIZED_ONLY_LAYOUTS
#include "NxParameterized.h"
#include "NxParameters.h"
#include "NxParameterizedTraits.h"
#include "NxTraitsInternal.h"
#endif

namespace physx
{
namespace apex
{

#pragma warning(push)
#pragma warning(disable: 4324) // structure was padded due to __declspec(align())

namespace ClothingMaterialLibraryParameters_0p10NS
{

struct StiffnessScaling_Type;
struct ClothingMaterial_Type;

struct ClothingMaterial_DynamicArray1D_Type
{
	ClothingMaterial_Type* buf;
	bool isAllocated;
	physx::PxI32 elementSize;
	physx::PxI32 arraySizes[1];
};

struct StiffnessScaling_Type
{
	physx::PxF32 range;
	physx::PxF32 scale;
};
struct ClothingMaterial_Type
{
	NxParameterized::DummyStringStruct materialName;
	physx::PxF32 verticalStretchingStiffness;
	physx::PxF32 horizontalStretchingStiffness;
	physx::PxF32 bendingStiffness;
	physx::PxF32 shearingStiffness;
	physx::PxF32 zeroStretchStiffness;
	physx::PxF32 tetherStiffness;
	physx::PxF32 tetherLimit;
	bool orthoBending;
	StiffnessScaling_Type verticalStiffnessScaling;
	StiffnessScaling_Type horizontalStiffnessScaling;
	StiffnessScaling_Type bendingStiffnessScaling;
	StiffnessScaling_Type shearingStiffnessScaling;
	physx::PxF32 damping;
	physx::PxF32 stiffnessFrequency;
	physx::PxF32 drag;
	bool comDamping;
	physx::PxF32 friction;
	physx::PxF32 massScale;
	physx::PxU32 solverIterations;
	physx::PxF32 solverFrequency;
	physx::PxF32 gravityScale;
	physx::PxF32 inertiaScale;
	physx::PxF32 hardStretchLimitation;
	physx::PxF32 maxDistanceBias;
	physx::PxU32 hierarchicalSolverIterations;
};

struct ParametersStruct
{

	ClothingMaterial_DynamicArray1D_Type materials;

};

static const physx::PxU32 checksum[] = { 0x4bbf73c3, 0xbb7f05e0, 0xf659f61c, 0x827f3962, };

} // namespace ClothingMaterialLibraryParameters_0p10NS

#ifndef NX_PARAMETERIZED_ONLY_LAYOUTS
class ClothingMaterialLibraryParameters_0p10 : public NxParameterized::NxParameters, public ClothingMaterialLibraryParameters_0p10NS::ParametersStruct
{
public:
	ClothingMaterialLibraryParameters_0p10(NxParameterized::Traits* traits, void* buf = 0, PxI32* refCount = 0);

	virtual ~ClothingMaterialLibraryParameters_0p10();

	virtual void destroy();

	static const char* staticClassName(void)
	{
		return("ClothingMaterialLibraryParameters");
	}

	const char* className(void) const
	{
		return(staticClassName());
	}

	static const physx::PxU32 ClassVersion = ((physx::PxU32)0 << 16) + (physx::PxU32)10;

	static physx::PxU32 staticVersion(void)
	{
		return ClassVersion;
	}

	physx::PxU32 version(void) const
	{
		return(staticVersion());
	}

	static const physx::PxU32 ClassAlignment = 8;

	static const physx::PxU32* staticChecksum(physx::PxU32& bits)
	{
		bits = 8 * sizeof(ClothingMaterialLibraryParameters_0p10NS::checksum);
		return ClothingMaterialLibraryParameters_0p10NS::checksum;
	}

	static void freeParameterDefinitionTable(NxParameterized::Traits* traits);

	const physx::PxU32* checksum(physx::PxU32& bits) const
	{
		return staticChecksum(bits);
	}

	const ClothingMaterialLibraryParameters_0p10NS::ParametersStruct& parameters(void) const
	{
		ClothingMaterialLibraryParameters_0p10* tmpThis = const_cast<ClothingMaterialLibraryParameters_0p10*>(this);
		return *(static_cast<ClothingMaterialLibraryParameters_0p10NS::ParametersStruct*>(tmpThis));
	}

	ClothingMaterialLibraryParameters_0p10NS::ParametersStruct& parameters(void)
	{
		return *(static_cast<ClothingMaterialLibraryParameters_0p10NS::ParametersStruct*>(this));
	}

	virtual NxParameterized::ErrorType getParameterHandle(const char* long_name, NxParameterized::Handle& handle) const;
	virtual NxParameterized::ErrorType getParameterHandle(const char* long_name, NxParameterized::Handle& handle);

	void initDefaults(void);

protected:

	virtual const NxParameterized::DefinitionImpl* getParameterDefinitionTree(void);
	virtual const NxParameterized::DefinitionImpl* getParameterDefinitionTree(void) const;


	virtual void getVarPtr(const NxParameterized::Handle& handle, void*& ptr, size_t& offset) const;

private:

	void buildTree(void);
	void initDynamicArrays(void);
	void initStrings(void);
	void initReferences(void);
	void freeDynamicArrays(void);
	void freeStrings(void);
	void freeReferences(void);

	static bool mBuiltFlag;
	static NxParameterized::MutexType mBuiltFlagMutex;
};

class ClothingMaterialLibraryParameters_0p10Factory : public NxParameterized::Factory
{
	static const char* const vptr;

public:
	virtual NxParameterized::Interface* create(NxParameterized::Traits* paramTraits)
	{
		// placement new on this class using mParameterizedTraits

		void* newPtr = paramTraits->alloc(sizeof(ClothingMaterialLibraryParameters_0p10), ClothingMaterialLibraryParameters_0p10::ClassAlignment);
		if (!NxParameterized::IsAligned(newPtr, ClothingMaterialLibraryParameters_0p10::ClassAlignment))
		{
			NX_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class ClothingMaterialLibraryParameters_0p10");
			paramTraits->free(newPtr);
			return 0;
		}

		memset(newPtr, 0, sizeof(ClothingMaterialLibraryParameters_0p10)); // always initialize memory allocated to zero for default values
		return NX_PARAM_PLACEMENT_NEW(newPtr, ClothingMaterialLibraryParameters_0p10)(paramTraits);
	}

	virtual NxParameterized::Interface* finish(NxParameterized::Traits* paramTraits, void* bufObj, void* bufStart, physx::PxI32* refCount)
	{
		if (!NxParameterized::IsAligned(bufObj, ClothingMaterialLibraryParameters_0p10::ClassAlignment)
		        || !NxParameterized::IsAligned(bufStart, ClothingMaterialLibraryParameters_0p10::ClassAlignment))
		{
			NX_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class ClothingMaterialLibraryParameters_0p10");
			return 0;
		}

		// Init NxParameters-part
		// We used to call empty constructor of ClothingMaterialLibraryParameters_0p10 here
		// but it may call default constructors of members and spoil the data
		NX_PARAM_PLACEMENT_NEW(bufObj, NxParameterized::NxParameters)(paramTraits, bufStart, refCount);

		// Init vtable (everything else is already initialized)
		*(const char**)bufObj = vptr;

		return (ClothingMaterialLibraryParameters_0p10*)bufObj;
	}

	virtual const char* getClassName()
	{
		return (ClothingMaterialLibraryParameters_0p10::staticClassName());
	}

	virtual physx::PxU32 getVersion()
	{
		return (ClothingMaterialLibraryParameters_0p10::staticVersion());
	}

	virtual physx::PxU32 getAlignment()
	{
		return (ClothingMaterialLibraryParameters_0p10::ClassAlignment);
	}

	virtual const physx::PxU32* getChecksum(physx::PxU32& bits)
	{
		return (ClothingMaterialLibraryParameters_0p10::staticChecksum(bits));
	}
};
#endif // NX_PARAMETERIZED_ONLY_LAYOUTS

} // namespace apex
} // namespace physx

#pragma warning(pop)

#endif
