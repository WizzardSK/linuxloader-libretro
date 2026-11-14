# Rules for coding agents

These apply to any AI agent working in this repository (Claude Code reads them through `CLAUDE.md`). They came out of testing the libretro cores with their testers.

## Branches and history

- The `libretro` branch is never deleted, and nothing that rewrites its history is run on it: no force-push, no rebase, no amending or squashing of commits that are already pushed. It is the fork's only long-lived branch.
- New features and experimental changes go on their own branch, and testers test builds of that branch. When testing is done, the branch is merged into `libretro`.
- A fix that users of the `libretro` builds need before the branch is merged is cherry-picked into `libretro`, in a way that does not break the later merge of the branch.

## Merging upstream Linux Loader

Upstream is lindbergh-loader/linuxloader (remote `upstream`, branch `main`).

- Only full merges of upstream, no cherry-picked upstream commits.
- The libretro core's own files stay ours when a merge conflicts on them: `src/libretro/`, `src/loader/libretro/`, `Makefile.libretro`, `.gitlab-ci.yml`, `.github/workflows/libretro.yml` and `buildbot-preflight.yml`, and the scripts the core's CI uses (`scripts/appimage/pack-libs.sh`, `install-mesa.sh`). When upstream deletes a script our CI still calls, keep it.
- In the loader's own files (the graphics, input and audio hooks the core adds to), take upstream's change and keep the core's additions in it.
- After a merge, `display_version` in `linuxloader_libretro.info` is the loader release merged in; the core reports it with this repository's commit.
- `CHANGELOG.md` is this fork's own. When a merge conflicts on it, keep this one.

## These files

- Only the developer writes to or deletes `AGENTS.md` and `CLAUDE.md`. An agent does not change them on its own; it proposes the change to the developer instead.

## Changelog and README

- `CHANGELOG.md` is updated in the same commit as the change it describes: what changed for someone using the core, newest first. Not a copy of the commit message.
- Entries go under the heading of the current month (e.g. "November 2026"). A change on a feature branch gets its entry on that branch; it reaches `libretro` with the merge.
- `README.md` is kept true in the same way: when a change makes a sentence in it wrong (a limit lifted, an option added, a file moved), fix the sentence in that commit.

## Code

- The game runs in the loader as a process of its own; the core starts it and talks to it through shared memory (`src/libretro/libretro_shm.h`). A change on one side of that interface is made on the other side in the same commit.
- Keep comments true. When a change makes a comment describe behaviour that no longer exists, fix or remove the comment in the same commit.
- Look at the big picture, not just the function being changed. For example, resetting the content and closing it have to stop the loader and release its shared memory through the same path; a reset is an unload and a load.
- Every core option has to be connected to something. Do not add an option the core does not read, and remove one that turns out to do nothing. Option defaults follow the loader's own defaults (`linuxloader.ini`) unless there is a reason, written down beside the option.
- A game's own `linuxloader.ini` and `controls.ini` keep working as they do standalone; a core option overrides a setting only where the README says so.

## Testing

- The core logs its version and the commit of this repository it was built from. Ask testers for RetroArch's log, and check which commit a log came from before drawing conclusions from it.
- Compare with standalone Linux Loader at the same release before calling something a core bug; when standalone fails the same way (Ghost Squad Evolution's 53.5 fps, for example), it is upstream's.
- Test works per game as the README's Controls section describes: most games quit and the core starts them again in test mode, some run a separate test program, some have the menu in the game. A change to it is tested with one game of each kind.

## Libretro pitfalls already hit in the other cores

Each of these was a bug in at least one of the cemu, rpcs3, vita3k, xenia or linuxloader cores. Check new code against them before asking testers.

- Audio: each retro_run hands the frontend exactly one frame's worth (sample rate / declared fps), never "whatever is queued". Several streams are mixed, not appended one after another, and each is taken in its own format and sample rate.
- Geometry: the size the frame is handed over at goes to the frontend: base geometry at load, SET_GEOMETRY when it changes, SET_SYSTEM_AV_INFO when it would exceed the max. The max has to cover the highest Resolution option.
- Pacing: the frontend paces display and audio; the core does not sleep to pace itself.
- Files: everything the core writes goes under `system/linuxloader/` (or `saves/linuxloader/`); nothing next to the RetroArch executable. The loader's log goes there too, and its warnings and errors also go to RetroArch's log.
- No window: the loader's own windows and dialogs have no place in a core. Every path that reaches for them needs a headless branch that answers the way the user most likely would.
- Unload: never end RetroArch's process. Stop the loader and wait for it with a timeout, and never wait without a timeout on something the frontend has to drive.
- No downloads at run time; data files ship with the core.
