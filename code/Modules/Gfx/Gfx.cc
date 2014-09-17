//------------------------------------------------------------------------------
//  Gfx.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "Gfx.h"

namespace Oryol {

using namespace _priv;

Gfx::_state* Gfx::state = nullptr;

//------------------------------------------------------------------------------
void
Gfx::Setup(const class GfxSetup& setup) {
    o_assert_dbg(!IsValid());
    state = new _state();
    state->gfxSetup = setup;
    state->displayManager.SetupDisplay(setup);
    state->stateWrapper.Setup();
    state->resourceManager.Setup(setup, &state->stateWrapper, &state->displayManager);
    state->renderManager.Setup(&state->stateWrapper, &state->displayManager);
}

//------------------------------------------------------------------------------
void
Gfx::Discard() {
    o_assert_dbg(IsValid());
    state->renderManager.Discard();
    state->resourceManager.Discard();
    state->stateWrapper.Discard();
    state->displayManager.DiscardDisplay();
    delete state;
    state = nullptr;
}

//------------------------------------------------------------------------------
bool
Gfx::QuitRequested() {
    o_assert_dbg(IsValid());
    return state->displayManager.QuitRequested();
}

//------------------------------------------------------------------------------
void
Gfx::AttachEventHandler(const Ptr<Port>& handler) {
    o_assert_dbg(IsValid());
    o_assert_dbg(handler.isValid());
    state->displayManager.AttachDisplayEventHandler(handler);
}

//------------------------------------------------------------------------------
void
Gfx::DetachEventHandler(const Ptr<Port>& handler) {
    o_assert_dbg(IsValid());
    o_assert_dbg(handler.isValid());
    state->displayManager.DetachDisplayEventHandler(handler);
}

//------------------------------------------------------------------------------
const GfxSetup&
Gfx::GfxSetup() {
    o_assert_dbg(IsValid());
    return state->gfxSetup;
}

//------------------------------------------------------------------------------
const DisplayAttrs&
Gfx::DisplayAttrs() {
    o_assert_dbg(IsValid());
    return state->displayManager.GetDisplayAttrs();
}

//------------------------------------------------------------------------------
/**
 NOTE: the LookupResource() method will bump the use-count of looked up
 resource, so make sure to call DiscardResource() when you're done with it!
*/
GfxId
Gfx::LookupResource(const Locator& loc) {
    o_assert_dbg(IsValid());
    return GfxId(state->resourceManager.LookupResource(loc));
}

//------------------------------------------------------------------------------
ResourceState::Code
Gfx::QueryResourceState(const GfxId& gfxId) {
    o_assert_dbg(IsValid());
    return state->resourceManager.QueryResourceState(gfxId.Id());
}

//------------------------------------------------------------------------------
void
Gfx::ApplyDefaultRenderTarget() {
    o_assert_dbg(IsValid());
    state->renderManager.ApplyRenderTarget(nullptr);
}

//------------------------------------------------------------------------------
void
Gfx::ApplyOffscreenRenderTarget(const GfxId& gfxId) {
    o_assert_dbg(IsValid());
    o_assert_dbg(gfxId.IsValid());

    texture* renderTarget = state->resourceManager.LookupTexture(gfxId.Id());
    o_assert_dbg(nullptr != renderTarget);
    state->renderManager.ApplyRenderTarget(renderTarget);
}

//------------------------------------------------------------------------------
void
Gfx::ApplyDrawState(const GfxId& gfxId) {
    o_assert_dbg(IsValid());
    state->renderManager.ApplyDrawState(state->resourceManager.LookupDrawState(gfxId.Id()));
}

//------------------------------------------------------------------------------
bool
Gfx::BeginFrame() {
    o_assert_dbg(IsValid());
    
    state->resourceManager.Update();
    state->displayManager.ProcessSystemEvents();
    state->renderManager.BeginFrame();
    
    /// @todo: check and return whether rendering is possible / necessary
    return true;
}

//------------------------------------------------------------------------------
void
Gfx::EndFrame() {
    o_assert_dbg(IsValid());
    state->renderManager.EndFrame();
    state->displayManager.Present();
}

//------------------------------------------------------------------------------
void
Gfx::ResetStateCache() {
    o_assert_dbg(IsValid());
    state->stateWrapper.ResetStateCache();
}

//------------------------------------------------------------------------------
void
Gfx::UpdateVertices(const GfxId& gfxId, int32 numBytes, const void* data) {
    o_assert_dbg(IsValid());
    mesh* msh = state->resourceManager.LookupMesh(gfxId.Id());
    state->renderManager.UpdateVertices(msh, numBytes, data);
}

//------------------------------------------------------------------------------
void
Gfx::ReadPixels(void* buf, int32 bufNumBytes) {
    o_assert_dbg(IsValid());
    state->renderManager.ReadPixels(buf, bufNumBytes);
}

//------------------------------------------------------------------------------
void
Gfx::Clear(PixelChannel::Mask channels, const glm::vec4& color, float32 depth, uint8 stencil) {
    o_assert_dbg(IsValid());
    state->renderManager.Clear(channels, color, depth, stencil);
}

//------------------------------------------------------------------------------
void
Gfx::Draw(int32 primGroupIndex) {
    o_assert_dbg(IsValid());
    state->renderManager.Draw(primGroupIndex);
}

//------------------------------------------------------------------------------
void
Gfx::Draw(const PrimitiveGroup& primGroup) {
    o_assert_dbg(IsValid());
    state->renderManager.Draw(primGroup);
}

//------------------------------------------------------------------------------
void
Gfx::DrawInstanced(int32 primGroupIndex, int32 numInstances) {
    o_assert_dbg(IsValid());
    state->renderManager.DrawInstanced(primGroupIndex, numInstances);
}

//------------------------------------------------------------------------------
void
Gfx::DrawInstanced(const PrimitiveGroup& primGroup, int32 numInstances) {
    o_assert_dbg(IsValid());
    state->renderManager.DrawInstanced(primGroup, numInstances);
}

} // namespace Oryol
