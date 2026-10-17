# Codex changelog

## 2026-10-17T10:44:21-05:00 — iteration 001: metadata variable names

- Reason: preserve producer dependency/address-binding names while exposing each metadata region by its declared variable name.
- Files: `src/ast.hpp`, `src/ast.cpp`, `src/dtl_api.hpp`, `src/dtl_api.cpp`.
- Change: carry producer ID, local metadata ID, and slot through preprocessing and compiled dependencies; use local IDs for handle lookup and ordinary metadata binding.
- Tests: isolated production-code host test passed with UBSan; `git diff --check` passed. Full syntax check remains blocked by existing errors.
- FireSim: not run.
- Disposition: kept; issues 7–10 unchanged.
- Branch: `composability`, explicitly authorized by the user. Pre-existing changes preserved; no stash or commit.
- Archive: `archive/001_metadata_names_changes/` contains before/after snapshots, per-file diffs, the host check, and validation details.
