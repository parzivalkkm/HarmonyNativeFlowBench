#include "napi/native_api.h"
#include "hilog/log.h"

static napi_value Leak(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
    
    char* str = new char[256];
    napi_get_value_string_utf8(env, args[0], str, NAPI_AUTO_LENGTH, nullptr);
    
    OH_LOG_INFO(LOG_APP, "Leak LastLocation (libdynamic.so) %{public}s", str);
    
    return args[0];
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "leak", nullptr, Leak, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

// https://developer.huawei.com/consumer/cn/forum/topic/0204155244605065198

static napi_module dynamicModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "dynamic",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&dynamicModule);
}
