#include "napi/native_api.h"

static napi_value SetProperty(napi_env env, napi_callback_info info)
{
    // 接收ArkTS侧传入的三个参数：第一个参数为想要设置的object，第二个参数为属性，第三个参数为属性对应的值
    size_t argc = 3;
    napi_value args[3] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    napi_set_property(env, args[0], args[1], args[2]);
}

static napi_value SetNamedProperty(napi_env env, napi_callback_info info)
{
    // 接收ArkTS侧传入的两个参数：第一个参数为想要设置的object，第二个参数为属性对应的值
    size_t argc = 3;
    napi_value args[3] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    napi_set_named_property(env, args[0], "lastLocation", args[2]);
}



EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"setProperty", nullptr, SetProperty, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setNamedProperty", nullptr, SetNamedProperty, nullptr, nullptr, nullptr, napi_default, nullptr}
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&demoModule);
}
