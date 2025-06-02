#include "napi/native_api.h"
#include "hilog/log.h"

static napi_value Leak(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
    
    char* str = new char[256];
    napi_get_value_string_utf8(env, args[0], str, NAPI_AUTO_LENGTH, nullptr);
    
    OH_LOG_INFO(LOG_APP, "Leak LastLocation %{public}s", str);
    
    return nullptr;
}

static napi_value LeakByCall(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
    // 获取全局对象，这里用global是因为napi_call_function的第二个参数是JS函数的this入参。
    napi_value global = nullptr;
    napi_get_global(env, &global);
    
    napi_value result = nullptr;
    napi_call_function(env, global, args[0],  1, &args[1], &result);
    
    return result;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "leak", nullptr, Leak, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "leakByCall", nullptr, LeakByCall, nullptr, nullptr, nullptr, napi_default, nullptr }
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
