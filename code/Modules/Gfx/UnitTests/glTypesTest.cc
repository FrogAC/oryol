//------------------------------------------------------------------------------
//  glTypesTest.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "UnitTest++/src/UnitTest++.h"
#include "Gfx/gl/gl_impl.h"
#include "Gfx/gl/glTypes.h"

using namespace Oryol;
using namespace _priv;

//------------------------------------------------------------------------------
TEST(glTypesTest) {

    // glTexImage format
    // FIXME: incomplete
    CHECK(glTypes::asGLTexImageFormat(PixelFormat::RGBA8) == GL_RGBA);
    CHECK(glTypes::asGLTexImageFormat(PixelFormat::RGB8) == GL_RGB);
    CHECK(glTypes::asGLTexImageFormat(PixelFormat::R5G6B5) == GL_RGB);
    CHECK(glTypes::asGLTexImageFormat(PixelFormat::R5G5B5A1) == GL_RGBA);
    CHECK(glTypes::asGLTexImageFormat(PixelFormat::RGBA4) == GL_RGBA);
    CHECK(glTypes::asGLTexImageFormat(PixelFormat::RGBA32F) == GL_RGBA);
    CHECK(glTypes::asGLTexImageFormat(PixelFormat::RGBA16F) == GL_RGBA);
    CHECK(glTypes::asGLTexImageFormat(PixelFormat::D16) == GL_DEPTH_COMPONENT);
    CHECK(glTypes::asGLTexImageFormat(PixelFormat::D32) == GL_DEPTH_COMPONENT);
    #if ORYOL_OPENGLES2
    CHECK(glTypes::asGLTexImageFormat(PixelFormat::D24S8) == GL_DEPTH_STENCIL_OES);
    #else
    CHECK(glTypes::asGLTexImageFormat(PixelFormat::D24S8) == GL_DEPTH_STENCIL);
    #endif
    
    // glTexImage type
    // FIXME: incomplete
    CHECK(glTypes::asGLTexImageType(PixelFormat::RGBA8) == GL_UNSIGNED_BYTE);
    CHECK(glTypes::asGLTexImageType(PixelFormat::RGB8) == GL_UNSIGNED_BYTE);
    CHECK(glTypes::asGLTexImageType(PixelFormat::R5G6B5) == GL_UNSIGNED_SHORT_5_6_5);
    CHECK(glTypes::asGLTexImageType(PixelFormat::R5G5B5A1) == GL_UNSIGNED_SHORT_5_5_5_1);
    CHECK(glTypes::asGLTexImageType(PixelFormat::RGBA4) == GL_UNSIGNED_SHORT_4_4_4_4);
    CHECK(glTypes::asGLTexImageType(PixelFormat::D16) == GL_UNSIGNED_SHORT);
    CHECK(glTypes::asGLTexImageType(PixelFormat::D32) == GL_UNSIGNED_INT);
    CHECK(glTypes::asGLTexImageType(PixelFormat::RGBA32F) == GL_FLOAT);
    #if ORYOL_OPENGLES2
    CHECK(glTypes::asGLTexImageType(PixelFormat::RGBA16F) == GL_HALF_FLOAT_OES);
    CHECK(glTypes::asGLTexImageType(PixelFormat::D24S8) == GL_UNSIGNED_INT_24_8_OES);
    #else
    CHECK(glTypes::asGLTexImageType(PixelFormat::RGBA16F) == GL_HALF_FLOAT);
    CHECK(glTypes::asGLTexImageType(PixelFormat::D24S8) == GL_UNSIGNED_INT_24_8);
    #endif
}
