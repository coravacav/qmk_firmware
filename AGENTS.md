# Agent notes

This is a personal fork of QMK. The keymaps that matter are the `coravacav` ones,
mainly the Keychron K8 Pro on the `keychron` branch:

- `keyboards/keychron/k8_pro/ansi/rgb/keymaps/coravacav/keymap.c`
- `keyboards/keychron/k8_pro/ansi/white/keymaps/coravacav/keymap.c`

## Keep the portfolio visualizer in sync

The portfolio site at `~/personal/portfolio` has a visualizer of these layers.
Whenever a keymap changes (keys, layers, behaviour, RGB colours), find that repo
and update the visualizer to match in the same piece of work. If the repo isn't
there, say so instead of skipping it quietly.

The visualizer is the `/keyboard` page. Its data lives in
`src/lib/keyboard/keymap.ts`, laid out row by row like `keymap.c` so the two can be
compared line by line. That includes the RGB colour logic, which mirrors
`mj_key_color`, `layer_key_color` and `layer_color_at`. The component is
`src/lib/keyboard/keyboardLayers.tsx`. Check it with `bun run lint` and
`bun run build`; bun isn't installed system-wide, so install it first if needed.

## Building

The toolchain is installed per user, not system-wide, so put it on `PATH` first:

```sh
export PATH="$HOME/.local/share/qmk/qmk_toolchains_linuxX64/bin:$HOME/.local/share/qmk/flashutils:$PATH"
make keychron/k8_pro/ansi/rgb:coravacav
```

`rgb.sh` and `white.sh` build and copy the firmware out, but need sudo for the copy.
