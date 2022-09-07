emcc -std=c++11 "../Sparky-core/src/editor/document/document_handler.cpp" "../Sparky-core/src/editor/document/document.cpp" "../Sparky-core/src/editor/tool/brush_tool.cpp" "../Sparky-core/src/editor/tool/tool.cpp" "../Sparky-core/src/editor/tool/tool_handler.cpp" "../Sparky-core/src/editor/editor.cpp" "../Sparky-core/src/graphics/window/input_handler.cpp" "../Sparky-core/src/graphics/window/window.cpp" "../Sparky-core/src/graphics/buffers/buffer.cpp" "../Sparky-core/src/graphics/buffers/indexbuffer.cpp" "../Sparky-core/src/graphics/buffers/vertexarray.cpp" "../Sparky-core/src/graphics/layers/tileLayer.cpp" "../Sparky-core/src/graphics/layers/layer.cpp" "../Sparky-core/src/graphics/sprite.cpp" "../Sparky-core/src/graphics/batchRenderer2d.cpp" "../Sparky-core/src/graphics/shader.cpp" "../Sparky-core/src/maths/mat4.cpp" "../Sparky-core/src/maths/vec2.cpp" "../Sparky-core/src/maths/vec3.cpp" "../Sparky-core/src/maths/vec4.cpp" "../Sparky-core/main.cpp" -s USE_GLFW=3 -s FULL_ES3=1 -DSPARKY_EMSCRIPTEN=1 --memory-init-file 0 --embed-file res -O3 -o Web\sparky.js