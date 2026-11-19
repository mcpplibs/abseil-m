// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil — Abseil, Google's C++ common libraries (LTS 20250512.1), as C++ modules.
// The root re-exports every group of the library and the macro mappings; each group can also be imported
// alone (import mcpplibs.mwrap.abseil.strings;). The library itself is compat.abseil, built from the same release.
export module mcpplibs.mwrap.abseil;

export import mcpplibs.mwrap.abseil.base;
export import mcpplibs.mwrap.abseil.meta;
export import mcpplibs.mwrap.abseil.utility;
export import mcpplibs.mwrap.abseil.memory;
export import mcpplibs.mwrap.abseil.functional;
export import mcpplibs.mwrap.abseil.algorithm;
export import mcpplibs.mwrap.abseil.numeric;
export import mcpplibs.mwrap.abseil.types;
export import mcpplibs.mwrap.abseil.hash;
export import mcpplibs.mwrap.abseil.container;
export import mcpplibs.mwrap.abseil.strings;
export import mcpplibs.mwrap.abseil.crc;
export import mcpplibs.mwrap.abseil.cleanup;
export import mcpplibs.mwrap.abseil.debugging;
export import mcpplibs.mwrap.abseil.synchronization;
export import mcpplibs.mwrap.abseil.time;
export import mcpplibs.mwrap.abseil.status;
export import mcpplibs.mwrap.abseil.random;
export import mcpplibs.mwrap.abseil.log;
export import mcpplibs.mwrap.abseil.flags;
export import mcpplibs.mwrap.abseil.macros;
