#pragma once
#include <napi.h>

#include <QMediaContent>

#include "nodegui/Extras/Utils/nutils.h"
#include "nodegui/core/Component/component_macro.h"

class DLL_EXPORT QMediaContentWrap
    : public Napi::ObjectWrap<QMediaContentWrap> {
  COMPONENT_WRAPPED_METHODS_DECLARATION
 private:
  std::unique_ptr<QMediaContent> instance;

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QMediaContentWrap(const Napi::CallbackInfo& info);
  ~QMediaContentWrap();
  QMediaContent* getInternalInstance();
  // Wrapped methods
  Napi::Value isNull(const Napi::CallbackInfo& info);
};