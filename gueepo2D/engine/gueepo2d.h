#pragma once

// ============================================================
// ============================================================
//				CORE INCLUDES
// ============================================================
// ============================================================
#ifdef GUEEPO2D_MAIN
#include "core/EntryPoint.h"
#endif


#include "core/Application.h"
#include "core/Common.h"
#include "core/Log.h"
#include "core/Window.h"

#include "core/debug/Profiler.h"

#include "core/audio/Audio.h"

#include "core/containers/hashed_string.h"
#include "core/containers/string.h"
#include "core/containers/vector.h"

#include "core/events/Event.h"
#include "core/events/EventDispatcher.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/KeyEvent.h"
#include "core/events/MouseEvent.h"

#include "core/filesystem/File.h"
#include "core/filesystem/Filesystem.h"
#include "core/filesystem/Font.h"
#include "core/filesystem/json.h"

#include "core/input/Input.h"

#include "core/math/math.h"
#include "core/math/mat4.h"
#include "core/math/rand.h"
#include "core/math/rect.h"
#include "core/math/vec2.h"
#include "core/math/vec3.h"

#include "core/renderer/Renderer.h"
#include "core/renderer/Shader.h"
#include "core/renderer/Texture.h"
#include "core/renderer/Color.h"
#include "core/renderer/OrtographicCamera.h"
#include "core/renderer/FontSprite.h"

#include "core/ui/UIManager.h"
#include "core/ui/Control.h"
#include "core/ui/Container.h"
#include "core/ui/Label.h"
#include "core/ui/PixelPanel.h"

// ============================================================
// ============================================================
//				UTILS INCLUDES
// ============================================================
// ============================================================
#include "utils/ImageUtils.h"
#include "utils/ResourceManager.h"
#include "utils/TextureRegion.h"
#include "utils/PixelBuffer.h"
#include "utils/SpriteAnimation.h"
#include "utils/Tilemap.h"
