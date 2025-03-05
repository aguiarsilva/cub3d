# cub3d
Cub3d project from 42School

# Cub3D Project Checklist

## 1. Initial Setup
- [ ] Create project directory structure
- [ ] Initialize git repository
- [ ] Create Makefile
- [ ] Set up MLX library
- [ ] Create basic header file
- [ ] Configure error handling system
- [ ] Set up basic window display

## 2. Map Parsing
- [ ] File handling
  - [ ] Open and read .cub file
  - [ ] Check file extension
  - [ ] Handle file errors
- [ ] Parse map elements
  - [ ] Read texture paths (NO, SO, WE, EA)
  - [ ] Parse floor color (F)
  - [ ] Parse ceiling color (C)
  - [ ] Store map grid in memory
- [ ] Map validation
  - [ ] Check map is enclosed by walls
  - [ ] Validate player starting position (N,S,E,W)
  - [ ] Check for invalid characters
  - [ ] Validate map is rectangular/valid
  - [ ] Check texture files exist and are readable
  - [ ] Validate color format (RGB)

## 3. Graphics Setup
- [ ] MLX initialization
  - [ ] Create window
  - [ ] Handle window events
  - [ ] Setup double buffering
- [ ] Texture handling
  - [ ] Load texture files
  - [ ] Convert textures to usable format
  - [ ] Store texture data
- [ ] Basic rendering
  - [ ] Draw simple shapes
  - [ ] Implement pixel plotting
  - [ ] Create frame buffer

## 4. Raycasting Implementation
- [ ] Basic raycasting
  - [ ] Calculate ray positions and directions
  - [ ] Implement DDA algorithm
  - [ ] Calculate wall distances
  - [ ] Determine wall heights
- [ ] Wall rendering
  - [ ] Draw vertical wall strips
  - [ ] Apply texture mapping
  - [ ] Handle different wall sides
  - [ ] Fix fisheye effect
- [ ] Floor/Ceiling
  - [ ] Draw floor with color
  - [ ] Draw ceiling with color

## 5. Player Movement
- [ ] Basic movement
  - [ ] Forward/Backward movement
  - [ ] Left/Right movement
  - [ ] Rotation (left/right)
- [ ] Collision detection
  - [ ] Wall collision
  - [ ] Boundary checking
- [ ] Input handling
  - [ ] Key press events
  - [ ] Key release events
  - [ ] Exit handling (ESC key)

## 6. Optimization & Polish
- [ ] Performance optimization
  - [ ] Efficient rendering
  - [ ] Memory management
  - [ ] Frame rate optimization
- [ ] Code cleanup
  - [ ] Remove memory leaks
  - [ ] Norm compliance (42 style)
  - [ ] Code documentation
- [ ] Error handling
  - [ ] Graceful error messages
  - [ ] Memory cleanup on exit
  - [ ] Handle edge cases

## 7. Testing
- [ ] Create test maps
  - [ ] Basic valid maps
  - [ ] Complex maps
  - [ ] Invalid maps
- [ ] Test all features
  - [ ] Movement in all directions
  - [ ] Collision with walls
  - [ ] Texture rendering
  - [ ] Color rendering
  - [ ] Error handling
- [ ] Test edge cases
  - [ ] Invalid files
  - [ ] Memory limits
  - [ ] Window resizing
  - [ ] Various map sizes

## 8. Documentation
- [ ] README file
- [ ] Usage instructions
- [ ] Map format documentation
- [ ] Known limitations
- [ ] Installation guide

## Bonus Features (Optional)
- [ ] Minimap
- [ ] Wall collisions
- [ ] Sprite rendering
- [ ] Floor/ceiling textures
- [ ] Doors
- [ ] Animated textures
