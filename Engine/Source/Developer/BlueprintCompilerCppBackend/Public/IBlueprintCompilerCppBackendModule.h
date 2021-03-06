// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/StringAssetReference.h"
#include "BlueprintCompilerCppBackendInterface.h"

class UBlueprint;

struct FNativizationSummary
{
	TMap<FStringAssetReference, int32> InaccessiblePropertyStat;

	struct FAnimBlueprintDetails
	{
		int32 Functions; //Number of functions or events
		int32 ReducibleFunctions; //Number of empty functions
		int32 Variables; // Number of new BlueprintReadWrite properties
		int32 Children; // Number of nativized children
		int32 FunctionUsage; //How many times a function (introduced in the BP) was used by unrelated nativized BP
		int32 VariableUsage; //How many times a variable (introduced in the BP) was used by unrelated nativized BP

		FAnimBlueprintDetails()
			: Functions(0), ReducibleFunctions(0), Variables(0), Children(0), FunctionUsage(0), VariableUsage(0)
		{}
	};

	TMap<FStringAssetReference, FAnimBlueprintDetails> AnimBlueprintStat;

	int32 MemberVariablesFromGraph;

	// The NativeLine is stored and the key is String-Reference, so the object doesn't need to be loaded.
	struct FDependencyRecord
	{
		FString NativeLine;
		int32 Index;

		FDependencyRecord() : Index(-1) {}
	};

	TMap<FStringAssetReference, FDependencyRecord> DependenciesGlobalMap;

	FNativizationSummary() : MemberVariablesFromGraph(0) {}
};

/**
 * The public interface to this module
 */
class IBlueprintCompilerCppBackendModule : public IBlueprintCompilerCppBackendModuleInterface
{
public:
	/**
	 * Aimed to help coordinate #include statements (generated by the backend) 
	 * and target file paths. A centralized function, that'll generate a 
	 * source-file name for the supplied asset object.
	 * 
	 * @param  AssetObj    The asset you want a source-file name for.
	 * @return The filename (without an extension) for the target asset.
	 */
	virtual FString ConstructBaseFilename(const UObject* AssetObj) = 0;


	DECLARE_DELEGATE_RetVal(FString, FPCHFilenameQuery);
	/**
	 * Provides a hook so that external modules can specify the PCH file that 
	 * should be used for generated source.
	 * 
	 * @return A delegate that will be used to fill out the shared include statement in generated source.
	 */
	virtual FPCHFilenameQuery& OnPCHFilenameQuery() = 0;


	DECLARE_DELEGATE_RetVal_OneParam(bool, FIsTargetedForConversionQuery, const UObject*);
	/**
	 * Provides a hook so that external modules can specify which assets will 
	 * and won't be converted (so the backend knows how to handle cross asset 
	 * references).
	 * 
	 * @return A delegate that will used to determine how to generate cross asset references (in generated source).
	 */
	virtual FIsTargetedForConversionQuery& OnIsTargetedForConversionQuery() = 0;

	/**
	 *	Cpp is generated from a duplicate of the original Blueprint. This map stores info about the original BPGC.
	 */
	virtual TMap<TWeakObjectPtr<UClass>, TWeakObjectPtr<UClass> >& GetOriginalClassMap() = 0;

	/**
	 *	Provides a hook so that external modules can mark some unconverted blueprints as necessary for the generated native code.
	 */
	DECLARE_DELEGATE_OneParam(FMarkUnconvertedBlueprintAsNecessary, TAssetPtr<UBlueprint>);
	virtual FMarkUnconvertedBlueprintAsNecessary& OnIncludingUnconvertedBP() = 0;

	DECLARE_DELEGATE_RetVal_OneParam(bool, FIsFunctionUsedInADelegate, const UFunction*);
	virtual FIsFunctionUsedInADelegate& GetIsFunctionUsedInADelegateCallback() = 0;

	// Collect functions that are used by delegates - they must have UFUNCTION macro
	BLUEPRINTCOMPILERCPPBACKEND_API static TArray<class UFunction*> CollectBoundFunctions(class UBlueprint* BP);

	virtual TSharedPtr<FNativizationSummary>& NativizationSummary() = 0;

	virtual FString DependenciesGlobalMapHeaderCode() = 0;
	virtual FString DependenciesGlobalMapBodyCode() = 0;
};

