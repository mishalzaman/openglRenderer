# OpengGL Renderer

I have always been interested in how 3d graphics are created and rendered, therefore learning OpenGL seemed like the best option. The following are the dependencies this renderer uses:  

- SDL 2.5
- GLM (math library)
- Assimp (model loader)
- stbi (texture loader)

## Features

### In Progress
- [ ] Scene Manager
  - [x] Read and load from a flat file
  - [x] load shaders
  - [x] load meshes
  - [x] load entities
  - [ ] load uniform buffers (for shader uniforms)
  - [x] Attach each entity to a game object class
- [x] Shader (load vertex/fragment shaders and link them)
- [x] Model (load meshes using assimp)
- [x] SkyBox
- [ ] First Person Camera
  - [ ] Requires adjustments to sensitivity
- [x] Input (handle user input)
- [x] FrameBuffer
- [x] Engine (main class that loads OpenGL prerequisites, creates context etc)
- [ ] AABB (Axis Align Bounding Box collision) 

### Future
- [ ] Variable time step where renderer is independent of user input.
- [ ] Uniform Buffer Objects
- [ ] Shadow Mapping
- [ ] Physically Based Rendering