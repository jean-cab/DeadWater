# Deadwater

Solo horror game built in Unreal Engine 5 over three months, with gameplay systems written in C++ on top of a Blueprint foundation.

**▶ Play it:** Incoming - playable build, Windows  
**Start here:** [`ScriptedEvents/CPP_Sound_swim`](Source/ScriptedEvents/CPP_Sound_swim.cpp) and [`/Interfaces`](Source/Interfaces)

---

## About this repo

This repository contains the C++ source files only — no assets, levels, or Blueprint graphs. The full project is too large to host here, so this is the code layer on its own. The playable build is linked above.

The project splits responsibilities: **C++ handles gameplay systems and logic** (event scripting, ambient audio sequencing, environmental triggers), **Blueprint handles content-side work** (UI, animations, material instances, input setup). A deliberate separation between systems programming and content implementation.

## Project structure

```
/Source
  /Player          → character, controller, camera (3C)
  /ScriptedEvents  → core gameplay systems: triggers, audio, lighting
  /Interfaces      → decoupled communication between class types
  /UI              → HUD and widget base classes
  /Core            → game mode
```

## Highlighted systems

### `ScriptedEvents/CPP_Sound_swim`
Ambient event actor that approaches a target from a randomized direction, adjusts pitch and volume on proximity detection, then chains into a second actor's function through a dynamic delegate once its sequence completes.

This drives the core scene of the game: the threat is never shown on screen. Its position, distance and approach are carried entirely by spatialized audio, with no 3D model and no UI. Event-driven sequencing across decoupled actors.

### `ScriptedEvents/CPP_Boat`
Scripted sequence actor: speed interpolation between acceleration and deceleration states, a deferred timer triggered by a widget animation event, and Perlin noise driving a secondary visual effect. State-driven actor behavior synced with UI-side animation events.

## Interfaces — decoupled communication

`/Interfaces` contains six `UInterface` classes (`Widget_to_GM`, `HUD_To_Controller`, `Actor_to_Actor`, and others) letting Widgets, HUD, Controller, GameMode and Actor classes communicate without direct casts or hard dependencies. Each concrete class implements only the interfaces it needs, keeping systems loosely coupled and Blueprint-callable through `BlueprintNativeEvent`.

## Blueprint / C++ integration

The `WBP_Loading_Screen` Event Graph orchestrates the transition between levels:

1. Streams the game level in asynchronously (`LoadStreamLevelBySoftObjectPtr`)
2. Unloads the menu level once loading completes
3. Calls `ChangePawnClass` on the GameMode through the `Widget_to_GM` interface
4. Calls `SwitchInput` on the PlayerController through the `Widget_to_Controller` interface
5. Plays a fade-out animation, then collapses the widget

<img width="2035" height="846" alt="image" src="https://github.com/user-attachments/assets/0dc8095c-eade-4f2f-9972-4e10a5a3461e" />


The Blueprint-side driver for the asynchronous level streaming system referenced in the C++ source, tying two of the interfaces above into a single sequence.

## Stack

Unreal Engine 5 · C++ · Blueprint · MetaSound

---

**Jean Cabrolier** - gameplay programmer  
[itch.io](https://jeancab.itch.io/) · [LinkedIn](https://www.linkedin.com/in/jean-cabrolier/)
