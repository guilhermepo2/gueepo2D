#pragma once

// ============================================================
// ============================================================
//				CORE INCLUDES
// ============================================================
// ============================================================
#include "core/Common.h"
#include "core/Log.h"
#include "core/EntryPoint.h"
#include "core/Application.h"
#include "core/Window.h"

#include "core/Containers/String.h"

#include "core/Debug/Profiler.h"

#include "core/events/Event.h"
#include "core/events/EventDispatcher.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/KeyEvent.h"
#include "core/events/MouseEvent.h"

#include "core/filesystem/File.h"
#include "core/filesystem/Filesystem.h"
#include "core/filesystem/json.h"

#include "core/layer/Layer.h"
#include "core/layer/LayerStack.h"

#include "core/renderer/Renderer.h"
#include "core/renderer/RendererAPI.h"
#include "core/renderer/GraphicsContext.h"
#include "core/renderer/VertexArray.h"
#include "core/renderer/VertexBuffer.h"
#include "core/renderer/IndexBuffer.h"
#include "core/renderer/Shader.h"
#include "core/renderer/Texture.h"
#include "core/renderer/Color.h"
#include "core/renderer/OrtographicCamera.h"

#include "core/math/Math.h"
#include "core/math/Vector2.h"
#include "core/math/Vector3.h"
#include "core/math/Matrix4.h"
#include "core/math/Random.h"

#include "core/input/Input.h"

#include "core/ImGuiLayer.h"

#include "core/GameObject/Entity.h"
#include "core/GameObject/GameObject.h"
#include "core/GameObject/Component.h"
#include "core/GameObject/TransformComponent.h"
#include "core/GameObject/SpriteComponent.h"

// ============================================================
// ============================================================
//				UTILS INCLUDES
// ============================================================
// ============================================================
#include "utils/ImageUtils.h"
#include "utils/JsonHelper.h"
#include "utils/Tilemap.h"
