#pragma once
#define PGT_VERSION_MAJOR 0
#define PGT_VERSION_MINOR 1

// Debug or Release Build
#if _DEBUG
#define PGT_DEBUG true
#else
#define PGT_DEBUG false
#endif
#define PGT_RELEASE !PGT_DEBUG

// Windowing toolkit
#define PGT_WTK_SDL true
#define PGT_WTK_GLFW false  // currently broken

// Rendering Standard
#define PGT_RENDERER_2D_DYNAMIC false   // not implemented
#define PGT_RENDERER_2D_HARDWARE true   // SELECTED
#define PGT_RENDERER_2D_SOFTWARE false  // not implemented

// Hardware Acceleration API
#define PGT_HWA_OPENGL true
#define PGT_HWA_DIRECTX false  // not supported yet