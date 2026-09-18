# Periodic Color

`Periodic Color` is a C Pebble watchface for every rectangular display: Aplite,
Basalt, Diorite, Flint, and Emery (Pebble Time 2). It recreates the original
Periodic layout—two diagonal periodic-table cards on a black background—while
using approximations of each element's real-world appearance on colour screens.

The time is read from the atomic number in each card. In 12-hour mode, `12:46`
is Magnesium / Palladium. In 24-hour mode, the hour uses `00`–`23`. Element zero
is intentionally the original watchface's `Nuetronium` entry so that `:00` and
midnight always have a card.

## Motion

When an element changes, its old card exits at the bottom while the replacement
enters from above. Both columns call the same draw routine, easing expression,
650 ms duration, and 30 FPS timer; a side cannot use a different curve or lag
the other side. The hour card only animates when the hour changes, avoiding a
distracting duplicate transition every minute.

On Emery (Pebble Time 2), the larger 94 px cards automatically use larger
atomic-number, name, and weight fonts with expanded text bands. The 66 px card
layout used by every other rectangular target is unchanged.

## Build

Install the current Pebble SDK/`pebble-tool`, then run:

```sh
pebble build
```

The generated bundle contains all listed rectangular platform builds. No phone
companion or network connection is required.

## Colour note

The Pebble palette has 64 colours, so the C source uses memorable chemistry
cues instead of making most metals the same grey: sodium is flame yellow,
strontium is firework red, potassium and noble-gas discharges are purple,
copper is orange, and so on. Monochrome hardware automatically maps these to
the nearest supported shade while retaining the identical layout and motion.

## Settings

The companion app’s settings page provides a background picker followed by a
60-entry element editor. Each entry has independent card and text-colour
pickers, and **Reset to original preset colours** restores the chemistry-cue
palette. Colour watches receive Clay’s 64-colour Pebble palette. Monochrome
watches receive five grayscale swatches (black through white), which PebbleOS
maps to its supported display shades.

The project includes Clay as a package dependency. If your local SDK does not
install project packages during `pebble build`, run `pebble package install`
once before building.
