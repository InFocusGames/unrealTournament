// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "CurveAssetEditorPrivatePCH.h"

#include "CurveAssetEditor.h"
#include "SCurveEditor.h"
#include "RichCurveEditorCommands.h"
//#include "Toolkits/IToolkitHost.h"
#include "WorkspaceMenuStructureModule.h"
#include "SDockTab.h"
#include "Curves/CurveVector.h"
#include "Curves/CurveLinearColor.h"
#include "Curves/CurveFloat.h"
#include "SNumericDropDown.h"

#define LOCTEXT_NAMESPACE "CurveAssetEditor"

const FName FCurveAssetEditor::CurveTabId( TEXT( "CurveAssetEditor_Curve" ) );

void FCurveAssetEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager)
{
	WorkspaceMenuCategory = TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_CurveAssetEditor", "Curve Asset Editor"));

	FAssetEditorToolkit::RegisterTabSpawners(TabManager);

	TabManager->RegisterTabSpawner( CurveTabId, FOnSpawnTab::CreateSP(this, &FCurveAssetEditor::SpawnTab_CurveAsset) )
		.SetDisplayName( LOCTEXT("CurveTab", "Curve") )
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "ClassIcon.CurveBase"));
}

void FCurveAssetEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager)
{
	TabManager->UnregisterTabSpawner( CurveTabId );
}

void FCurveAssetEditor::InitCurveAssetEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UCurveBase* CurveToEdit )
{	
	TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout( "Standalone_CurveAssetEditor_Layout" )
	->AddArea
	(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.1f)
			->SetHideTabWell( true )
			->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
		) 
		->Split
		(
			FTabManager::NewStack()
			->SetHideTabWell( true )
			->AddTab( CurveTabId, ETabState::OpenedTab )
		)
	);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor( Mode, InitToolkitHost, FCurveAssetEditorModule::CurveAssetEditorAppIdentifier, StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, CurveToEdit );
	
	FCurveAssetEditorModule& CurveAssetEditorModule = FModuleManager::LoadModuleChecked<FCurveAssetEditorModule>( "CurveAssetEditor" );
	AddMenuExtender(CurveAssetEditorModule.GetMenuExtensibilityManager()->GetAllExtenders(GetToolkitCommands(), GetEditingObjects()));
	AddToolbarExtender(GetToolbarExtender());

	// @todo toolkit world centric editing
	/*// Setup our tool's layout
	if( IsWorldCentricAssetEditor() )
	{
		const FString TabInitializationPayload(TEXT(""));		// NOTE: Payload not currently used for table properties
		SpawnToolkitTab( CurveTabId, TabInitializationPayload, EToolkitTabSpot::Details );
	}*/

	if (TrackWidget.IsValid())
	{
		RegenerateMenusAndToolbars();
	}
}

FName FCurveAssetEditor::GetToolkitFName() const
{
	return FName("CurveAssetEditor");
}

FText FCurveAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT( "AppLabel", "Curve Asset Editor" );
}

FString FCurveAssetEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "CurveAsset ").ToString();
}

FLinearColor FCurveAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor( 0.0f, 0.0f, 0.2f, 0.5f );
}

TSharedRef<SDockTab> FCurveAssetEditor::SpawnTab_CurveAsset( const FSpawnTabArgs& Args )
{
	check( Args.GetTabId().TabType == CurveTabId );

	ViewMinInput=0.f;
	ViewMaxInput=5.f;

	InputSnap = 0.1f;
	OutputSnap = 0.05f;

	TSharedRef<SDockTab> NewDockTab = SNew(SDockTab)
		.Icon( FEditorStyle::GetBrush("CurveAssetEditor.Tabs.Properties") )
		.Label( FText::Format(LOCTEXT("CurveAssetEditorTitle", "{0} Curve Asset"), FText::FromString(GetTabPrefix())))
		.TabColorScale( GetTabColorScale() )
		[
			SNew(SBorder)
			.BorderImage( FEditorStyle::GetBrush("ToolPanel.GroupBorder") )
			.Padding(0.0f)
			[
				SAssignNew(TrackWidget, SCurveEditor)
				.ViewMinInput(this, &FCurveAssetEditor::GetViewMinInput)
				.ViewMaxInput(this, &FCurveAssetEditor::GetViewMaxInput)
				.InputSnap(this, &FCurveAssetEditor::GetInputSnap)
				.OutputSnap(this, &FCurveAssetEditor::GetOutputSnap)
				.TimelineLength(this, &FCurveAssetEditor::GetTimelineLength)
				.OnSetInputViewRange(this, &FCurveAssetEditor::SetInputViewRange)
				.HideUI(false)
				.AlwaysDisplayColorCurves(true)
				.ShowZoomButtons(false)
			]
		];

	UCurveBase* Curve = Cast<UCurveBase>(GetEditingObject());

	FCurveOwnerInterface* CurveOwner = Curve;
	
	if (CurveOwner != NULL)
	{
		check(TrackWidget.IsValid());
		// Set this curve as the SCurveEditor's selected curve
		TrackWidget->SetCurveOwner(CurveOwner);
	}

	return NewDockTab;
}

float FCurveAssetEditor::GetInputSnap() const
{
	return InputSnap;
}

void FCurveAssetEditor::SetInputSnap(float value)
{
	InputSnap = value;
}

float FCurveAssetEditor::GetOutputSnap() const
{
	return OutputSnap;
}

void FCurveAssetEditor::SetOutputSnap(float value)
{
	OutputSnap = value;
}

float FCurveAssetEditor::GetTimelineLength() const
{
	return 0.f;
}

void FCurveAssetEditor::SetInputViewRange(float InViewMinInput, float InViewMaxInput)
{
	ViewMaxInput = InViewMaxInput;
	ViewMinInput = InViewMinInput;
}

TSharedPtr<FExtender> FCurveAssetEditor::GetToolbarExtender()
{
	struct Local
	{
		static void FillToolbar(FToolBarBuilder& ToolbarBuilder, TSharedRef<SWidget> InputSnapWidget, TSharedRef<SWidget> OutputSnapWidget)
		{
			ToolbarBuilder.BeginSection("Curve");
			{
				ToolbarBuilder.AddToolBarButton(FRichCurveEditorCommands::Get().ZoomToFitHorizontal);
				ToolbarBuilder.AddToolBarButton(FRichCurveEditorCommands::Get().ZoomToFitVertical);
				ToolbarBuilder.AddToolBarButton(FRichCurveEditorCommands::Get().ZoomToFitAll);
				ToolbarBuilder.AddToolBarButton(FRichCurveEditorCommands::Get().ZoomToFitSelected);
			}
			ToolbarBuilder.EndSection();

			ToolbarBuilder.BeginSection("Interpolation");
			{
				ToolbarBuilder.AddToolBarButton(FRichCurveEditorCommands::Get().InterpolationCubicAuto);
				ToolbarBuilder.AddToolBarButton(FRichCurveEditorCommands::Get().InterpolationCubicUser);
				ToolbarBuilder.AddToolBarButton(FRichCurveEditorCommands::Get().InterpolationCubicBreak);
				ToolbarBuilder.AddToolBarButton(FRichCurveEditorCommands::Get().InterpolationLinear);
				ToolbarBuilder.AddToolBarButton(FRichCurveEditorCommands::Get().InterpolationConstant);
			}
			ToolbarBuilder.EndSection();

			ToolbarBuilder.BeginSection("Snap");
			{
				ToolbarBuilder.AddToolBarButton(FRichCurveEditorCommands::Get().ToggleSnapping);
				ToolbarBuilder.AddWidget(InputSnapWidget);
				ToolbarBuilder.AddWidget(OutputSnapWidget);
			}
			ToolbarBuilder.EndSection();
		}
	};

	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

	TArray<SNumericDropDown<float>::FNamedValue> SnapValues;
	SnapValues.Add( SNumericDropDown<float>::FNamedValue( 0.001f, LOCTEXT( "Snap_OneThousandth", "0.001" ), LOCTEXT( "SnapDescription_OneThousandth", "Set snap to 1/1000th" ) ) );
	SnapValues.Add( SNumericDropDown<float>::FNamedValue( 0.01f, LOCTEXT( "Snap_OneHundredth", "0.01" ), LOCTEXT( "SnapDescription_OneHundredth", "Set snap to 1/100th" ) ) );
	SnapValues.Add( SNumericDropDown<float>::FNamedValue( 0.1f, LOCTEXT( "Snap_OneTenth", "0.1" ), LOCTEXT( "SnapDescription_OneTenth", "Set snap to 1/10th" ) ) );
	SnapValues.Add( SNumericDropDown<float>::FNamedValue( 1.0f, LOCTEXT( "Snap_One", "1" ), LOCTEXT( "SnapDescription_One", "Set snap to 1" ) ) );
	SnapValues.Add( SNumericDropDown<float>::FNamedValue( 10.0f, LOCTEXT( "Snap_Ten", "10" ), LOCTEXT( "SnapDescription_Ten", "Set snap to 10" ) ) );
	SnapValues.Add( SNumericDropDown<float>::FNamedValue( 100.0f, LOCTEXT( "Snap_OneHundred", "100" ), LOCTEXT( "SnapDescription_OneHundred", "Set snap to 100" ) ) );

	TSharedRef<SWidget> InputSnapWidget =
		SNew( SNumericDropDown<float> )
		.DropDownValues( SnapValues )
		.LabelText( LOCTEXT("InputSnapLabel", "Input Snap"))
		.Value( this, &FCurveAssetEditor::GetInputSnap )
		.OnValueChanged( this, &FCurveAssetEditor::SetInputSnap )
		.Orientation( this, &FCurveAssetEditor::GetSnapLabelOrientation );

	TSharedRef<SWidget> OutputSnapWidget =
		SNew( SNumericDropDown<float> )
		.DropDownValues( SnapValues )
		.LabelText( LOCTEXT( "OutputSnapLabel", "Output Snap" ) )
		.Value( this, &FCurveAssetEditor::GetOutputSnap )
		.OnValueChanged( this, &FCurveAssetEditor::SetOutputSnap )
		.Orientation( this, &FCurveAssetEditor::GetSnapLabelOrientation );

	ToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		TrackWidget->GetCommands(),
		FToolBarExtensionDelegate::CreateStatic(&Local::FillToolbar, InputSnapWidget, OutputSnapWidget)
		);

	return ToolbarExtender;
}

EOrientation FCurveAssetEditor::GetSnapLabelOrientation() const
{
	return FMultiBoxSettings::UseSmallToolBarIcons.Get()
		? EOrientation::Orient_Horizontal
		: EOrientation::Orient_Vertical;
}

#undef LOCTEXT_NAMESPACE