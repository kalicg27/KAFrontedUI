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

## Process Overview - How To?

1. **Configure Gameplay Tags:** Define your widget stack hierarchy under `Frontend.WidgetStack` (e.g., `Frontend.WidgetStack.Frontend`, `Frontend.WidgetStack.GameMenu`, `Frontend.WidgetStack.Modal`).
2. **Initialize Primary Layout:** Create a Blueprint subclass of `UWidget_PrimaryLayout` containing your named widget stacks and register it at startup via `UFrontendUISybsystem::RegisterCreatedPrimaryLayoutWidget`.
3. **Push Menus Asynchronously:** Call **Push Soft Widget to Widget Stack** from Blueprints (or `PushSoftWidgetToStackAnynsc` in C++), passing a `TSoftClassPtr<UWidget_ActivatableBase>` and target stack `GameplayTag`.
4. **Extend Settings:** Add new option entries inside `UOptionsDataRegistry` using `UListDataObject_String`, `UListDataObject_Value`, or `UListDataObject_Collection`, and map them in `UDataAsset_DataListEntryMapping`.
