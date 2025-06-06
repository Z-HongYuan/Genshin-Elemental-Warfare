// Copyright 2022 bstt, Inc. All Rights Reserved.

#include "ANA_CommandHelper.h"
#include "../Arrangement/ANA_Manager.h"
#include "../Debug/Log.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "ANA_GraphHelper.h"
#include "ANA_SelectionHelper.h"

void ANA_CommandHelper::ArrangeNodesStraight()
{
	// bCompact, bCenterize
	ArrangeNodes(false, false);
}

void ANA_CommandHelper::ArrangeNodesCenter()
{
	// bCompact, bCenterize
	ArrangeNodes(false, true);
}

void ANA_CommandHelper::ArrangeNodesCompact()
{
	// bCompact, bCenterize
	ArrangeNodes(true, false); // last bCenterize will be used
}

void ANA_CommandHelper::SelectConnectedGraph()
{
	INIT_GRAPH_PANEL();
	ANA_SelectionHelper::SelectConnectedGraph(graphPanel);
}

void ANA_CommandHelper::RegisterAllNodes()
{
	INIT_GRAPH_PANEL();
	ANA_Manager::instance.RegisterAllNodes(graphPanel);
}

void ANA_CommandHelper::AddCustomConfig()
{
	TSharedPtr<SGraphPanel> shrGraphPanel = ANA_GraphHelper::GetCurrentGraphPanel();
	if (!shrGraphPanel.IsValid())
	{
		FNotificationInfo notifWarning(NSLOCTEXT("AutoNodeArranger", "AddCustomConfigCommand", ""));
		FString message = FString("No graph panel detected");
		notifWarning.Text = FText::FromString(message);
		notifWarning.ExpireDuration = 3.0f;
		notifWarning.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Warning"));
		FSlateNotificationManager::Get().AddNotification(notifWarning);
		UE_LOG(LogAutoNodeArranger, Warning, TEXT("%s"), *message);
		return;
	}
	auto graphClassName = shrGraphPanel->GetGraphObj()->GetClass()->GetFName().ToString();
	if (UANA_EditorConfig::ContainsGraphConfig(graphClassName))
	{
		FNotificationInfo notifInfo(NSLOCTEXT("AutoNodeArranger", "AddCustomConfigCommand", ""));
		FString message = graphClassName + FString(" has already a custom config");
		notifInfo.Text = FText::FromString(message);
		notifInfo.ExpireDuration = 3.0f;
		FSlateNotificationManager::Get().AddNotification(notifInfo);
		UE_LOG(LogAutoNodeArranger, Warning, TEXT("%s"), *message);
		return;
	}
	UANA_EditorConfig::AddGraphConfig(graphClassName);
	FNotificationInfo notifInfo(NSLOCTEXT("AutoNodeArranger", "AddCustomConfigCommand", ""));
	FString message = graphClassName + FString(" added");
	notifInfo.Text = FText::FromString(message);
	notifInfo.ExpireDuration = 3.0f;
	FSlateNotificationManager::Get().AddNotification(notifInfo);
	UE_LOG(LogAutoNodeArranger, Warning, TEXT("%s"), *message);
}

void ANA_CommandHelper::ArrangeNodes(bool bCompact, bool bCenterize)
{
	INIT_GRAPH_PANEL();
	if (isForbiddenGraph)
	{
		FNotificationInfo notifWarning(NSLOCTEXT("AutoNodeArranger", "ArrangeCommand", ""));
		FString message = FString("Arrange command disabled for this graph type");
		notifWarning.ExpireDuration = 3.0f;
		notifWarning.Text = FText::FromString(message);
		notifWarning.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Warning"));
		FSlateNotificationManager::Get().AddNotification(notifWarning);
		UE_LOG(LogAutoNodeArranger, Warning, TEXT("%s"), *message);
		return;
	}
	ANA_GraphPanel::instance.StopArrangeGraph();
	ANA_GraphPanel::instance = ANA_GraphPanel(graphPanel, graphType);

	// initialized with parameters value
	static bool bLastCenterize = bCenterize;

	if (bCompact)
		bCenterize = bLastCenterize && (graphType != EGraphTypeEnum::Blueprint); // no compact centerize for blueprintGraph

	ANA_Manager::instance.ArrangeGraph(bCompact, bCenterize, graphConfig);

	bLastCenterize = bCenterize;
}
