# KAFrontedUI — Modular Unreal Engine Frontend UI Framework

A C++ driven Frontend UI architecture built for Unreal Engine using **CommonUI**, **GameplayTags**, **EnhancedInput**, and **Asynchronous Latent Actions**. Designed to decouple UI navigation, modal confirmation dialogs, and game settings from hardcoded widget references.

---

## Main Purpose

Modern Unreal Engine menus require non-blocking asset loading, seamless gamepad/keyboard/mouse focus routing, and scalable settings management. **KAFrontedUI** solves this by providing:

- **Zero-Hitch Async UI Loading:** Uses `TSoftClassPtr` and custom `UBlueprintAsyncActionBase` nodes to stream and push widgets onto layered UI stacks without blocking the game thread.
- **Tag-Driven Stack Routing & Modal Dialogs:** Menus, modals, and confirmation prompts are pushed to designated layers using `GameplayTags` (`Frontend.WidgetStack.*`) with `TFunction` lambda and multicast delegate callbacks.
- **Data-Driven Options & Settings Pipeline:** A modular tab registry (`UOptionsDataRegistry`) and polymorphic `UListView` data-object pipeline (`UListDataObject_Base`) that cleanly separates Gameplay, Audio, Video, Controls, and Cheats settings from UI presentation.
- **Cross-Platform Input & Focus Management:** Built on top of `CommonInput` and `EnhancedInput` to automatically manage input focus targets and dynamic button description broadcasts.

---
## Development Roadmap & Build Process

> **Status:** In Active Development — Sections below document the completed architectural milestones and upcoming stages.

### Stage 1: Core Infrastructure & Base Widgets
- **Custom Player Controller (`AFrontedUIPlayerController`):** C++ PlayerController foundation configured to manage UI input modes and route player ownership into activatable menus.
- **Native Gameplay Tags (`FGameplayTags`):** Registered hierarchical stack and widget identification tags (`Frontend.WidgetStack.*`, `Frontend.Widget.*`) directly in C++ for compile-time safety.
- **Primary Layout Container (`UWidget_PrimaryLayout`):** Derived from `UCommonUserWidget` to act as the root viewport canvas, mapping `FGameplayTag` keys to `UCommonActivatableWidgetContainerBase` layers.
- **Centralized UI Subsystem (`UFrontendUISybsystem`):** `UGameInstanceSubsystem` managing primary layout registration, asynchronous soft-widget loading, modal stack pushing, and global button description broadcasts.
- **Activatable Widget Base (`UWidget_ActivatableBase`):** Base screen class extending `UCommonActivatableWidget` with cached weak-pointer access (`TWeakObjectPtr<AFrontedUIPlayerController>`) to the owning player controller.

### Stage 2: Async Streaming, Templates & Data-Driven Lookup
- **Latent Async Push Node (`UAsyncAction_PushSoftWidget`):** Custom `UBlueprintAsyncActionBase` node that streams `TSoftClassPtr<UWidget_ActivatableBase>` off the game thread, assigns the owning `APlayerController`, fires pre/post-push delegates, and sets focus automatically.
- **Template Layout System:** Standardized base widget blueprint layouts shared across multiple menu screens to maintain consistent visual framing and navigation bars.
- **Editor Developer Settings (`UKAFrontendSettings`):** Exposed directly inside **Project Settings** to eliminate hardcoded asset paths. Uses a `TMap<FGameplayTag, TSoftClassPtr<UWidget_ActivatableBase>>` (`FrontendWidgetMap`) to bind widget tags to soft class references in the editor.
- **Lightweight Blueprint Function Library (`UFrontendFunctionLibrary`):** Fast, category-filtered Blueprint helper nodes (`GetFrontendSoftWidgetClassByTag`) that resolve soft widget classes directly from a single `FGameplayTag` without bloated default Blueprint lookups.

### Stage 3: CommonUI Primitives & Modal Dialogs
- **Custom CommonButton (`UFrontendCommonButtonBase`):** Extended `UCommonButtonBase` supporting dynamic text formatting (automatic uppercase toggle), synchronized `UCommonTextBlock` styling, and hover/unhover description broadcasts to the UI subsystem.
- **Modal Confirmation Screen (`UWidget_ConfirmScreen` & `UConfirmScreenInfoObject`):** Reusable modal dialog system supporting `OK`, `Yes/No`, and `OK/Cancel` layouts via dynamic button entry boxes (`UDynamicEntryBox`) and `TFunction` / async latent callbacks (`UAsyncAction_PushConfirmScreen`).

### Next Stage: Options Pipeline & Persistent Settings *(In Progress)*
- **Data-Driven Options Registry (`UOptionsDataRegistry`):** Modular tab initialization (`Gameplay`, `Audio`, `Video`, `Controls`, `Cheats`) decoupled from UI list entries.
- **Custom GameUserSettings (`UFrontendGameUserSettings`):** Persistent save/load reflection bindings via `FOptionsDataInteractionHelper`.
- *(Reserved for upcoming modules and polish...)*

---
## System Architecture

```text
Source/KAFrontedUI/
├── Public/
│   ├── AsyncActions/                # Latent Blueprint nodes
│   │   ├── AsyncAction_PushConfirmScreen.h
│   │   └── AsyncAction_PushSoftWidget.h
│   ├── Controllers/                 # Custom PlayerController integration
│   │   └── FrontedUIPlayerController.h
│   ├── FrontendSettings/            # Persistent user & developer settings
│   │   ├── FrontendGameUserSettings.h
│   │   └── KAFrontendSettings.h
│   ├── FrontedTypes/                # Shared enums & state definitions
│   │   └── FrontendEnumTypes.h
│   ├── Subsystem/                   # GameInstanceSubsystem hub
│   │   └── FrontendUISybsystem.h
│   └── Widgets/
│       ├── Components/              # Reusable CommonUI primitives
│       │   ├── FrontendCommonButtonBase.h
│       │   ├── FrontendCommonListView.h
│       │   ├── FrontendCommonRotator.h
│       │   └── FrontendTabListWidgetBase.h
│       ├── Options/                 # Data-driven settings architecture
│       │   ├── DataObjects/
│       │   │   ├── ListDataObject_Base.h
│       │   │   ├── ListDataObject_Collection.h
│       │   │   ├── ListDataObject_String.h
│       │   │   └── ListDataObject_Value.h
│       │   ├── ListEntries/
│       │   ├── DataAsset_DataListEntryMapping.h
│       │   ├── OptionsDataInteractionHelper.h
│       │   ├── OptionsDataRegistry.h
│       │   ├── Widget_OptionsDetailsView.h
│       │   └── Widget_OptionsScreen.h
│       ├── Widget_ActivatableBase.h
│       ├── Widget_ConfirmScreen.h
│       └── Widget_PrimaryLayout.h
```
---

## Module Dependencies & Tech Stack

Configured in `KAFrontedUI.Build.cs`:

| Category | Modules |
| :--- | :--- |
| **UI & Input** | `UMG`, `CommonInput`, `EnhancedInput`, `Slate`, `SlateCore` |
| **Architecture & Data** | `GameplayTags`, `PropertyPath`, `Core`, `CoreUObject`, `Engine`, `InputCore` |

---
## Code Style & Header Convention

All C++ headers and source files follow a strict ownership-based layout to keep Unreal Engine overrides, UMG widget bindings, and custom class logic immediately distinguishable:

- **Top-of-File Types:** Grouped sequentially above `UCLASS()` under `// FORWARD DECLARATIONS`, `// ENUMS`, `// STRUCTS`, `// DELEGATES`, and `// MACROS`.
- **Ownership Banners (`// METHODS`):** Functions are grouped by origin (`// [ClassName]`, `// [ParentClass]`, and `// UE` with explicit `// from UUserWidget` / `// from UCommonButtonBase` markers) rather than lumping everything under a single access specifier.
- **UI & State Separation:** Designer-bound UMG pointers are isolated under `// BIND WIDGETS` (`BindWidget` / `BindWidgetOptional`), while member variables and delegates live under `// PROPERTIES`.
- **1:1 `.cpp` Symmetry:** Implementation files mirror the exact same ownership banners in identical top-to-bottom order.

---
## Process Overview - How To?

1. **Configure Gameplay Tags:** Define your widget stack hierarchy under `Frontend.WidgetStack` (e.g., `Frontend.WidgetStack.Frontend`, `Frontend.WidgetStack.GameMenu`, `Frontend.WidgetStack.Modal`).
2. **Initialize Primary Layout:** Create a Blueprint subclass of `UWidget_PrimaryLayout` containing your named widget stacks and register it at startup via `UFrontendUISybsystem::RegisterCreatedPrimaryLayoutWidget`.
3. **Push Menus Asynchronously:** Call **Push Soft Widget to Widget Stack** from Blueprints (or `PushSoftWidgetToStackAnynsc` in C++), passing a `TSoftClassPtr<UWidget_ActivatableBase>` and target stack `GameplayTag`.
4. **Extend Settings:** Add new option entries inside `UOptionsDataRegistry` using `UListDataObject_String`, `UListDataObject_Value`, or `UListDataObject_Collection`, and map them in `UDataAsset_DataListEntryMapping`.
