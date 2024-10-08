#include "input_router.h"

#include <core/assert.h>

namespace input
{
  Router* Router::m_Router = nullptr;

  Router::Router()
  {
    get_keyboard_driver()->setListener(this);
    get_pointer_driver()->setListener(this);
  }

  Router::~Router()
  {
    get_keyboard_driver()->setListener(nullptr);
    get_pointer_driver()->setListener(nullptr);
  }

  void Router::init()
  {
    ASSERT(m_Router == nullptr);
    m_Router = new Router;
  }

  void Router::destroy()
  {
    ASSERT(m_Router != nullptr);
    delete m_Router;
    m_Router = nullptr;
  }

  void Router::onMouseButtonStateChanged(const IPointer& device,
                                              const int key,
                                              const bool pressed)
  {
    for (auto* l: m_Listeners)
    {
      const auto st = l->onMouseButtonStateChanged(device, key, pressed);
      if (st == InputRouterProcessStatus::StopProcessing)
        break;
    }
  }

  void Router::onMouseMove(const IPointer& device,
                                const int2 new_pos,
                                const int2 delta)
  {
    for (auto* l: m_Listeners)
    {
      const auto st = l->onMouseMove(device, new_pos, delta);
      if (st == InputRouterProcessStatus::StopProcessing)
        break;
    }
  }

  void Router::onMouseWheelScroll(const IPointer& device, const float delta)
  {
    for (auto* l: m_Listeners)
    {
      const auto st = l->onMouseWheelScroll(device, delta);
      if (st == InputRouterProcessStatus::StopProcessing)
        break;
    }
  }

  void Router::onKeyStateChanged(const IKeyboard& device,
                                      const int key,
                                      const bool pressed)
  {
    for (auto* l: m_Listeners)
    {
      const auto st = l->onKeyStateChanged(device, key, pressed);
      if (st == InputRouterProcessStatus::StopProcessing)
        break;
    }
  }

  void Router::registerListener(IInputRouterListener* l)
  {
    auto it = std::find(m_Router->m_Listeners.begin(), m_Router->m_Listeners.end(), l);
    if (it == m_Router->m_Listeners.end())
      m_Router->m_Listeners.insert(l);
  }

  void Router::unregisterListener(IInputRouterListener* l)
  {
    m_Router->m_Listeners.erase(l);
  }
}
