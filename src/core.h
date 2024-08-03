#pragma once

#include "types.h"
#include <raylib.h>

#include <raylib.h>
#include <raymath.h>

#define COUNT_OF(arr) (size_t)(sizeof(arr)/sizeof(arr[0]))

// text drawing

static Font GLOBAL_FONT;

static inline 
void draw_text(const char* text, int x, int y, int font_size_px, Color color)
{
    DrawTextEx(GLOBAL_FONT, text, (Vector2) {x, y}, font_size_px, 1.0f, color);
}

// forward declare types

typedef Vector2 vec2d;
typedef Vector3 vec3d;

typedef struct mat4x4 mat4x4;

typedef struct viewport viewport;



// -----------------------------------------------------------------------------
// vector stuff
// -----------------------------------------------------------------------------

// scale vec2d by a f32 factor
void vec2d_scale(vec2d* v, f32 factor);

// multiply vec2d by vec2d
void vec2d_multiply(vec2d *v, f32 factor);

// takes input (vec3d) i, multiplies it by matrix (mat4x4) m and outputs to buffer (vec3d) o
void multiply_vec_by_mat(vec3d* i, mat4x4* m, vec3d* o);

// -----------------------------------------------------------------------------
// matrix stuff
// -----------------------------------------------------------------------------
typedef struct mat4x4
{
    f64 m[4][4];
} mat4x4;

// generate x-rotation matrix
mat4x4 matrix_rotation_X(f32 angle); 

// generate y-rotation matrix
mat4x4 matrix_rotation_Y(f32 angle);

// generate z-rotation matrix
mat4x4 matrix_rotation_Z(f32 angle);

// multiply matrix (mat4x4*) x by matrix (mat4x4*) y and outputs to buffer (mat4x4*) o
mat4x4 matrix_multiplication(mat4x4* x, mat4x4* y, mat4x4* o);

// -----------------------------------------------------------------------------
// tri stuff
// -----------------------------------------------------------------------------

typedef struct tri
{
    vec3d p[3]; // points
} tri;

void tri_print(tri t);
void tri_draw(tri t);

void tri_scale(tri* t, f32 factor, tri* o);

void tri_scale_v(tri* t, vec3d vector, tri* o);

void tri_project(tri t, viewport* v, tri* o);

void tri_rotate_m(tri t, mat4x4* rm, tri* o);

void tri_translate(tri t, vec3d vector, tri* o);

void tri_translate_xyz(tri t, f32 x, f32 y, f32 z, tri* o);

// -----------------------------------------------------------------------------
// mesh stuff
// -----------------------------------------------------------------------------

typedef struct mesh 
{
    tri* tris;
    size_t tri_count;
} mesh;

void _mesh_print(mesh mesh, const char* mesh_name);
mesh mesh_cube(void);

#define mesh_print(mesh) _mesh_print(mesh, #mesh)
