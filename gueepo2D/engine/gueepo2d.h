#pragma once

// ============================================================
// ============================================================
//				CORE INCLUDES
// ============================================================
// ============================================================
#include "core/Application.h"
#include "core/Common.h"
#include "core/EntryPoint.h"
#include "core/Log.h"
#include "core/ImGuiLayer.h"
#include "core/Window.h"

#include "core/Containers/hashed_string.h"
#include "core/Containers/string.h"
#include "core/Containers/vector.h"
#include "core/Debug/Profiler.h"

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

#include "core/layer/Layer.h"
#include "core/layer/LayerStack.h"

#include "core/math/math.h"
#include "core/math/mat4.h"
#include "core/math/rand.h"
#include "core/math/vec2.h"
#include "core/math/vec3.h"

#include "core/physics/LineSegment.h"

#include "core/renderer/Renderer.h"
#include "core/renderer/RendererAPI.h"
#include "core/renderer/GraphicsContext.h"
#include "core/renderer/VertexArray.h"
#include "core/renderer/VertexBuffer.h"
#include "core/renderer/IndexBuffer.h"
#include "core/renderer/Shader.h"
#include "core/renderer/SpriteBatcher.h"
#include "core/renderer/Texture.h"
#include "core/renderer/Color.h"
#include "core/renderer/OrtographicCamera.h"
#include "core/renderer/FontSprite.h"

// ============================================================
// ============================================================
//				UTILS INCLUDES
// ============================================================
// ============================================================
#include "utils/ImageUtils.h"
#include "utils/JsonHelper.h"
#include "utils/Tilemap.h"
#include "utils/TextureRegion.h"
#include "utils/PixelBuffer.h"
